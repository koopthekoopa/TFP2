#ifndef PRFILE2_VFMOD_PR_UNSORTED_STUFF_H
#define PRFILE2_VFMOD_PR_UNSORTED_STUFF_H

#include <private/vf/PrFILE2/pf_types.h>

typedef struct PR_BINHEADER {
    pf_s8 signature[4];     // offset 0x0, size 0x4
    pf_u16 byteOrder;       // offset 0x4, size 0x2
    pf_u8 version[2];       // offset 0x6, size 0x2
    pf_u8 fileSize[4];      // offset 0x8, size 0x4
    pf_u16 headerSize;      // offset 0xC, size 0x2
    pf_u16 dataBlocks;      // offset 0xE, size 0x2
    pf_u8 volatile_memory;  // offset 0x10, size 0x1
    pf_u8 pad[15];          // offset 0x11, size 0xF
} PR_BINHEADER;

#endif  // PRFILE2_VFMOD_PR_UNSORTED_STUFF_H
