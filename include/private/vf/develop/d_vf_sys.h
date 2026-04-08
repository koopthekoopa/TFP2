#ifndef VF_D_VF_SYSTEM_H
#define VF_D_VF_SYSTEM_H

#include <private/vf/PrFILE2/pf_types.h>

typedef struct VFSysTime {
    pf_s32 sec;    // offset 0x0, size 0x4
    pf_s32 min;    // offset 0x4, size 0x4
    pf_s32 hour;   // offset 0x8, size 0x4
    pf_s32 day;    // offset 0xC, size 0x4
    pf_s32 month;  // offset 0x10, size 0x4
    pf_s32 year;   // offset 0x14, size 0x4
} VFSysTime;

typedef void (*VFSysTimeStampCallback)(VFSysTime* time);

extern VFSysTimeStampCallback VFSysGetTimeStampCallback();

#endif  // VF_D_VF_SYSTEM_H
