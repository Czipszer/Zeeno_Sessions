#include "TestSet.hpp"

std::vector<std::vector<BigInt>> TestSet::data{
    {1},
    {2, 1},
    {3, 10, 5, 16, 8, 4, 2, 1},
    {4, 2, 1},
    {5, 16, 8, 4, 2, 1},
    {6, 3, 10, 5, 16, 8, 4, 2, 1},
    {7, 22, 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1},
    {0x766803a4,  0x3b3401d2, 0x1d9a00e9,  0x58ce02bc, 0x2c67015e,  0x163380af, 0x429a820e, 0x214d4107, 0x63e7c316, 0x31f3e18b,  0x95dba4a2, 0x4aedd251,
     0xe0c976f4,  0x7064bb7a, 0x38325dbd,  0xa8971938, 0x544b8c9c,  0x2a25c64e, 0x1512e327, 0x3f38a976, 0x1f9c54bb, 0x5ed4fe32,  0x2f6a7f19, 0x8e3f7d4c,
     0x471fbea6,  0x238fdf53, 0x6aaf9dfa,  0x3557cefd, 0xa0076cf8,  0x5003b67c, 0x2801db3e, 0x1400ed9f, 0x3c02c8de, 0x1e01646f,  0x5a042d4e, 0x2d0216a7,
     0x870643f6,  0x438321fb, 0xca8965f2,  0x6544b2f9, 0x12fce18ec, 0x97e70c76, 0x4bf3863b, 0xe3da92b2, 0x71ed4959, 0x155c7dc0c, 0xaae3ee06, 0x5571f703,
     0x10055e50a, 0x802af285, 0x18080d790, 0xc0406bc8, 0x602035e4,  0x30101af2, 0x18080d79, 0x4818286c, 0x240c1436, 0x12060a1b,  0x36121e52, 0x1b090f29,
     0x511b2d7c,  0x288d96be, 0x1446cb5f,  0x3cd4621e, 0x1e6a310f,  0x5b3e932e, 0x2d9f4997, 0x88dddcc6, 0x446eee63, 0xcd4ccb2a,  0x66a66595, 0x133f330c0,
     0x99f99860,  0x4cfccc30, 0x267e6618,  0x133f330c, 0x99f9986,   0x4cfccc3,  0xe6f664a,  0x737b325,  0x15a71970, 0xad38cb8,   0x569c65c,  0x2b4e32e,
     0x15a7197,   0x40f54c6,  0x207aa63,   0x616ff2a,  0x30b7f95,   0x9227ec0,  0x4913f60,  0x2489fb0,  0x1244fd8,  0x9227ec,    0x4913f6,   0x2489fb,
     0x6d9df2,    0x36cef9,   0xa46cec,    0x523676,   0x291b3b,    0x7b51b2,   0x3da8d9,   0xb8fa8c,   0x5c7d46,   0x2e3ea3,    0x8abbea,   0x455df5,
     0xd019e0,    0x680cf0,   0x340678,    0x1a033c,   0xd019e,     0x680cf,    0x13826e,   0x9c137,    0x1d43a6,   0xea1d3,     0x2be57a,   0x15f2bd,
     0x41d838,    0x20ec1c,   0x10760e,    0x83b07,    0x18b116,    0xc588b,    0x2509a2,   0x1284d1,   0x378e74,   0x1bc73a,    0xde39d,    0x29aad8,
     0x14d56c,    0xa6ab6,    0x5355b,     0xfa012,    0x7d009,     0x17701c,   0xbb80e,    0x5dc07,    0x119416,   0x8ca0b,     0x1a5e22,   0xd2f11,
     0x278d34,    0x13c69a,   0x9e34d,     0x1da9e8,   0xed4f4,     0x76a7a,    0x3b53d,    0xb1fb8,    0x58fdc,    0x2c7ee,     0x163f7,    0x42be6,
     0x215f3,     0x641da,    0x320ed,     0x962c8,    0x4b164,     0x258b2,    0x12c59,    0x3850c,    0x1c286,    0xe143,      0x2a3ca,    0x151e5,
     0x3f5b0,     0x1fad8,    0xfd6c,      0x7eb6,     0x3f5b,      0xbe12,     0x5f09,     0x11d1c,    0x8e8e,     0x4747,      0xd5d6,     0x6aeb,
     0x140c2,     0xa061,     0x1e124,     0xf092,     0x7849,      0x168dc,    0xb46e,     0x5a37,     0x10ea6,    0x8753,      0x195fa,    0xcafd,
     0x260f8,     0x1307c,    0x983e,      0x4c1f,     0xe45e,      0x722f,     0x1568e,    0xab47,     0x201d6,    0x100eb,     0x302c2,    0x18161,
     0x48424,     0x24212,    0x12109,     0x3631c,    0x1b18e,     0xd8c7,     0x28a56,    0x1452b,    0x3cf82,    0x1e7c1,     0x5b744,    0x2dba2,
     0x16dd1,     0x44974,    0x224ba,     0x1125d,    0x33718,     0x19b8c,    0xcdc6,     0x66e3,     0x134aa,    0x9a55,      0x1cf00,    0xe780,
     0x73c0,      0x39e0,     0x1cf0,      0xe78,      0x73c,       0x39e,      0x1cf,      0x56e,      0x2b7,      0x826,       0x413,      0xc3a,
     0x61d,       0x1258,     0x92c,       0x496,      0x24b,       0x6e2,      0x371,      0xa54,      0x52a,      0x295,       0x7c0,      0x3e0,
     0x1f0,       0xf8,       0x7c,        0x3e,       0x1f,        0x5e,       0x2f,       0x8e,       0x47,       0xd6,        0x6b,       0x142,
     0xa1,        0x1e4,      0xf2,        0x79,       0x16c,       0xb6,       0x5b,       0x112,      0x89,       0x19c,       0xce,       0x67,
     0x136,       0x9b,       0x1d2,       0xe9,       0x2bc,       0x15e,      0xaf,       0x20e,      0x107,      0x316,       0x18b,      0x4a2,
     0x251,       0x6f4,      0x37a,       0x1bd,      0x538,       0x29c,      0x14e,      0xa7,       0x1f6,      0xfb,        0x2f2,      0x179,
     0x46c,       0x236,      0x11b,       0x352,      0x1a9,       0x4fc,      0x27e,      0x13f,      0x3be,      0x1df,       0x59e,      0x2cf,
     0x86e,       0x437,      0xca6,       0x653,      0x12fa,      0x97d,      0x1c78,     0xe3c,      0x71e,      0x38f,       0xaae,      0x557,
     0x1006,      0x803,      0x180a,      0xc05,      0x2410,      0x1208,     0x904,      0x482,      0x241,      0x6c4,       0x362,      0x1b1,
     0x514,       0x28a,      0x145,       0x3d0,      0x1e8,       0xf4,       0x7a,       0x3d,       0xb8,       0x5c,        0x2e,       0x17,
     0x46,        0x23,       0x6a,        0x35,       0xa0,        0x50,       0x28,       0x14,       0xa,        0x5,         0x10,       0x8,
     0x4,         0x2,        0x1},
    {0x3aa2d49057610cbc,
     0x1d516a482bb0865e,
     0xea8b52415d8432f,
     0x2bfa1f6c4188c98e,
     0x15fd0fb620c464c7,
     0x41f72f22624d2e56,
     0x20fb97913126972b,
     0x62f2c6b39373c582,
     0x31796359c9b9e2c1,
     0x946c2a0d5d2da844,
     0x4a361506ae96d422,
     0x251b0a83574b6a11,
     0x6f511f8a05e23e34,
     0x37a88fc502f11f1a,
     0x1bd447e281788f8d,
     0x537cd7a78469aea8,
     0x29be6bd3c234d754,
     0x14df35e9e11a6baa,
     0xa6f9af4f08d35d5,
     0x1f4ed0ded1a7a180,
     0xfa7686f68d3d0c0,
     0x7d3b437b469e860,
     0x3e9da1bda34f430,
     0x1f4ed0ded1a7a18,
     0xfa7686f68d3d0c,
     0x7d3b437b469e86,
     0x3e9da1bda34f43,
     0xbbd8e538e9edca,
     0x5dec729c74f6e5,
     0x119c557d55ee4b0,
     0x8ce2abeaaf7258,
     0x467155f557b92c,
     0x2338aafaabdc96,
     0x119c557d55ee4b,
     0x34d5007801cae2,
     0x1a6a803c00e571,
     0x4f3f80b402b054,
     0x279fc05a01582a,
     0x13cfe02d00ac15,
     0x3b6fa087020440,
     0x1db7d043810220,
     0xedbe821c08110,
     0x76df410e04088,
     0x3b6fa08702044,
     0x1db7d04381022,
     0xedbe821c0811,
     0x2c93b86541834,
     0x1649dc32a0c1a,
     0xb24ee195060d,
     0x216eca4bf1228,
     0x10b76525f8914,
     0x85bb292fc48a,
     0x42dd9497e245,
     0xc898bdc7a6d0,
     0x644c5ee3d368,
     0x32262f71e9b4,
     0x191317b8f4da,
     0xc898bdc7a6d,
     0x259ca3956f48,
     0x12ce51cab7a4,
     0x96728e55bd2,
     0x4b39472ade9,
     0xe1abd5809bc,
     0x70d5eac04de,
     0x386af56026f,
     0xa940e02074e,
     0x54a070103a7,
     0xfde15030af6,
     0x7ef0a81857b,
     0x17cd1f849072,
     0xbe68fc24839,
     0x23b3af46d8ac,
     0x11d9d7a36c56,
     0x8ecebd1b62b,
     0x1ac6c3752282,
     0xd6361ba9141,
     0x282a252fb3c4,
     0x14151297d9e2,
     0xa0a894becf1,
     0x1e1f9be3c6d4,
     0xf0fcdf1e36a,
     0x787e6f8f1b5,
     0x1697b4ead520,
     0xb4bda756a90,
     0x5a5ed3ab548,
     0x2d2f69d5aa4,
     0x1697b4ead52,
     0xb4bda756a9,
     0x21e38f603fc,
     0x10f1c7b01fe,
     0x878e3d80ff,
     0x196aab882fe,
     0xcb555c417f,
     0x2620014c47e,
     0x131000a623f,
     0x393001f26be,
     0x1c9800f935f,
     0x55c802eba1e,
     0x2ae40175d0f,
     0x80ac046172e,
     0x40560230b97,
     0xc10206922c6,
     0x60810349163,
     0x1218309db42a,
     0x90c184eda15,
     0x1b2448ec8e40,
     0xd9224764720,
     0x6c9123b2390,
     0x364891d91c8,
     0x1b2448ec8e4,
     0xd922476472,
     0x6c9123b239,
     0x145b36b16ac,
     0xa2d9b58b56,
     0x516cdac5ab,
     0xf446905102,
     0x7a23482881,
     0x16e69d87984,
     0xb734ec3cc2,
     0x5b9a761e61,
     0x112cf625b24,
     0x8967b12d92,
     0x44b3d896c9,
     0xce1b89c45c,
     0x670dc4e22e,
     0x3386e27117,
     0x9a94a75346,
     0x4d4a53a9a3,
     0xe7defafcea,
     0x73ef7d7e75,
     0x15bce787b60,
     0xade73c3db0,
     0x56f39e1ed8,
     0x2b79cf0f6c,
     0x15bce787b6,
     0xade73c3db,
     0x209b5b4b92,
     0x104dada5c9,
     0x30e908f15c,
     0x18748478ae,
     0xc3a423c57,
     0x24aec6b506,
     0x1257635a83,
     0x37062a0f8a,
     0x1b831507c5,
     0x52893f1750,
     0x29449f8ba8,
     0x14a24fc5d4,
     0xa5127e2ea,
     0x52893f175,
     0xf79bbd460,
     0x7bcddea30,
     0x3de6ef518,
     0x1ef377a8c,
     0xf79bbd46,
     0x7bcddea3,
     0x173699bea,
     0xb9b4cdf5,
     0x22d1e69e0,
     0x1168f34f0,
     0x8b479a78,
     0x45a3cd3c,
     0x22d1e69e,
     0x1168f34f,
     0x343ad9ee,
     0x1a1d6cf7,
     0x4e5846e6,
     0x272c2373,
     0x75846a5a,
     0x3ac2352d,
     0xb0469f88,
     0x58234fc4,
     0x2c11a7e2,
     0x1608d3f1,
     0x421a7bd4,
     0x210d3dea,
     0x10869ef5,
     0x3193dce0,
     0x18c9ee70,
     0xc64f738,
     0x6327b9c,
     0x3193dce,
     0x18c9ee7,
     0x4a5dcb6,
     0x252ee5b,
     0x6f8cb12,
     0x37c6589,
     0xa75309c,
     0x53a984e,
     0x29d4c27,
     0x7d7e476,
     0x3ebf23b,
     0xbc3d6b2,
     0x5e1eb59,
     0x11a5c20c,
     0x8d2e106,
     0x4697083,
     0xd3c518a,
     0x69e28c5,
     0x13da7a50,
     0x9ed3d28,
     0x4f69e94,
     0x27b4f4a,
     0x13da7a5,
     0x3b8f6f0,
     0x1dc7b78,
     0xee3dbc,
     0x771ede,
     0x3b8f6f,
     0xb2ae4e,
     0x595727,
     0x10c0576,
     0x8602bb,
     0x1920832,
     0xc90419,
     0x25b0c4c,
     0x12d8626,
     0x96c313,
     0x1c4493a,
     0xe2249d,
     0x2a66dd8,
     0x15336ec,
     0xa99b76,
     0x54cdbb,
     0xfe6932,
     0x7f3499,
     0x17d9dcc,
     0xbecee6,
     0x5f6773,
     0x11e365a,
     0x8f1b2d,
     0x1ad5188,
     0xd6a8c4,
     0x6b5462,
     0x35aa31,
     0xa0fe94,
     0x507f4a,
     0x283fa5,
     0x78bef0,
     0x3c5f78,
     0x1e2fbc,
     0xf17de,
     0x78bef,
     0x16a3ce,
     0xb51e7,
     0x21f5b6,
     0x10fadb,
     0x32f092,
     0x197849,
     0x4c68dc,
     0x26346e,
     0x131a37,
     0x394ea6,
     0x1ca753,
     0x55f5fa,
     0x2afafd,
     0x80f0f8,
     0x40787c,
     0x203c3e,
     0x101e1f,
     0x305a5e,
     0x182d2f,
     0x48878e,
     0x2443c7,
     0x6ccb56,
     0x3665ab,
     0xa33102,
     0x519881,
     0xf4c984,
     0x7a64c2,
     0x3d3261,
     0xb79724,
     0x5bcb92,
     0x2de5c9,
     0x89b15c,
     0x44d8ae,
     0x226c57,
     0x674506,
     0x33a283,
     0x9ae78a,
     0x4d73c5,
     0xe85b50,
     0x742da8,
     0x3a16d4,
     0x1d0b6a,
     0xe85b5,
     0x2b9120,
     0x15c890,
     0xae448,
     0x57224,
     0x2b912,
     0x15c89,
     0x4159c,
     0x20ace,
     0x10567,
     0x31036,
     0x1881b,
     0x49852,
     0x24c29,
     0x6e47c,
     0x3723e,
     0x1b91f,
     0x52b5e,
     0x295af,
     0x7c10e,
     0x3e087,
     0xba196,
     0x5d0cb,
     0x117262,
     0x8b931,
     0x1a2b94,
     0xd15ca,
     0x68ae5,
     0x13a0b0,
     0x9d058,
     0x4e82c,
     0x27416,
     0x13a0b,
     0x3ae22,
     0x1d711,
     0x58534,
     0x2c29a,
     0x1614d,
     0x423e8,
     0x211f4,
     0x108fa,
     0x847d,
     0x18d78,
     0xc6bc,
     0x635e,
     0x31af,
     0x950e,
     0x4a87,
     0xdf96,
     0x6fcb,
     0x14f62,
     0xa7b1,
     0x1f714,
     0xfb8a,
     0x7dc5,
     0x17950,
     0xbca8,
     0x5e54,
     0x2f2a,
     0x1795,
     0x46c0,
     0x2360,
     0x11b0,
     0x8d8,
     0x46c,
     0x236,
     0x11b,
     0x352,
     0x1a9,
     0x4fc,
     0x27e,
     0x13f,
     0x3be,
     0x1df,
     0x59e,
     0x2cf,
     0x86e,
     0x437,
     0xca6,
     0x653,
     0x12fa,
     0x97d,
     0x1c78,
     0xe3c,
     0x71e,
     0x38f,
     0xaae,
     0x557,
     0x1006,
     0x803,
     0x180a,
     0xc05,
     0x2410,
     0x1208,
     0x904,
     0x482,
     0x241,
     0x6c4,
     0x362,
     0x1b1,
     0x514,
     0x28a,
     0x145,
     0x3d0,
     0x1e8,
     0xf4,
     0x7a,
     0x3d,
     0xb8,
     0x5c,
     0x2e,
     0x17,
     0x46,
     0x23,
     0x6a,
     0x35,
     0xa0,
     0x50,
     0x28,
     0x14,
     0xa,
     0x5,
     0x10,
     0x8,
     0x4,
     0x2,
     0x1}};
