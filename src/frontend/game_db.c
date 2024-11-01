#include "game_db.h"

static const gamedb_entry_t gamedb[] = {
        {"NNM", "E",        SAVE_NONE,        "Namco Museum 64"},
        {"NDM", "E",        SAVE_NONE,        "Doom 64"},
        {"NGN", "E",        SAVE_EEPROM_4k,   "GoldenEye 007"},
        // Copied from CEN64 with small edits: https://github.com/n64dev/cen64/blob/master/device/cart_db.c
        {"CFZ", "EJ",       SAVE_SRAM_256k,  "F-Zero X (NTSC)"},
        {"CLB", "EJ",       SAVE_EEPROM_4k,  "Mario Party (NTSC)"},
        {"CP2", "J",        SAVE_FLASH_1m,   "Pokémon Stadium 2 (Japan)"},
        {"CPS", "J",        SAVE_SRAM_256k,  "Pokémon Stadium (Japan)"},
        {"CZL", "EJ",       SAVE_SRAM_256k,  "Legend of Zelda: Ocarina of Time (NTSC)"},
        {"N3D", "J",        SAVE_EEPROM_16k, "Doraemon 3: Nobita no Machi SOS!"},
        {"N3H", "J",        SAVE_SRAM_256k,  "Ganbare! Nippon! Olympics 2000"},
        {"NA2", "J",        SAVE_SRAM_256k,  "Virtual Pro Wrestling 2"},
        {"NAB", "JP",       SAVE_EEPROM_4k,  "Air Boarder 64"},
        {"NAD", "E",        SAVE_EEPROM_4k,  "Worms Armageddon (USA)"},
        {"NAF", "J",        SAVE_FLASH_1m,   "Doubutsu no Mori"},
        {"NAG", "EJP",      SAVE_EEPROM_4k,  "AeroGauge"},
        {"NAL", "EJPU",     SAVE_SRAM_256k,  "Super Smash Bros"},
        {"NB5", "J",        SAVE_SRAM_256k,  "Biohazard 2"},
        {"NB6", "J",        SAVE_EEPROM_4k,  "Super B-Daman: Battle Phoenix 64"},
        {"NB7", "EJPU",     SAVE_EEPROM_16k, "Banjo-Tooie"},
        {"NBC", "EJP",      SAVE_EEPROM_4k,  "Blast Corps"},
        {"NBD", "EJP",      SAVE_EEPROM_4k,  "Bomberman Hero"},
        {"NBH", "EP",       SAVE_EEPROM_4k,  "Body Harvest"},
        {"NBK", "EJP",      SAVE_EEPROM_4k,  "Banjo-Kazooie"},
        {"NBM", "EJP",      SAVE_EEPROM_4k,  "Bomberman 64"},
        {"NBN", "J",        SAVE_EEPROM_4k,  "Bakuretsu Muteki Bangaioh"},
        {"NBV", "EJ",       SAVE_EEPROM_4k,  "Bomberman 64: The Second Attack!"},
        {"NCC", "DEP",      SAVE_FLASH_1m,   "Command & Conquer"},
        {"NCG", "J",        SAVE_EEPROM_4k,  "Choro Q 64 2: Hacha-Mecha Grand Prix Race"},
        {"NCH", "EP",       SAVE_EEPROM_4k,  "Chopper Attack"},
        {"NCK", "E",        SAVE_FLASH_1m,   "NBA Courtside 2"},
        {"NCR", "EJP",      SAVE_EEPROM_4k,  "Penny Racers"},
        {"NCT", "EJP",      SAVE_EEPROM_4k,  "Chameleon Twist"},
        {"NCU", "EP",       SAVE_EEPROM_4k,  "Cruis'n USA"},
        {"NCW", "EP",       SAVE_EEPROM_16k, "Cruis'n World"},
        {"NCX", "J",        SAVE_EEPROM_4k,  "Custom Robo"},
        {"NCZ", "J",        SAVE_EEPROM_16k, "Custom Robo V2"},
        {"ND2", "J",        SAVE_EEPROM_16k, "Doraemon 2: Nobita to Hikari no Shinden"},
        {"ND3", "J",        SAVE_EEPROM_16k, "Akumajou Dracula Mokushiroku"},
        {"ND4", "J",        SAVE_EEPROM_16k, "Akumajou Dracula Mokushiroku Gaiden: Legend of Cornell"},
        {"ND6", "J",        SAVE_EEPROM_16k, "Densha de Go! 64"},
        {"NDA", "J",        SAVE_FLASH_1m,   "Derby Stallion 64"},
        {"NDK", "J",        SAVE_EEPROM_4k,  "Space Dynamites"},
        {"NDO", "EJP",      SAVE_EEPROM_16k, "Donkey Kong 64"},
        {"NDP", "E",        SAVE_FLASH_1m,   "Dinosaur Planet"},
        {"NDR", "J",        SAVE_EEPROM_4k,  "Doraemon: Nobita to 3tsu no Seireiseki"},
        {"NDU", "EP",       SAVE_EEPROM_4k,  "Duck Dodgers"},
        {"NDY", "EJP",      SAVE_EEPROM_4k,  "Diddy Kong Racing"},
        {"NEA", "EP",       SAVE_EEPROM_4k,  "PGA European Tour"},
        {"NEP", "EJP",      SAVE_EEPROM_16k, "Star Wars Episode I: Racer"},
        {"NER", "E",        SAVE_EEPROM_4k,  "AeroFighters Assault (USA)"},
        {"NEV", "J",        SAVE_EEPROM_16k, "Neon Genesis Evangelion"},
        {"NF2", "P",        SAVE_EEPROM_4k,  "F-1 World Grand Prix II"},
        {"NFG", "E",        SAVE_EEPROM_4k,  "Fighter Destiny 2"},
        {"NFH", "EP",       SAVE_EEPROM_4k,  "Bass Hunter 64"},
        {"NFU", "EP",       SAVE_EEPROM_16k, "Conker's Bad Fur Day"},
        {"NFW", "DEFJP",    SAVE_EEPROM_4k,  "F-1 World Grand Prix"},
        {"NFX", "EJPU",     SAVE_EEPROM_4k,  "Star Fox 64"},
        {"NFY", "J",        SAVE_EEPROM_4k,  "Kakutou Denshou: F-Cup Maniax"},
        {"NFZ", "P",        SAVE_SRAM_256k,  "F-Zero X (PAL)"},
        {"NG6", "J",        SAVE_SRAM_256k,  "Ganbare Goemon: Dero Dero Douchuu Obake Tenkomori"},
        {"NGC", "EP",       SAVE_EEPROM_16k, "GT 64: Championship Edition"},
        {"NGE", "EJP",      SAVE_EEPROM_4k,  "GoldenEye 007"},
        {"NGL", "J",        SAVE_EEPROM_4k,  "Getter Love!!"},
        {"NGP", "J",        SAVE_SRAM_256k,  "Goemon: Mononoke Sugoroku"},
        {"NGT", "J",        SAVE_EEPROM_16k, "City-Tour GP: Zen-Nihon GT Senshuken"},
        {"NGU", "J",        SAVE_EEPROM_4k,  "Tsumi to Batsu: Hoshi no Keishousha"},
        {"NGV", "EP",       SAVE_EEPROM_4k,  "Glover"},
        {"NHA", "J",        SAVE_EEPROM_4k,  "Bomber Man 64 (Japan)"},
        {"NHF", "J",        SAVE_EEPROM_4k,  "64 Hanafuda: Tenshi no Yakusoku"},
        {"NHP", "J",        SAVE_EEPROM_4k,  "Heiwa Pachinko World 64"},
        {"NHY", "J",        SAVE_SRAM_256k,  "Hybrid Heaven (Japan)"},
        {"NIB", "J",        SAVE_SRAM_256k,  "Itoi Shigesato no Bass Tsuri No. 1 Kettei Ban!"},
        {"NIC", "E",        SAVE_EEPROM_4k,  "Indy Racing 2000"},
        {"NIJ", "EP",       SAVE_EEPROM_4k,  "Indiana Jones and the Infernal Machine"},
        {"NIM", "J",        SAVE_EEPROM_16k, "Ide Yosuke no Mahjong Juku"},
        {"NIR", "J",        SAVE_EEPROM_4k,  "Utchan Nanchan no Hono no Challenger: Denryuu Ira Ira Bou"},
        {"NJ5", "J",        SAVE_SRAM_256k,  "Jikkyou Powerful Pro Yakyuu 5"},
        {"NJD", "E",        SAVE_FLASH_1m,   "Jet Force Gemini (Kiosk Demo)"},
        {"NJF", "EJP",      SAVE_FLASH_1m,   "Jet Force Gemini"},
        {"NJG", "J",        SAVE_SRAM_256k,  "Jinsei Game 64"},
        {"NJM", "EP",       SAVE_EEPROM_4k,  "Earthworm Jim 3D"},
        {"NK2", "EJP",      SAVE_EEPROM_4k,  "Snowboard Kids 2"},
        {"NK4", "EJP",      SAVE_EEPROM_16k, "Kirby 64: The Crystal Shards"},
        {"NKA", "DEFJP",    SAVE_EEPROM_4k,  "Fighters Destiny"},
        {"NKG", "EP",       SAVE_SRAM_256k,  "MLB featuring Ken Griffey Jr."},
        {"NKI", "EP",       SAVE_EEPROM_4k,  "Killer Instinct Gold"},
        {"NKJ", "E",        SAVE_FLASH_1m,   "Ken Griffey Jr.'s Slugfest"},
        {"NKT", "EJP",      SAVE_EEPROM_4k,  "Mario Kart 64"},
        {"NLB", "P",        SAVE_EEPROM_4k,  "Mario Party (PAL)"},
        {"NLL", "J",        SAVE_EEPROM_4k,  "Last Legion UX"},
        {"NLR", "EJP",      SAVE_EEPROM_4k,  "Lode Runner 3D"},
        {"NM6", "E",        SAVE_FLASH_1m,   "Mega Man 64"},
        {"NM8", "EJP",      SAVE_EEPROM_16k, "Mario Tennis"},
        {"NMF", "EJP",      SAVE_SRAM_256k,  "Mario Golf"},
        {"NMG", "DEP",      SAVE_EEPROM_4k,  "Monaco Grand Prix"},
        {"NMI", "DEFIPS",   SAVE_EEPROM_4k,  "Mission: Impossible"},
        {"NML", "EJP",      SAVE_EEPROM_4k,  "Mickey's Speedway USA"},
        {"NMO", "E",        SAVE_EEPROM_4k,  "Monopoly"},
        {"NMQ", "EJP",      SAVE_FLASH_1m,   "Paper Mario"},
        {"NMR", "EJP",      SAVE_EEPROM_4k,  "Multi Racing Championship"},
        {"NMS", "J",        SAVE_EEPROM_4k,  "Morita Shougi 64"},
        {"NMU", "E",        SAVE_EEPROM_4k,  "Big Mountain 2000"},
        {"NMV", "EJP",      SAVE_EEPROM_16k, "Mario Party 3"},
        {"NMW", "EJP",      SAVE_EEPROM_4k,  "Mario Party 2"},
        {"NMX", "EJP",      SAVE_EEPROM_16k, "Excitebike 64"},
        {"NN6", "E",        SAVE_EEPROM_4k,  "Dr. Mario 64"},
        {"NNA", "EP",       SAVE_EEPROM_4k,  "Star Wars Episode I: Battle for Naboo"},
        {"NNB", "EP",       SAVE_EEPROM_16k, "Kobe Bryant in NBA Courtside"},
        {"NOB", "EJ",       SAVE_SRAM_256k,  "Ogre Battle 64: Person of Lordly Caliber"},
        {"NOS", "J",        SAVE_EEPROM_4k,  "64 Oozumou"},
        {"NP2", "J",        SAVE_EEPROM_4k,  "Chou Kuukan Nighter Pro Yakyuu King 2"},
        {"NP3", "DEFIJPS",  SAVE_FLASH_1m,   "Pokémon Stadium 2"},
        {"NP6", "J",        SAVE_SRAM_256k,  "Jikkyou Powerful Pro Yakyuu 6"},
        {"NPA", "J",        SAVE_SRAM_256k,  "Jikkyou Powerful Pro Yakyuu 2000"},
        {"NPD", "EJP",      SAVE_EEPROM_16k, "Perfect Dark"},
        {"NPE", "J",        SAVE_SRAM_256k,  "Jikkyou Powerful Pro Yakyuu Basic Ban 2001"},
        {"NPF", "DEFIJPSU", SAVE_FLASH_1m,   "Pokémon Snap"},
        {"NPG", "EJ",       SAVE_EEPROM_4k,  "Hey You, Pikachu!"},
        {"NPH", "E",        SAVE_FLASH_1m,   "Pokémon Snap Station (Kiosk Demo)"},
        {"NPM", "P",        SAVE_SRAM_256k,  "Premier Manager 64"},
        {"NPN", "DEFP",     SAVE_FLASH_1m,   "Pokémon Puzzle League"},
        {"NPO", "DEFIPS",   SAVE_FLASH_1m,   "Pokémon Stadium (USA, PAL)"},
        {"NPP", "J",        SAVE_EEPROM_16k, "Parlor! Pro 64: Pachinko Jikki Simulation Game"},
        {"NPS", "J",        SAVE_SRAM_256k,  "Jikkyou J.League 1999: Perfect Striker 2"},
        {"NPT", "J",        SAVE_EEPROM_4k,  "Puyo Puyon Party"},
        {"NPW", "EJP",      SAVE_EEPROM_4k,  "Pilotwings 64"},
        {"NPY", "J",        SAVE_EEPROM_4k,  "Puyo Puyo Sun 64"},
        {"NR7", "J",        SAVE_EEPROM_16k, "Robot Poncots 64: 7tsu no Umi no Caramel"},
        {"NRA", "J",        SAVE_EEPROM_4k,  "Rally '99"},
        {"NRC", "EJP",      SAVE_EEPROM_4k,  "Top Gear Overdrive"},
        {"NRE", "EP",       SAVE_SRAM_256k,  "Resident Evil 2"},
        {"NRH", "J",        SAVE_FLASH_1m,   "Rockman Dash"},
        {"NRI", "EP",       SAVE_SRAM_256k,  "The New Tetris"},
        {"NRS", "EJP",      SAVE_EEPROM_4k,  "Star Wars: Rogue Squadron"},
        {"NRZ", "EP",       SAVE_EEPROM_16k, "Ridge Racer 64"},
        {"NS4", "J",        SAVE_SRAM_256k,  "Super Robot Taisen 64"},
        {"NS6", "EJ",       SAVE_EEPROM_4k,  "Star Soldier: Vanishing Earth"},
        {"NSA", "JP",       SAVE_EEPROM_4k,  "AeroFighters Assault (PAL, Japan)"},
        {"NSC", "EP",       SAVE_EEPROM_4k,  "Starshot: Space Circus Fever"},
        {"NSI", "J",        SAVE_SRAM_256k,  "Fushigi no Dungeon: Fuurai no Shiren 2"},
        {"NSM", "EJP",      SAVE_EEPROM_4k,  "Super Mario 64"},
        {"NSN", "J",        SAVE_EEPROM_4k,  "Snow Speeder"},
        {"NSQ", "EP",       SAVE_FLASH_1m,   "StarCraft 64"},
        {"NSS", "J",        SAVE_EEPROM_4k,  "Super Robot Spirits"},
        {"NSU", "EP",       SAVE_EEPROM_4k,  "Rocket: Robot on Wheels"},
        {"NSV", "EP",       SAVE_EEPROM_4k,  "SpaceStation Silicon Valley"},
        {"NSW", "EJP",      SAVE_EEPROM_4k,  "Star Wars: Shadows of the Empire"},
        {"NT3", "J",        SAVE_SRAM_256k,  "Toukon Road 2"},
        {"NT6", "J",        SAVE_EEPROM_4k,  "Tetris 64"},
        {"NT9", "EP",       SAVE_FLASH_1m,   "Tigger's Honey Hunt"},
        {"NTB", "J",        SAVE_EEPROM_4k,  "Transformers: Beast Wars Metals 64"},
        {"NTC", "J",        SAVE_EEPROM_4k,  "64 Trump Collection"},
        {"NTE", "AP",       SAVE_SRAM_256k,  "1080 Snowboarding"},
        {"NTJ", "EP",       SAVE_EEPROM_4k,  "Tom and Jerry in Fists of Furry"},
        {"NTM", "EJP",      SAVE_EEPROM_4k,  "Mischief Makers"},
        {"NTN", "EP",       SAVE_EEPROM_4k,  "All-Star Tennis 99"},
        {"NTP", "EP",       SAVE_EEPROM_4k,  "Tetrisphere"},
        {"NTR", "JP",       SAVE_EEPROM_4k,  "Top Gear Rally (PAL, Japan)"},
        {"NTW", "J",        SAVE_EEPROM_4k,  "64 de Hakken!! Tamagotchi"},
        {"NTX", "EP",       SAVE_EEPROM_4k,  "Taz Express"},
        {"NUB", "J",        SAVE_EEPROM_16k, "PD Ultraman Battle Collection 64"},
        {"NUM", "J",        SAVE_SRAM_256k,  "Nushi Zuri 64: Shiokaze ni Notte"},
        {"NUT", "J",        SAVE_SRAM_256k,  "Nushi Zuri 64"},
        {"NVB", "J",        SAVE_SRAM_256k,  "Bass Rush: ECOGEAR PowerWorm Championship"},
        {"NVL", "EP",       SAVE_EEPROM_4k,  "V-Rally 99 (USA, PAL)"},
        {"NVP", "J",        SAVE_SRAM_256k,  "Virtual Pro Wrestling 64"},
        {"NVY", "J",        SAVE_EEPROM_4k,  "V-Rally 99 (Japan)"},
        {"NW2", "EP",       SAVE_SRAM_256k,  "WCW/nWo Revenge"},
        {"NW4", "EP",       SAVE_FLASH_1m,   "WWF No Mercy"},
        {"NWC", "J",        SAVE_EEPROM_4k,  "Wild Choppers"},
        {"NWL", "EP",       SAVE_SRAM_256k,  "Waialae Country Club: True Golf Classics"},
        {"NWQ", "E",        SAVE_EEPROM_4k,  "Rally Challenge 2000"},
        {"NWR", "EJP",      SAVE_EEPROM_4k,  "Wave Race 64"},
        {"NWT", "J",        SAVE_EEPROM_4k,  "Wetrix (Japan)"},
        {"NWU", "P",        SAVE_EEPROM_4k,  "Worms Armageddon (PAL)"},
        {"NWX", "EJP",      SAVE_SRAM_256k,  "WWF WrestleMania 2000"},
        {"NXO", "E",        SAVE_EEPROM_4k,  "Cruis'n Exotica"},
        {"NYK", "J",        SAVE_EEPROM_4k,  "Yakouchuu II: Satsujin Kouro"},
        {"NYS", "EJP",      SAVE_EEPROM_16k, "Yoshi's Story"},
        {"NYW", "EJ",       SAVE_SRAM_256k,  "Harvest Moon 64"},
        {"NZL", "P",        SAVE_SRAM_256k,  "Legend of Zelda: Ocarina of Time (PAL)"},
        {"NZS", "EJP",      SAVE_FLASH_1m,   "Legend of Zelda: Majora's Mask"},
};

