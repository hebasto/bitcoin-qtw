/**********************************************************************
 * Copyright (c) 2018 Pieter Wuille, Greg Maxwell, Gleb Naumenko      *
 * Distributed under the MIT software license, see the accompanying   *
 * file LICENSE or http://www.opensource.org/licenses/mit-license.php.*
 **********************************************************************/

/* This file was substantially auto-generated by doc/gen_params.sage. */
#include "../fielddefines.h"

#if defined(ENABLE_FIELD_BYTES_INT_5)

#include "generic_common_impl.h"

#include "../lintrans.h"
#include "../sketch_impl.h"

#endif

#include "../sketch.h"

namespace {
#ifdef ENABLE_FIELD_INT_33
// 33 bit field
typedef RecLinTrans<uint64_t, 6, 6, 6, 5, 5, 5> StatTable33;
typedef RecLinTrans<uint64_t, 4, 4, 4, 4, 4, 4, 3, 3, 3> DynTable33;
constexpr StatTable33 SQR_TABLE_33({0x1, 0x4, 0x10, 0x40, 0x100, 0x400, 0x1000, 0x4000, 0x10000, 0x40000, 0x100000, 0x400000, 0x1000000, 0x4000000, 0x10000000, 0x40000000, 0x100000000, 0x802, 0x2008, 0x8020, 0x20080, 0x80200, 0x200800, 0x802000, 0x2008000, 0x8020000, 0x20080000, 0x80200000, 0x800401, 0x2001004, 0x8004010, 0x20010040, 0x80040100});
constexpr StatTable33 QRT_TABLE_33({0xba504dd4, 0x1e2798ef2, 0x1e2798ef0, 0x6698a4ec, 0x1e2798ef4, 0x1c7f1bef0, 0x6698a4e4, 0x16da1b384, 0x1e2798ee4, 0x661ca6ec, 0x1c7f1bed0, 0x1483b87a6, 0x6698a4a4, 0x800000, 0x16da1b304, 0x1a185101c, 0x1e2798fe4, 0xaa400954, 0x661ca4ec, 0x667caeec, 0x1c7f1bad0, 0x400800, 0x1483b8fa6, 0, 0x6698b4a4, 0x1c61da4b8, 0x802000, 0x16e5dadec, 0x16da1f304, 0x62fc8eec, 0x1a185901c, 0x1661da5ec, 0x1e2788fe4});
typedef Field<uint64_t, 33, 1025, StatTable33, DynTable33, &SQR_TABLE_33, &QRT_TABLE_33> Field33;
#endif

#ifdef ENABLE_FIELD_INT_34
// 34 bit field
typedef RecLinTrans<uint64_t, 6, 6, 6, 6, 5, 5> StatTable34;
typedef RecLinTrans<uint64_t, 4, 4, 4, 4, 4, 4, 4, 3, 3> DynTable34;
constexpr StatTable34 SQR_TABLE_34({0x1, 0x4, 0x10, 0x40, 0x100, 0x400, 0x1000, 0x4000, 0x10000, 0x40000, 0x100000, 0x400000, 0x1000000, 0x4000000, 0x10000000, 0x40000000, 0x100000000, 0x81, 0x204, 0x810, 0x2040, 0x8100, 0x20400, 0x81000, 0x204000, 0x810000, 0x2040000, 0x8100000, 0x20400000, 0x81000000, 0x204000000, 0x10000102, 0x40000408, 0x100001020});
constexpr StatTable34 QRT_TABLE_34({0x2f973a1f6, 0x40202, 0x40200, 0x348102060, 0x40204, 0x8000420, 0x348102068, 0x1092195c8, 0x40214, 0x3f6881b6e, 0x8000400, 0x3f810383e, 0x348102028, 0x340002068, 0x109219548, 0x24015a774, 0x40314, 0x3f050343e, 0x3f688196e, 0x3f81c3a3a, 0x8000000, 0x24031a560, 0x3f810303e, 0xb08c1a12, 0x348103028, 0xb2881906, 0x340000068, 0, 0x10921d548, 0x2e131e576, 0x240152774, 0x18921d55e, 0x50314, 0x14015271c});
typedef Field<uint64_t, 34, 129, StatTable34, DynTable34, &SQR_TABLE_34, &QRT_TABLE_34> Field34;
#endif

#ifdef ENABLE_FIELD_INT_35
// 35 bit field
typedef RecLinTrans<uint64_t, 6, 6, 6, 6, 6, 5> StatTable35;
typedef RecLinTrans<uint64_t, 4, 4, 4, 4, 4, 4, 4, 4, 3> DynTable35;
constexpr StatTable35 SQR_TABLE_35({0x1, 0x4, 0x10, 0x40, 0x100, 0x400, 0x1000, 0x4000, 0x10000, 0x40000, 0x100000, 0x400000, 0x1000000, 0x4000000, 0x10000000, 0x40000000, 0x100000000, 0x400000000, 0xa, 0x28, 0xa0, 0x280, 0xa00, 0x2800, 0xa000, 0x28000, 0xa0000, 0x280000, 0xa00000, 0x2800000, 0xa000000, 0x28000000, 0xa0000000, 0x280000000, 0x200000005});
constexpr StatTable35 QRT_TABLE_35({0x5c2038114, 0x2bf547ee8, 0x2bf547eea, 0x2bf1074e8, 0x2bf547eee, 0x1883d0736, 0x2bf1074e0, 0x100420, 0x2bf547efe, 0x400800, 0x1883d0716, 0x5e90e4a0, 0x2bf1074a0, 0x4e70ac20, 0x1004a0, 0x2f060c880, 0x2bf547ffe, 0x37d55fffe, 0x400a00, 0x3372573de, 0x1883d0316, 0x700c20, 0x5e90eca0, 0x10604880, 0x2bf1064a0, 0x18f35377e, 0x4e708c20, 0x33f557ffe, 0x1044a0, 0x1bf557ffe, 0x2f0604880, 0x200000000, 0x2bf557ffe, 0, 0x37d57fffe});
typedef Field<uint64_t, 35, 5, StatTable35, DynTable35, &SQR_TABLE_35, &QRT_TABLE_35> Field35;
#endif

#ifdef ENABLE_FIELD_INT_36
// 36 bit field
typedef RecLinTrans<uint64_t, 6, 6, 6, 6, 6, 6> StatTable36;
typedef RecLinTrans<uint64_t, 4, 4, 4, 4, 4, 4, 4, 4, 4> DynTable36;
constexpr StatTable36 SQR_TABLE_36({0x1, 0x4, 0x10, 0x40, 0x100, 0x400, 0x1000, 0x4000, 0x10000, 0x40000, 0x100000, 0x400000, 0x1000000, 0x4000000, 0x10000000, 0x40000000, 0x100000000, 0x400000000, 0x201, 0x804, 0x2010, 0x8040, 0x20100, 0x80400, 0x201000, 0x804000, 0x2010000, 0x8040000, 0x20100000, 0x80400000, 0x201000000, 0x804000000, 0x10000402, 0x40001008, 0x100004020, 0x400010080});
constexpr StatTable36 QRT_TABLE_36({0x40200, 0x8b0526186, 0x8b0526184, 0x240001000, 0x8b0526180, 0xcb6894d94, 0x240001008, 0xdb6880c22, 0x8b0526190, 0x8000200, 0xcb6894db4, 0x500424836, 0x240001048, 0x406cb2834, 0xdb6880ca2, 0x241200008, 0x8b0526090, 0xdb05021a6, 0x8000000, 0xdb01829b2, 0xcb68949b4, 0x1001000, 0x500424036, 0x106116406, 0x240000048, 0xcb29968a4, 0x406cb0834, 0, 0xdb6884ca2, 0x110010516, 0x241208008, 0x430434520, 0x8b0536090, 0x41208040, 0xdb05221a6, 0xb6884d14});
typedef Field<uint64_t, 36, 513, StatTable36, DynTable36, &SQR_TABLE_36, &QRT_TABLE_36> Field36;
#endif

#ifdef ENABLE_FIELD_INT_37
// 37 bit field
typedef RecLinTrans<uint64_t, 6, 6, 5, 5, 5, 5, 5> StatTable37;
typedef RecLinTrans<uint64_t, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3> DynTable37;
constexpr StatTable37 SQR_TABLE_37({0x1, 0x4, 0x10, 0x40, 0x100, 0x400, 0x1000, 0x4000, 0x10000, 0x40000, 0x100000, 0x400000, 0x1000000, 0x4000000, 0x10000000, 0x40000000, 0x100000000, 0x400000000, 0x1000000000, 0xa6, 0x298, 0xa60, 0x2980, 0xa600, 0x29800, 0xa6000, 0x298000, 0xa60000, 0x2980000, 0xa600000, 0x29800000, 0xa6000000, 0x298000000, 0xa60000000, 0x980000053, 0x60000011f, 0x180000047c});
constexpr StatTable37 QRT_TABLE_37({0xa3c62e7ba, 0xdc7a0c16a, 0xdc7a0c168, 0x12f7484546, 0xdc7a0c16c, 0xa9803a20, 0x12f748454e, 0xda07064a4, 0xdc7a0c17c, 0x123908de8e, 0xa9803a00, 0x122a888a8e, 0x12f748450e, 0x6790add8, 0xda0706424, 0x12e0a0384c, 0xdc7a0c07c, 0xcb28a2c2, 0x123908dc8e, 0xd09f85e86, 0xa9803e00, 0x124d682b6e, 0x122a88828e, 0x1738711a, 0x12f748550e, 0x73035b8, 0x67908dd8, 0xa0702438, 0xda0702424, 0xe0a0b860, 0x12e0a0b84c, 0x1c7a1c060, 0xdc7a1c07c, 0, 0xcb2aa2c2, 0x100000002c, 0x12390cdc8e});
typedef Field<uint64_t, 37, 83, StatTable37, DynTable37, &SQR_TABLE_37, &QRT_TABLE_37> Field37;
#endif

#ifdef ENABLE_FIELD_INT_38
// 38 bit field
typedef RecLinTrans<uint64_t, 6, 6, 6, 5, 5, 5, 5> StatTable38;
typedef RecLinTrans<uint64_t, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3> DynTable38;
constexpr StatTable38 SQR_TABLE_38({0x1, 0x4, 0x10, 0x40, 0x100, 0x400, 0x1000, 0x4000, 0x10000, 0x40000, 0x100000, 0x400000, 0x1000000, 0x4000000, 0x10000000, 0x40000000, 0x100000000, 0x400000000, 0x1000000000, 0x63, 0x18c, 0x630, 0x18c0, 0x6300, 0x18c00, 0x63000, 0x18c000, 0x630000, 0x18c0000, 0x6300000, 0x18c00000, 0x63000000, 0x18c000000, 0x630000000, 0x18c0000000, 0x2300000063, 0xc0000014a, 0x3000000528});
constexpr StatTable38 QRT_TABLE_38({0x34b0ac6430, 0x2223262fa, 0x2223262f8, 0x35554405fe, 0x2223262fc, 0x355514098a, 0x35554405f6, 0x400840, 0x2223262ec, 0x1777726532, 0x35551409aa, 0x15c06fc0, 0x35554405b6, 0x1f5303fec, 0x4008c0, 0x236a21030, 0x2223263ec, 0x1a9008c00, 0x1777726732, 0x3692c60ab6, 0x3555140daa, 0x15556007ee, 0x15c067c0, 0x14a0b030f2, 0x35554415b6, 0x227c06d168, 0x1f5301fec, 0x16c3928fc2, 0x4048c0, 0x3a942c4c0, 0x236a29030, 0x1636a2902e, 0x2223363ec, 0x3a6e898276, 0x1a9028c00, 0x6de74eb2c, 0x1777766732, 0});
typedef Field<uint64_t, 38, 99, StatTable38, DynTable38, &SQR_TABLE_38, &QRT_TABLE_38> Field38;
#endif

#ifdef ENABLE_FIELD_INT_39
// 39 bit field
typedef RecLinTrans<uint64_t, 6, 6, 6, 6, 5, 5, 5> StatTable39;
typedef RecLinTrans<uint64_t, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3> DynTable39;
constexpr StatTable39 SQR_TABLE_39({0x1, 0x4, 0x10, 0x40, 0x100, 0x400, 0x1000, 0x4000, 0x10000, 0x40000, 0x100000, 0x400000, 0x1000000, 0x4000000, 0x10000000, 0x40000000, 0x100000000, 0x400000000, 0x1000000000, 0x4000000000, 0x22, 0x88, 0x220, 0x880, 0x2200, 0x8800, 0x22000, 0x88000, 0x220000, 0x880000, 0x2200000, 0x8800000, 0x22000000, 0x88000000, 0x220000000, 0x880000000, 0x2200000000, 0x800000011, 0x2000000044});
constexpr StatTable39 QRT_TABLE_39({0x66b02a408c, 0x100420, 0x100422, 0x14206080, 0x100426, 0x5dccefab1c, 0x14206088, 0x9fc11e5b6, 0x100436, 0x5466bea62a, 0x5dccefab3c, 0x9aa110536, 0x142060c8, 0x54739ed6e2, 0x9fc11e536, 0xe7a82c080, 0x100536, 0x4002000, 0x5466bea42a, 0x6a4022000, 0x5dccefaf3c, 0x9e8118536, 0x9aa110d36, 0x5680e080, 0x142070c8, 0x7d293c5b6, 0x54739ef6e2, 0x8d680e080, 0x9fc11a536, 0x6d282c080, 0xe7a824080, 0x800000000, 0x110536, 0x2d680e080, 0x4022000, 0, 0x5466baa42a, 0x46b03a44aa, 0x6a40a2000});
typedef Field<uint64_t, 39, 17, StatTable39, DynTable39, &SQR_TABLE_39, &QRT_TABLE_39> Field39;
#endif

#ifdef ENABLE_FIELD_INT_40
// 40 bit field
typedef RecLinTrans<uint64_t, 6, 6, 6, 6, 6, 5, 5> StatTable40;
typedef RecLinTrans<uint64_t, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4> DynTable40;
constexpr StatTable40 SQR_TABLE_40({0x1, 0x4, 0x10, 0x40, 0x100, 0x400, 0x1000, 0x4000, 0x10000, 0x40000, 0x100000, 0x400000, 0x1000000, 0x4000000, 0x10000000, 0x40000000, 0x100000000, 0x400000000, 0x1000000000, 0x4000000000, 0x39, 0xe4, 0x390, 0xe40, 0x3900, 0xe400, 0x39000, 0xe4000, 0x390000, 0xe40000, 0x3900000, 0xe400000, 0x39000000, 0xe4000000, 0x390000000, 0xe40000000, 0x3900000000, 0xe400000000, 0x900000004b, 0x400000015e});
constexpr StatTable40 QRT_TABLE_40({0x624b3cecc, 0xbc5c3f4c6, 0xbc5c3f4c4, 0xde1603e2c, 0xbc5c3f4c0, 0xaabec06cea, 0xde1603e24, 0x6cd9f724c2, 0xbc5c3f4d0, 0xcde1743818, 0xaabec06cca, 0xa138c314ca, 0xde1603e64, 0xaafc00f01a, 0x6cd9f72442, 0xcdca11bb4, 0xbc5c3f5d0, 0xa00002001a, 0xcde1743a18, 0xdf1407b90, 0xaabec068ca, 0xc043b482c8, 0xa138c31cca, 0xcb86977e3c, 0xde1602e64, 0x604596a326, 0xaafc00d01a, 0xcc1c165d0, 0x6cd9f76442, 0x673c94da26, 0xcdca19bb4, 0x67c0940a26, 0xbc5c2f5d0, 0xa4dca19bae, 0xa00000001a, 0x1bc5c2f5d0, 0xcde1703a18, 0, 0xdf1487b90, 0x8df1487b8a});
typedef Field<uint64_t, 40, 57, StatTable40, DynTable40, &SQR_TABLE_40, &QRT_TABLE_40> Field40;
#endif
}

Sketch* ConstructGeneric5Bytes(int bits, int implementation)
{
    switch (bits) {
#ifdef ENABLE_FIELD_INT_33
    case 33: return new SketchImpl<Field33>(implementation, 33);
#endif
#ifdef ENABLE_FIELD_INT_34
    case 34: return new SketchImpl<Field34>(implementation, 34);
#endif
#ifdef ENABLE_FIELD_INT_35
    case 35: return new SketchImpl<Field35>(implementation, 35);
#endif
#ifdef ENABLE_FIELD_INT_36
    case 36: return new SketchImpl<Field36>(implementation, 36);
#endif
#ifdef ENABLE_FIELD_INT_37
    case 37: return new SketchImpl<Field37>(implementation, 37);
#endif
#ifdef ENABLE_FIELD_INT_38
    case 38: return new SketchImpl<Field38>(implementation, 38);
#endif
#ifdef ENABLE_FIELD_INT_39
    case 39: return new SketchImpl<Field39>(implementation, 39);
#endif
#ifdef ENABLE_FIELD_INT_40
    case 40: return new SketchImpl<Field40>(implementation, 40);
#endif
    default: return nullptr;
    }
}
