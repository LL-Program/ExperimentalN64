#include <metrics.h>
#include <dynarec/dynarec_memory_management.h>
#include <mem/n64bus.h>
#include "v1_compiler.h"
#include "v1_emitter.h"

void* v1_link_and_encode(dasm_State** d, size_t* code_size_result) {
    size_t code_size;
    dasm_link(d, &code_size);
#ifdef N64_LOG_COMPILATIONS
    printf("Generated %ld bytes of code\n", code_size);
#endif
    void* buf = dynarec_bumpalloc(code_size);
    dasm_encode(d, buf);

    if (code_size_result) {
        *code_size_result = code_size;
    }

    return buf;
}

static int arg_host_registers[] = {0, 0};
static int dest_host_register = 0;
static int valid_host_regs[32];
static int num_valid_host_regs;
static int num_available_host_regs;
static bool guest_reg_loaded[32];
static bool host_reg_used[32];
static int guest_reg_to_host_reg[32];

INLINE bool is_reg_loaded(int guest) {
    return guest_reg_loaded[guest];
}

INLINE bool is_reg_used(int host) {
    return host_reg_used[host];
}

INLINE int get_valid_host_reg() {
    for (int r = 0; r < num_valid_host_regs; r++) {
        if (!is_reg_used(r)) {
            return r;
        }
    }

    logfatal("Ran out of valid host regs! Should have flushed!");
}

INLINE void flush_reg(dasm_State** Dst, int guest) {
    if (is_reg_loaded(guest)) {
        int host_reg = guest_reg_to_host_reg[guest];
        flush_host_register_to_gpr(Dst, valid_host_regs[host_reg], guest);
        num_available_host_regs++;
    }
    guest_reg_loaded[guest] = false;
    host_reg_used[guest_reg_to_host_reg[guest]] = false;
}

INLINE int load_reg(dasm_State** Dst, int guest) {
    if (!is_reg_loaded(guest)) {
        guest_reg_loaded[guest] = true;
        int host_reg = get_valid_host_reg();
        num_available_host_regs--;

        guest_reg_to_host_reg[guest] = host_reg;
        host_reg_used[host_reg] = true;

        load_host_register_from_gpr(Dst, valid_host_regs[host_reg], guest);
    }
    int valid_host_reg = valid_host_regs[guest_reg_to_host_reg[guest]];
    return valid_host_reg;
}

INLINE void flush_all(dasm_State** Dst) {
    for (int r = 0; r < 32; r++) {
        if (is_reg_loaded(r)) {
            flush_reg(Dst, r);
        }
    }
}

INLINE void load_reg_1(dasm_State** Dst, int* dest1, int r1) {
    bool r1_loaded = is_reg_loaded(r1);

    if (num_available_host_regs >= 1 || r1_loaded) {
        *dest1 = load_reg(Dst, r1);
    } else {
        flush_all(Dst);
        *dest1 = load_reg(Dst, r1);
    }
}

INLINE void load_reg_2(dasm_State** Dst, int* dest1, int r1, int* dest2, int r2) {
    bool r1_loaded = is_reg_loaded(r1);
    bool r2_loaded = is_reg_loaded(r2);

    if (num_available_host_regs >= 2 || (r1_loaded && r2_loaded)) {
        *dest1 = load_reg(Dst, r1);
        *dest2 = load_reg(Dst, r2);
    } else {
        flush_all(Dst);
        *dest1 = load_reg(Dst, r1);
        *dest2 = load_reg(Dst, r2);
    }
}

INLINE void load_reg_3(dasm_State** Dst, int* dest1, int r1, int* dest2, int r2, int* dest3, int r3) {
    bool r1_loaded = is_reg_loaded(r1);
    bool r2_loaded = is_reg_loaded(r2);
    bool r3_loaded = is_reg_loaded(r3);

    if (num_available_host_regs >= 3 || (r1_loaded && r2_loaded && r3_loaded)) {
        *dest1 = load_reg(Dst, r1);
        *dest2 = load_reg(Dst, r2);
        *dest3 = load_reg(Dst, r3);
    } else {
        flush_all(Dst);
        *dest1 = load_reg(Dst, r1);
        *dest2 = load_reg(Dst, r2);
        *dest3 = load_reg(Dst, r3);
    }
}

