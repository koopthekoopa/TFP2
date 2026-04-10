#ifndef VF_D_VF_SYSTEM_H
#define VF_D_VF_SYSTEM_H

#include <private/vf/PrFILE2/pf_types.h>

#include <private/vf/PrFILE2/fatfs/pf_cache.h>
#include <private/vf/PrFILE2/fatfs/pf_volume.h>

#include <private/vf/PrFILE2/dskmng/pdm_disk.h>

#include <revolution/mem.h>

#include <revolution/dvd.h>
#include <revolution/nand.h>
#include <revolution/sdi.h>

typedef struct {
    u32 status;     // offset 0x0, size 0x4
    u32 err;        // offset 0x4, size 0x4
    u32 type;       // offset 0x8, size 0x4
    u32 sync_mode;  // offset 0xC, size 0x4
} VFSys_device;

typedef struct {
    MEMiHeapHead* heap_handle;        // offset 0x0, size 0x4
    u32 cache_pages;                  // offset 0x4, size 0x4
    PF_CACHE_PAGE* pf_cache_page_p;   // offset 0x8, size 0x4
    PF_CACHE_BUFFER* pf_cache_buf_p;  // offset 0xC, size 0x4
} VFSys_cache;

typedef struct {
    void* file_p;                   // offset 0x0, size 0x4
    PDM_DISK* pf_disk_p;            // offset 0x4, size 0x4
    PF_DRV_TBL pf_drv;              // offset 0x8, size 0xC
    PDM_PARTITION* pf_part_p;       // offset 0x14, size 0x4
    VFSys_cache cache;              // offset 0x18, size 0x10
    PF_CACHE_SETTING pf_cache_set;  // offset 0x28, size 0x14
    u8 pf_filename[255];            // offset 0x3C, size 0xFF
} VFSys_drive;

typedef struct {
    VFSys_device* device_p;  // offset 0x0, size 0x4
    VFSys_drive drive;       // offset 0x4, size 0x13C
} VFSys_handle;

typedef struct {
    VFSys_device base;  // offset 0x0, size 0x10
} VFSys_deviceBase;

typedef struct {
    VFSys_deviceBase device;  // offset 0x0, size 0x10
    DVDFileInfo file_info;    // offset 0x10, size 0x3C
} VFSys_deviceDvd;

typedef struct {
    VFSys_deviceBase device;  // offset 0x0, size 0x10
    NANDFileInfo file_info;   // offset 0x10, size 0x8C
} VFSys_deviceNand;

typedef struct {
    VFSys_device base;                 // offset 0x0, size 0x10
    SDDev drive;                       // offset 0x20, size 0x28
    SDDevEventCallback eventCallback;  // offset 0x48, size 0x4
    u32 slotNo;                        // offset 0x4C, size 0x4
} VFSys_deviceSD;

typedef struct VFSysTime {
    s32 sec;    // offset 0x0, size 0x4
    s32 min;    // offset 0x4, size 0x4
    s32 hour;   // offset 0x8, size 0x4
    s32 day;    // offset 0xC, size 0x4
    s32 month;  // offset 0x10, size 0x4
    s32 year;   // offset 0x14, size 0x4
} VFSysTime;

typedef void (*VFSysTimeStampCallback)(VFSysTime* time);

void VFSysSetLastError(s32 err);

VFSys_handle* VFSysGetHandleP(s32 idx);
s32 VFSysHandleP2Idx(VFSys_handle* handle);
VFSys_handle* VFSysVol2HandleP(PF_VOLUME* vol);
VFSys_handle* VFSys_file_2_handle(PF_FILE* file);
int VFSysPDMDisk2HandleIdx(const PDM_DISK* disk);
VFSys_drive* VFSysGetDriveP(s32 idx);
VFSys_drive* VFSysPDMDisk2DriveP(PDM_DISK* disk);

void VFSysInit(void* heap_start_address, u32 size);
void VFSysFinalize();

void VFSysSetDevErrInfo(s32 handle_idx, s32 err);

s32 VFSysSetDeviceNANDFlash(s32* idx, void* cache_heap, u32 cache_size);
s32 VFSysUnsetDevice(s32 handle_idx);

s32 VFSysCheckExistPrfFile(s32 handle_idx, const char* prf_file_name, void* memory);
s32 VFSysCreatePrfFileNANDFlashEx(const char* prf_file_name, u32 file_size);

s32 VFSysMountDrv(s32 handle_idx, const char* prf_file_name, void* memory);

s32 VFSysUnmountDrv(s32 handle_idx, u32 mode);

PF_FILE* VFSysOpenFile_current(const char* path, const char* mode);
PF_FILE* VFSysOpenFile(s32 handle_idx, const char* path, const char* mode);

s32 VFSysCloseFile(PF_FILE* file);

s32 VFSysSeekFile(PF_FILE* file, s32 offset, s32 origin);

s32 VFSysReadFile(u32* read_size, void* buf, u32 size, PF_FILE* file);
s32 VFSysWriteFile(void* buf, u32 size, PF_FILE* file);

s32 VFSysDeleteFile_current(const char* path);
s32 VFSysDeleteFile(s32 handle_idx, const char* path);

s32 VFSysCreateDir_current(const char* dir_name);
s32 VFSysCreateDir(s32 handle_idx, const char* dir_name);

s32 VFSysGetFileSizeByFd(s32* size, PF_FILE* file);

s32 VFSysGetDriveFreeSize(s32 handle_idx);

s32 VFSysGetLastError();
s32 VFSysGetLastDeviceError(s32 handle_idx);

void VFSysSetNandFuncNormal(u32 handle_idx);
void VFSysSetNandFuncEx(u32 handle_idx);

s32 VFSysFormatDrive(s32 handle_idx);

s32 VFSysSetSyncMode(s32 handle_idx, u32 mode);
u32 VFSysGetSyncMode(s32 handle_idx);

VFSysTimeStampCallback VFSysSetTimeStampCallback(VFSysTimeStampCallback timestamp_callback);
VFSysTimeStampCallback VFSysGetTimeStampCallback();

#endif  // VF_D_VF_SYSTEM_H
