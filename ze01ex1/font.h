u8 fonts[41][31] = {
  {'0',0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x0,0x98,0x9,0x81,0x8,0x10,0x81,0x8,0x10,0x81,0x8,0x10,0x80,0x98,0xd,0x80,0xf0,0x0,0x0,0x0,0x0,0x0,0x0},
  {'1',0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x0,0x40,0x4,0x0,0x40,0x4,0x0,0x40,0x4,0x0,0x40,0x4,0x0,0x40,0xc,0x0,0x40,0x0,0x0,0x0,0x0,0x0,0x0},
  {'2',0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0x80,0x88,0xc,0x0,0x40,0x2,0x0,0x10,0x1,0x0,0x18,0x1,0x81,0x18,0x9,0x0,0xe0,0x0,0x0,0x0,0x0,0x0,0x0},
  {'3',0x0,0x0,0x0,0x0,0x0,0x0,0x1e,0x1,0x90,0x1,0x80,0x18,0x1,0x80,0x38,0xf,0x0,0x20,0x1,0x1,0x10,0xb,0x0,0xe0,0x0,0x0,0x0,0x0,0x0,0x0},
  {'4',0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x10,0x1,0x3,0xf8,0x21,0x1,0x10,0x9,0x0,0xd0,0x5,0x0,0x50,0x3,0x0,0x10,0x0,0x0,0x0,0x0,0x0,0x0},
  {'5',0x0,0x0,0x0,0x0,0x0,0x0,0x1e,0x1,0x90,0x1,0x0,0x18,0x1,0x80,0x18,0x7,0x0,0xe0,0xc,0x0,0xc0,0xc,0x0,0x78,0x0,0x0,0x0,0x0,0x0,0x0},
  {'6',0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x0,0x98,0x10,0x81,0x8,0x10,0x81,0x8,0x11,0x80,0xf0,0x8,0x0,0xc0,0x6,0x0,0x18,0x0,0x0,0x0,0x0,0x0,0x0},
  {'7',0x0,0x0,0x0,0x0,0x0,0x0,0x4,0x0,0x40,0x2,0x0,0x20,0x2,0x0,0x10,0x1,0x0,0x10,0x1,0x80,0x18,0x10,0x80,0xf8,0x0,0x0,0x0,0x0,0x0,0x0},
  {'8',0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x1,0x98,0x11,0x81,0x18,0x11,0x80,0xf0,0xe,0x0,0xd0,0x19,0x81,0x18,0x9,0x80,0xf0,0x0,0x0,0x0,0x0,0x0,0x0},
  {'9',0x0,0x0,0x0,0x0,0x0,0x0,0x1c,0x0,0x60,0x1,0x0,0x18,0xf,0x80,0x88,0x10,0x81,0x8,0x10,0x81,0x8,0x9,0x80,0xf0,0x0,0x0,0x0,0x0,0x0,0x0},
  {'.',0x0,0x0,0x0,0x0,0x0,0x0,0xc,0x0,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
  {'%',0x0,0x0,0x0,0x0,0x0,0x1e,0x11,0xb0,0x9b,0xd,0xb0,0x5b,0x5,0xe0,0x20,0x1,0x1,0xd8,0x36,0x83,0x68,0x36,0x43,0x62,0x1c,0x30,0x0,0x0,0x0,0x0},
  {'C',0x0,0x0,0x0,0x0,0x0,0x38,0xc,0x60,0xc2,0xc,0x31,0x80,0x18,0x1,0x80,0x18,0x1,0x80,0xc,0x30,0xc3,0xc,0x73,0x3f,0x30,0x0,0x0,0x0,0x0,0x0},
  {'a',0x0,0x0,0x0,0x0,0x0,0x0,0x7d,0xe3,0x1c,0x11,0x81,0x18,0xf,0x80,0x98,0x9,0x80,0xf0,0xf,0x0,0xf0,0x6,0x0,0x60,0x2,0x0,0x0,0x0,0x0,0x0},
  {'b',0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0x81,0x98,0x18,0xc1,0x8c,0x18,0xc1,0x98,0x1f,0x1,0x98,0x19,0x81,0x98,0x19,0x81,0x98,0x7f,0x0,0x0,0x0,0x0,0x0},
  {'c',0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x1,0x98,0x30,0x83,0x4,0x60,0x6,0x0,0x60,0x6,0x0,0x60,0x3,0x4,0x30,0xc1,0x9c,0xf,0xc0,0x0,0x0,0x0,0x0},
  {'d',0x0,0x0,0x0,0x0,0x0,0x0,0x7e,0x3,0x18,0x31,0x83,0x8,0x30,0xc3,0xc,0x30,0xc3,0xc,0x30,0xc3,0x18,0x31,0x83,0x38,0x7e,0x0,0x0,0x0,0x0,0x0},
  {'e',0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xc1,0x8c,0x18,0xc1,0x84,0x19,0x1,0x90,0x1f,0x1,0x90,0x19,0x1,0x80,0x18,0x81,0x98,0x7f,0x80,0x0,0x0,0x0,0x0},
  {'f',0x0,0x0,0x0,0x0,0x0,0x0,0x7c,0x1,0x80,0x18,0x1,0x80,0x19,0x1,0x90,0x1f,0x1,0x90,0x19,0x1,0x80,0x18,0x81,0x98,0x7f,0x80,0x0,0x0,0x0,0x0},
  {'g',0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x83,0x18,0x61,0x86,0x18,0x61,0x86,0x3e,0x60,0x6,0x0,0x60,0x6,0x8,0x61,0x83,0x18,0xf,0x80,0x0,0x0,0x0,0x0},
  {'h',0x0,0x0,0x0,0x0,0x0,0x0,0x7d,0xf3,0xc,0x30,0xc3,0xc,0x30,0xc3,0xc,0x3f,0xc3,0xc,0x30,0xc3,0xc,0x30,0xc3,0xc,0x7d,0xf0,0x0,0x0,0x0,0x0},
  {'i',0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x80,0x60,0x6,0x0,0x60,0x6,0x0,0x60,0x6,0x0,0x60,0x6,0x0,0x60,0x6,0x0,0x60,0xf,0x80,0x0,0x0,0x0,0x0},
  {'j',0x0,0x0,0x0,0x0,0x0,0x0,0x1c,0x2,0x60,0x33,0x3,0x30,0x3,0x0,0x30,0x3,0x0,0x30,0x3,0x0,0x30,0x3,0x0,0x30,0xf,0x80,0x0,0x0,0x0,0x0},
  {'k',0x0,0x0,0x0,0x0,0x0,0x0,0x3c,0xe1,0x9c,0x19,0x81,0x98,0x1b,0x1,0xe0,0x1e,0x1,0xc0,0x1a,0x1,0x90,0x19,0x81,0x88,0x3d,0xc0,0x0,0x0,0x0,0x0},
  {'l',0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xc1,0x9c,0x18,0xc1,0x84,0x18,0x1,0x80,0x18,0x1,0x80,0x18,0x1,0x80,0x18,0x1,0x80,0x7c,0x0,0x0,0x0,0x0,0x0},
  {'m',0x0,0x0,0x0,0x0,0x0,0x0,0xf5,0xf6,0x46,0x6e,0x66,0xe6,0x6e,0x66,0xd6,0x6d,0x66,0xd6,0x79,0xe7,0x9e,0x70,0xe7,0xe,0xf0,0xf0,0x0,0x0,0x0,0x0},
  {'n',0x0,0x0,0x0,0x0,0x0,0x0,0x78,0x43,0xc,0x21,0xc2,0x1c,0x21,0xc2,0x34,0x26,0x42,0xc4,0x2c,0x42,0xc4,0x38,0x47,0xc,0x71,0xf0,0x0,0x0,0x0,0x0},
  {'o',0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x1,0x98,0x30,0xc2,0x4,0x60,0x66,0x6,0x60,0x66,0x6,0x60,0x63,0x4,0x30,0xc1,0x98,0xf,0x0,0x0,0x0,0x0,0x0},
  {'p',0x0,0x0,0x0,0x0,0x0,0x0,0x3e,0x0,0xc0,0xc,0x0,0xc0,0xc,0x0,0xc0,0xf,0x80,0xd8,0xc,0xc0,0xcc,0xc,0xc0,0xdc,0x3f,0x80,0x0,0x0,0x0,0x0},
  {'q',0x0,0x0,0x1e,0x3,0x80,0x30,0xf,0x1,0x98,0x30,0xc2,0x4,0x60,0x66,0x6,0x60,0x66,0x6,0x60,0x63,0x4,0x30,0xc1,0x98,0xf,0x0,0x0,0x0,0x0,0x0},
  {'r',0x0,0x0,0x0,0x0,0x0,0x0,0x3c,0xf1,0x8c,0x19,0x81,0x98,0x19,0x81,0xb0,0x1e,0x1,0x98,0x19,0x81,0x98,0x19,0x81,0x98,0x3f,0x0,0x0,0x0,0x0,0x0},
  {'s',0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0x1,0x98,0x19,0x81,0x18,0x1,0x80,0x38,0xf,0x80,0xe0,0x1c,0x1,0x88,0x19,0x80,0xd8,0xf,0x80,0x0,0x0,0x0,0x0},
  {'t',0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x80,0x60,0x6,0x0,0x60,0x6,0x0,0x60,0x6,0x0,0x60,0x6,0x0,0x60,0x26,0x43,0x6c,0x3f,0xc0,0x0,0x0,0x0,0x0,},
  {'u',0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x81,0x88,0x30,0x43,0x4,0x30,0x43,0x4,0x30,0x43,0x4,0x30,0x43,0x4,0x30,0x43,0x4,0x7d,0xf0,0x0,0x0,0x0,0x0},
  {'v',0x0,0x0,0x0,0x0,0x0,0x0,0x4,0x0,0x60,0x6,0x0,0xd0,0xd,0x0,0xd0,0xd,0x80,0xd8,0xd,0x81,0x88,0x18,0x83,0x8c,0x7d,0xe0,0x0,0x0,0x0,0x0},
  {'w',0x0,0x0,0x0,0x0,0x0,0x0,0x11,0x81,0x18,0x11,0x82,0x98,0x29,0x82,0x98,0x6e,0x46,0xe4,0x6e,0x46,0xe4,0x44,0x24,0x42,0xe4,0xf0,0x0,0x0,0x0,0x0},
  {'x',0x0,0x0,0x0,0x0,0x0,0x0,0x7b,0xe2,0x18,0x11,0x81,0xb8,0xb,0x0,0xe0,0xe,0x0,0xe0,0xe,0x1,0xd0,0x19,0x83,0x98,0x7d,0xe0,0x0,0x0,0x0,0x0},
  {'y',0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x80,0x60,0x6,0x0,0x60,0x6,0x0,0x60,0x5,0x0,0xd0,0xd,0x80,0xd8,0x8,0x81,0x84,0x3d,0xe0,0x0,0x0,0x0,0x0},
  {'z',0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xc3,0x1c,0x18,0xc1,0x84,0xc,0x0,0xc0,0xe,0x0,0x60,0x3,0x2,0x18,0x31,0x83,0x98,0x3f,0xc0,0x0,0x0,0x0,0x0},
  {' ',0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
  {':',0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xc0,0xc,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xc,0x0,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}
};