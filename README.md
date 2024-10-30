# Experimental N64
Experimental low-level N64 emulator written in C and a bit of C++.
  
# Features
- Keyboard and gamepad support
- GDB stub for debugging

# Building
For Linux:

1. Install dependencies: SDL2, Vulkan, dbus, and optionally Capstone
2. Run the following commands:
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```
For Windows:

1. Install dependencies: Visual Studio 2019 with the clang workload, vcpkg, CMake.
2. Run the following commands, replacing the vcpkg path with where you installed it:
```bash
vcpkg install sdl2[vulkan]:x64-windows
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -T clangcl -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake ..
cmake --build . --config Release
```

# Running

```
./n64 [OPTION]... [FILE]
n64, a dgb n64 emulator

  -v, --verbose             enables verbose output, repeat up to 4 times for more verbosity
  -h, --help                Display this help message
  -i, --interpreter         Force the use of the interpreter
  -m, --movie               Load movie (Mupen64Plus .m64 format)
  -p, --pif                 Load PIF ROM
```

# Libraries Used
- [DynASM](https://luajit.org/dynasm.html) as the emitter for the dynamic recompiler
- [SDL2](https://www.libsdl.org/) for graphics, audio, and input
- [Capstone](http://www.capstone-engine.org/) as a MIPS disassembler for debugging
- [parallel-rdp](https://github.com/Themaister/parallel-rdp) as the RDP until I write my own
- [Dear Imgui](https://github.com/ocornut/imgui) for the GUI
