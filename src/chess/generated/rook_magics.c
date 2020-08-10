#include "chess/coordinates.h"
#include "chess/find_magics.h"

const struct Magic MAGICS[SQUARES_COUNT] = {
	[00] = { .premask = 0x101010101017eULL,
	         .multiplier = 0x4880053040002280ULL,
	         .rshift = 52,
	         .postmask = 0x0ULL,
	         .start = 0,
	         .end = 4095 },
	[01] = { .premask = 0x202020202027cULL,
	         .multiplier = 0xc009c040002310ULL,
	         .rshift = 52,
	         .postmask = 0x0ULL,
	         .start = 0,
	         .end = 4095 },
	[02] = { .premask = 0x404040404047aULL,
	         .multiplier = 0x220040020000800ULL,
	         .rshift = 52,
	         .postmask = 0x0ULL,
	         .start = 0,
	         .end = 4091 },
	[03] = { .premask = 0x8080808080876ULL,
	         .multiplier = 0x1100125000182004ULL,
	         .rshift = 52,
	         .postmask = 0x0ULL,
	         .start = 0,
	         .end = 4015 },
	[04] = { .premask = 0x1010101010106eULL,
	         .multiplier = 0x424002400a013400ULL,
	         .rshift = 52,
	         .postmask = 0x0ULL,
	         .start = 0,
	         .end = 4089 },
	[05] = { .premask = 0x2020202020205eULL,
	         .multiplier = 0x400a0208810420ULL,
	         .rshift = 52,
	         .postmask = 0x0ULL,
	         .start = 0,
	         .end = 4071 },
	[06] = { .premask = 0x4040404040403eULL,
	         .multiplier = 0x5008221100010040ULL,
	         .rshift = 52,
	         .postmask = 0x0ULL,
	         .start = 0,
	         .end = 4079 },
	[07] = { .premask = 0x8080808080807eULL,
	         .multiplier = 0x920000cc81060024ULL,
	         .rshift = 52,
	         .postmask = 0x0ULL,
	         .start = 0,
	         .end = 4095 },
	[010] = { .premask = 0x1010101017e00ULL,
	          .multiplier = 0x280080004220ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4073 },
	[011] = { .premask = 0x2020202027c00ULL,
	          .multiplier = 0x2a08010c0002008ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4095 },
	[012] = { .premask = 0x4040404047a00ULL,
	          .multiplier = 0x401200880202c00ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4093 },
	[013] = { .premask = 0x8080808087600ULL,
	          .multiplier = 0x91010002c424800ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4047 },
	[014] = { .premask = 0x10101010106e00ULL,
	          .multiplier = 0x1000201000418ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 3583 },
	[015] = { .premask = 0x20202020205e00ULL,
	          .multiplier = 0xa0010840081c0010ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 3832 },
	[016] = { .premask = 0x40404040403e00ULL,
	          .multiplier = 0x812000300a80a41ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4091 },
	[017] = { .premask = 0x80808080807e00ULL,
	          .multiplier = 0x8401000021000082ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4093 },
	[020] = { .premask = 0x10101017e0100ULL,
	          .multiplier = 0x310020009208a0ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4031 },
	[021] = { .premask = 0x20202027c0200ULL,
	          .multiplier = 0x8882011080008ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4092 },
	[022] = { .premask = 0x40404047a0400ULL,
	          .multiplier = 0x8820842000040260ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4085 },
	[023] = { .premask = 0x8080808760800ULL,
	          .multiplier = 0x40c00101028ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4082 },
	[024] = { .premask = 0x101010106e1000ULL,
	          .multiplier = 0x5280010810800800ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4017 },
	[025] = { .premask = 0x202020205e2000ULL,
	          .multiplier = 0x2014008002002400ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 3901 },
	[026] = { .premask = 0x404040403e4000ULL,
	          .multiplier = 0x80624801004ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4087 },
	[027] = { .premask = 0x808080807e8000ULL,
	          .multiplier = 0x904444a001804b00ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4091 },
	[030] = { .premask = 0x101017e010100ULL,
	          .multiplier = 0x2002010602110830ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4092 },
	[031] = { .premask = 0x202027c020200ULL,
	          .multiplier = 0x4103001204e002ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4040 },
	[032] = { .premask = 0x404047a040400ULL,
	          .multiplier = 0x8040010204004ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 3989 },
	[033] = { .premask = 0x8080876080800ULL,
	          .multiplier = 0x4000020700208410ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4095 },
	[034] = { .premask = 0x1010106e101000ULL,
	          .multiplier = 0x108002084420cULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4086 },
	[035] = { .premask = 0x2020205e202000ULL,
	          .multiplier = 0x80024902b0040100ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4094 },
	[036] = { .premask = 0x4040403e404000ULL,
	          .multiplier = 0x4080300802a2100ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 3881 },
	[037] = { .premask = 0x8080807e808000ULL,
	          .multiplier = 0x40408018010020ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4042 },
	[040] = { .premask = 0x1017e01010100ULL,
	          .multiplier = 0x80042000b0400040ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4094 },
	[041] = { .premask = 0x2027c02020200ULL,
	          .multiplier = 0x210010012520042ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4094 },
	[042] = { .premask = 0x4047a04040400ULL,
	          .multiplier = 0x85000206100ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 3916 },
	[043] = { .premask = 0x8087608080800ULL,
	          .multiplier = 0x40610307001000ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4093 },
	[044] = { .premask = 0x10106e10101000ULL,
	          .multiplier = 0x141080004080880ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 3403 },
	[045] = { .premask = 0x20205e20202000ULL,
	          .multiplier = 0x10009100385ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4087 },
	[046] = { .premask = 0x40403e40404000ULL,
	          .multiplier = 0x88c0100023aULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 3879 },
	[047] = { .premask = 0x80807e80808000ULL,
	          .multiplier = 0x28829220000a4ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4095 },
	[050] = { .premask = 0x17e0101010100ULL,
	          .multiplier = 0x10400200a2382000ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4095 },
	[051] = { .premask = 0x27c0202020200ULL,
	          .multiplier = 0x2151200800102000ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4095 },
	[052] = { .premask = 0x47a0404040400ULL,
	          .multiplier = 0x1000100240504208ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4091 },
	[053] = { .premask = 0x8760808080800ULL,
	          .multiplier = 0x22440002188010a1ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4039 },
	[054] = { .premask = 0x106e1010101000ULL,
	          .multiplier = 0x101020088088800ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4095 },
	[055] = { .premask = 0x205e2020202000ULL,
	          .multiplier = 0x480180030805ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4093 },
	[056] = { .premask = 0x403e4040404000ULL,
	          .multiplier = 0x20003120894ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4095 },
	[057] = { .premask = 0x807e8080808000ULL,
	          .multiplier = 0x882a000408001ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4094 },
	[060] = { .premask = 0x7e010101010100ULL,
	          .multiplier = 0x4000206040100020ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 3593 },
	[061] = { .premask = 0x7c020202020200ULL,
	          .multiplier = 0x80c0021c01104420ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4094 },
	[062] = { .premask = 0x7a040404040400ULL,
	          .multiplier = 0x2480820004410801ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 3835 },
	[063] = { .premask = 0x76080808080800ULL,
	          .multiplier = 0x2100080100aULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 3995 },
	[064] = { .premask = 0x6e101010101000ULL,
	          .multiplier = 0x80010240a4100ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 3935 },
	[065] = { .premask = 0x5e202020202000ULL,
	          .multiplier = 0x2080408401448020ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 3534 },
	[066] = { .premask = 0x3e404040404000ULL,
	          .multiplier = 0x1018001240940ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4094 },
	[067] = { .premask = 0x7e808080808000ULL,
	          .multiplier = 0x408c00804002208ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4095 },
	[070] = { .premask = 0x7e01010101010100ULL,
	          .multiplier = 0x402008900403022ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4095 },
	[071] = { .premask = 0x7c02020202020200ULL,
	          .multiplier = 0x102801040618aULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4094 },
	[072] = { .premask = 0x7a04040404040400ULL,
	          .multiplier = 0x100882002042ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4095 },
	[073] = { .premask = 0x7608080808080800ULL,
	          .multiplier = 0x102200400802ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4094 },
	[074] = { .premask = 0x6e10101010101000ULL,
	          .multiplier = 0x81200200100aULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4093 },
	[075] = { .premask = 0x5e20202020202000ULL,
	          .multiplier = 0x82000090010806ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4095 },
	[076] = { .premask = 0x3e40404040404000ULL,
	          .multiplier = 0x202880844008102ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4090 },
	[077] = { .premask = 0x7e80808080808000ULL,
	          .multiplier = 0x100a83040421c2ULL,
	          .rshift = 52,
	          .postmask = 0x0ULL,
	          .start = 0,
	          .end = 4095 },
};
