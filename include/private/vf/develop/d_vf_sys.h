#ifndef VF_D_VF_SYSTEM_H
#define VF_D_VF_SYSTEM_H

#include <private/vf/PrFILE2/pf_types.h>

#include <private/vf/PrFILE2/fatfs/pf_cache.h>
#include <private/vf/PrFILE2/fatfs/pf_volume.h>

#include <private/vf/PrFILE2/dskmng/pdm_disk.h>

#include <revolution/mem.h>

typedef struct {
    pf_u32 status;     // offset 0x0, size 0x4
    pf_u32 err;        // offset 0x4, size 0x4
    pf_u32 type;       // offset 0x8, size 0x4
    pf_u32 sync_mode;  // offset 0xC, size 0x4
} VFSys_device;

typedef struct {
    MEMiHeapHead* heap_handle;        // offset 0x0, size 0x4
    pf_u32 cache_pages;               // offset 0x4, size 0x4
    PF_CACHE_PAGE* pf_cache_page_p;   // offset 0x8, size 0x4
    PF_CACHE_BUFFER* pf_cache_buf_p;  // offset 0xC, size 0x4
} VFSys_cache_setting;

typedef struct {
    void* file_p;                   // offset 0x0, size 0x4
    PDM_DISK* pf_disk_p;            // offset 0x4, size 0x4
    PF_DRV_TBL pf_drv;              // offset 0x8, size 0xC
    PDM_PARTITION* pf_part_p;       // offset 0x14, size 0x4
    VFSys_cache_setting cache;      // offset 0x18, size 0x10
    PF_CACHE_SETTING pf_cache_set;  // offset 0x28, size 0x14
    pf_u8 pf_filename[255];         // offset 0x3C, size 0xFF
} VFSys_drive;

typedef struct {
    // total size: 0x140
    VFSys_device* device_p;  // offset 0x0, size 0x4
    VFSys_drive drive;       // offset 0x4, size 0x13C
} VFSys_handle;

typedef struct VFSysTime {
    pf_s32 sec;    // offset 0x0, size 0x4
    pf_s32 min;    // offset 0x4, size 0x4
    pf_s32 hour;   // offset 0x8, size 0x4
    pf_s32 day;    // offset 0xC, size 0x4
    pf_s32 month;  // offset 0x10, size 0x4
    pf_s32 year;   // offset 0x14, size 0x4
} VFSysTime;

typedef void (*VFSysTimeStampCallback)(VFSysTime* time);

VFSys_handle* VFSysVol2HandleP(PF_VOLUME* i_vol_p /* r28 */);
VFSys_handle* VFSysGetHandleP(long i_idx);
long VFSysHandleP2Idx(VFSys_handle* handle);

int VFSysPDMDisk2HandleIdx(const PDM_DISK* disk);

extern VFSysTimeStampCallback VFSysGetTimeStampCallback();

#endif  // VF_D_VF_SYSTEM_H
