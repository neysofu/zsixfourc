use crate::chess::*;

pub static KING_ATTACKS: [BitBoard; Square::count()] = [
    0x0000_0000_0000_0302,
    0x0000_0000_0000_0705,
    0x0000_0000_0000_0e0a,
    0x0000_0000_0000_1c14,
    0x0000_0000_0000_3828,
    0x0000_0000_0000_7050,
    0x0000_0000_0000_e0a0,
    0x0000_0000_0000_c040,
    0x0000_0000_0003_0203,
    0x0000_0000_0007_0507,
    0x0000_0000_000e_0a0e,
    0x0000_0000_001c_141c,
    0x0000_0000_0038_2838,
    0x0000_0000_0070_5070,
    0x0000_0000_00e0_a0e0,
    0x0000_0000_00c0_40c0,
    0x0000_0000_0302_0300,
    0x0000_0000_0705_0700,
    0x0000_0000_0e0a_0e00,
    0x0000_0000_1c14_1c00,
    0x0000_0000_3828_3800,
    0x0000_0000_7050_7000,
    0x0000_0000_e0a0_e000,
    0x0000_0000_c040_c000,
    0x0000_0003_0203_0000,
    0x0000_0007_0507_0000,
    0x0000_000e_0a0e_0000,
    0x0000_001c_141c_0000,
    0x0000_0038_2838_0000,
    0x0000_0070_5070_0000,
    0x0000_00e0_a0e0_0000,
    0x0000_00c0_40c0_0000,
    0x0000_0302_0300_0000,
    0x0000_0705_0700_0000,
    0x0000_0e0a_0e00_0000,
    0x0000_1c14_1c00_0000,
    0x0000_3828_3800_0000,
    0x0000_7050_7000_0000,
    0x0000_e0a0_e000_0000,
    0x0000_c040_c000_0000,
    0x0003_0203_0000_0000,
    0x0007_0507_0000_0000,
    0x000e_0a0e_0000_0000,
    0x001c_141c_0000_0000,
    0x0038_2838_0000_0000,
    0x0070_5070_0000_0000,
    0x00e0_a0e0_0000_0000,
    0x00c0_40c0_0000_0000,
    0x0302_0300_0000_0000,
    0x0705_0700_0000_0000,
    0x0e0a_0e00_0000_0000,
    0x1c14_1c00_0000_0000,
    0x3828_3800_0000_0000,
    0x7050_7000_0000_0000,
    0xe0a0_e000_0000_0000,
    0xc040_c000_0000_0000,
    0x0203_0000_0000_0000,
    0x0507_0000_0000_0000,
    0x0a0e_0000_0000_0000,
    0x141c_0000_0000_0000,
    0x2838_0000_0000_0000,
    0x5070_0000_0000_0000,
    0xa0e0_0000_0000_0000,
    0x40c0_0000_0000_0000,
];
