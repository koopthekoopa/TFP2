#ifndef PRFILE2_VFMOD_PF_TYPES_H
#define PRFILE2_VFMOD_PF_TYPES_H

#include <stddef.h>

typedef signed char pf_s8;
typedef signed short pf_s16;
typedef signed long pf_s32;
typedef unsigned char pf_u8;
typedef unsigned short pf_u16;
typedef unsigned long pf_u32;

typedef char pf_ch8;
typedef int pf_int32;

typedef volatile pf_u8 pf_vu8;
typedef volatile pf_u16 pf_vu16;
typedef volatile pf_u32 pf_vu32;
typedef volatile pf_s8 pf_vs8;
typedef volatile pf_s16 pf_vs16;
typedef volatile pf_s32 pf_vs32;

typedef pf_u32 /* ? */ pf_bool;

#define PF_TRUE 1
#define PF_FALSE 0

#define PF_NULL 0

// clang-format off
#define PF_SWAP_16(x) ((pf_u16)((((x) >>  8) & 0x00FF    ) |  (((x) << 8) & 0xFF00  )                                                  ))
#define PF_SWAP_32(x) ((pf_u32)((((x) << 24) & 0xFF000000) | ((((x) << 8) & 0xFF0000) | ((((x) >> 24) & 0xFF) | (((x) >> 8) & 0xFF00)))))
// clang-format on

// unsorted structs
#include <private/vf/PrFILE2/dskmng/pdm_struct.h>
#include <private/vf/PrFILE2/pf_struct.h>

#endif  // PRFILE2_VFMOD_PF_TYPES_H