#define GAMEDB_SIZE (sizeof(gamedb) / sizeof(gamedb_entry_t))

// Special case for Japanese Kirby 64, which has different save types for different revisions
// (thanks CEN64)
void check_kirby_special_case(n64_system_t* system) {
    n64_rom_t* rom = &system->mem.rom;
    if (strcmp(rom->code, "NK4") == 0) {
        if(rom->rom[0x3E] == 'J' && rom->rom[0x3F] < 2){
            logalways("This looks like an early revision of Japanese Kirby 64, using SRAM instead of EEPROM!");
            system->mem.save_type = SAVE_SRAM_256k;
        }
    }
}

void gamedb_match(n64_system_t* system) {
    n64_rom_t* rom = &system->mem.rom;
    for (int i = 0; i < GAMEDB_SIZE; i++) {
        bool matches_code = strcmp(gamedb[i].code, rom->code) == 0;
        bool matches_region = false;

        for (int j = 0; j < strlen(gamedb[i].regions) && !matches_region; j++) {
            if (gamedb[i].regions[j] == rom->header.country_code[0]) {
                matches_region = true;
            }
        }

        if (matches_code) {
            if (matches_region) {
                system->mem.save_type = gamedb[i].save_type;
                system->mem.rom.game_name_db = gamedb[i].name;
                check_kirby_special_case(system);
                logalways("Loaded %s", gamedb[i].name);
                return;
            } else {
                logwarn("Matched code for %s, but not region! Game supposedly exists in regions [%s] but this image has region %c",
                        gamedb[i].name, gamedb[i].regions, rom->header.country_code[0]);
            }
        }

    }

    logalways("Did not match any Game DB entries. Code: %s Region: %c", system->mem.rom.code, system->mem.rom.header.country_code[0]);

    system->mem.rom.game_name_db = NULL;
    system->mem.save_type = SAVE_NONE;
}
