#ifndef REVOLUTION_SDI_H
#define REVOLUTION_SDI_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _SDDev {
    int SDDevFd;       // offset 0x0, size 0x4
    u32 SDDevFunc;     // offset 0x4, size 0x4
    char* SDDevName;   // offset 0x8, size 0x4
    u32 SDDevSlot;     // offset 0xC, size 0x4
    u32 SDDevRca;      // offset 0x10, size 0x4
    u32 SDBlockLen;    // offset 0x14, size 0x4
    u32 SDSectorSize;  // offset 0x18, size 0x4
    u32 SDSectorNum;   // offset 0x1C, size 0x4
    u32 SDDevSize;     // offset 0x20, size 0x4
    u32 SDState;       // offset 0x24, size 0x4
} SDDev;

typedef void (*SDDevEventCallback)(u32);

#ifdef __cplusplus
}
#endif

#endif  // REVOLUTION_SDI_H