bool branch_is_loop(mips_instruction_t instr, u32 block_length) {
    switch (instr.op) {
        case OPC_REGIMM: // REGIMM opcodes are only branches
        case OPC_BEQ:
        case OPC_BEQL:
        case OPC_BGTZ:
        case OPC_BGTZL:
        case OPC_BLEZ:
        case OPC_BLEZL:
        case OPC_BNE:
        case OPC_BNEL: {
            // offset is in number of instructions, not bytes
            s16 offset = instr.i.immediate;
            offset = -offset;

            return offset == block_length;
        }

        default:
            return false;
    }
}

void v1_compile_new_block(n64_dynarec_block_t* block, bool* code_mask, u64 virtual_address, u32 physical_address) {
    dasm_State** Dst = v1_block_header();

    memset(guest_reg_loaded, 0, sizeof(guest_reg_loaded));
    memset(host_reg_used, 0, sizeof(host_reg_used));

    num_available_host_regs = num_valid_host_regs;

    bool should_continue_block = true;
    int block_length = 0;
    int block_extra_cycles = 0;


    int instructions_left_in_block = -1;

    dynarec_instruction_category_t prev_instr_category = NORMAL;

    bool branch_in_block = false;

    bool block_is_stable = true;
    bool block_is_loop = false;

    do {
        mips_instruction_t instr;
        instr.raw = n64_read_physical_word(physical_address);

        code_mask[BLOCKCACHE_INNER_INDEX(physical_address)] = true;

        block_is_stable &= instruction_stable(instr);

        u32 next_physical_address = physical_address + 4;
        u64 next_virtual_address = virtual_address + 4;

        instructions_left_in_block--;
        bool instr_ends_block;

        u32 extra_cycles = 0;
        dynarec_ir_t* ir = instruction_ir(instr, physical_address);
        if (ir->exception_possible) {
            // save prev_pc
            // TODO will no longer need this when we emit code to check the exceptions
            flush_prev_pc(Dst, virtual_address);
        }
        if (is_branch(ir->category)) {
            flush_pc(Dst, next_virtual_address);
            flush_next_pc(Dst, next_virtual_address + 4);
            clear_branch_flag(Dst);
        }
        switch (ir->format) {
            case CALL_INTERPRETER:
                flush_all(Dst);
                break;
            case FORMAT_NOP:break; // Shouldn't touch any registers, so no need to do anything
            case SHIFT_CONST:
                load_reg_2(Dst, &arg_host_registers[0], instr.r.rt, &dest_host_register, instr.r.rd);
                break;
            case I_TYPE:
                load_reg_2(Dst, &arg_host_registers[0], instr.i.rs, &dest_host_register, instr.i.rt);
                break;
            case R_TYPE:
                load_reg_3(Dst, &arg_host_registers[0], instr.r.rt, &arg_host_registers[1], instr.r.rs, &dest_host_register, instr.r.rd);
                break;
            case J_TYPE:
                logfatal("Allocate regs for J_TYPE");
                break;
            case MF_MULTREG:
                load_reg_1(Dst, &dest_host_register, instr.r.rd);
                break;
            case MT_MULTREG:
                load_reg_1(Dst, &arg_host_registers[0], instr.r.rs);
                break;
        }
        if (ir->exception_possible) {
            set_prev_branch_flag(Dst, prev_instr_category == BRANCH || prev_instr_category == BRANCH_LIKELY);
        }
        ir->compiler(Dst, instr, physical_address, arg_host_registers, dest_host_register, &extra_cycles);
        block_length++;
        block_extra_cycles += extra_cycles;
        if (ir->exception_possible) {
            check_exception(Dst, block_length + block_extra_cycles);
        }
#ifdef N64_DEBUG_MODE
        else {
            check_exception_sanity(Dst, block_length + block_extra_cycles, instr);
        }
#endif

        switch (ir->category) {
            case NORMAL:
                instr_ends_block = instructions_left_in_block == 0;
                break;
            case BRANCH:
                branch_in_block = true;
                advance_pc(Dst);
                if (prev_instr_category == BRANCH || prev_instr_category == BRANCH_LIKELY) {
                    // Check if the previous branch was taken.

                    // If the last branch wasn't taken, we can treat this the same as if the previous instruction wasn't a branch
                    // just set the N64CPU.last_branch_taken to N64CPU.branch_taken and execute the next instruction.

                    // emit:
                    // if (!N64CPU.last_branch_taken) N64CPU.last_branch_taken = N64CPU.branch_taken;
                    logfatal("Branch in a branch delay slot");
                } else {
                    // If the last instruction wasn't a branch, no special behavior is needed. Just set up some state in case the next one is.
                    // emit:
                    // N64CPU.last_branch_taken = N64CPU.branch_taken;
                    //logfatal("unimp");
                }

                instr_ends_block = false;
                instructions_left_in_block = 1; // emit delay slot

                block_is_loop = branch_is_loop(instr, block_length);
                break;

            case BRANCH_LIKELY:
                branch_in_block = true;
                // If the previous instruction was a branch:
                if (prev_instr_category == BRANCH || prev_instr_category == BRANCH_LIKELY) {
                    logfatal("Branch in a branch likely delay slot");
                } else {
                    // TODO: only need to flush all if we exit the block early
                    flush_all(Dst);
                    post_branch_likely(Dst, block_length);
                }

                instr_ends_block = false;
                instructions_left_in_block = 1; // emit delay slot

                block_is_loop = branch_is_loop(instr, block_length);
                break;

            case BLOCK_ENDER:
                branch_in_block = true;
                instr_ends_block = true;
                break;

            case TLB_WRITE:
            case STORE:
                instr_ends_block = true;
                break;

            default:
                logfatal("Unknown dynarec instruction type");
        }

        bool page_boundary_ends_block = IS_PAGE_BOUNDARY(next_physical_address);
        // !!!!!!!!!!!!!!! WARNING !!!!!!!!!!!!!!!
        // If the first instruction in the new page is a delay slot, INCLUDE IT IN THE BLOCK ANYWAY.
        // This DOES BREAK a corner case!
        // If the game overwrites the delay slot but does not overwrite the branch or anything in the other page,
        // THIS BLOCK WILL NOT GET MARKED DIRTY.
        // I highly doubt any games do it, but THIS NEEDS TO GET FIXED AT SOME POINT
        // !!!!!!!!!!!!!!! WARNING !!!!!!!!!!!!!!!
        if (instructions_left_in_block == 1) { page_boundary_ends_block = false; } // FIXME, TODO, BAD, EVIL, etc

        if (instr_ends_block || page_boundary_ends_block) {
#ifdef N64_LOG_COMPILATIONS
            printf("Ending block. instr: %d pb: %d (0x%08X)\n", instr_ends_block, page_boundary_ends_block, next_physical_address);
#endif
            if (!branch_in_block) {
                flush_pc(Dst, next_virtual_address);
                flush_next_pc(Dst, next_virtual_address + 4);
            }
            should_continue_block = false;
        }

        physical_address = next_physical_address;
        virtual_address = next_virtual_address;
        prev_instr_category = ir->category;
    } while (should_continue_block);
    if (block_is_stable && block_is_loop) {
        block_extra_cycles += 64;
    }
    flush_all(Dst);
    end_block(Dst, block_length + block_extra_cycles);
    size_t code_size;
    void* compiled = v1_link_and_encode(Dst, &code_size);
    v1_dasm_free();

    block->run = compiled;
    block->host_size = code_size;
    block->guest_size = block_length * 4;
}

void v1_compiler_init() {
    num_valid_host_regs = 32;
    fill_valid_host_regs(valid_host_regs, &num_valid_host_regs);
}
