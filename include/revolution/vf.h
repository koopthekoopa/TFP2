#ifndef REVOLUTION_VF_H
#define REVOLUTION_VF_H

#include <revolution/vf/types.h>

VFErr VFIsAvailable();

void VFInitEx(void* heap_start_address, u32 size);
void VFInit();
void VFFinalize();

VFErr VFAttachDriveNANDFlash(const char* drive);

VFErr VFCreateSystemFileNANDFlashEx(const char* sys_file_name, u32 file_size);

VFErr VFActivateDriveNANDFlash(const char* drive, const char* sys_file_name);
VFErr VFActivateDriveNANDFlashEx(const char* drive, const char* sys_file_name);
VFErr VFInactivateDrive(const char* drive);

VFErr VFMountDriveNANDFlash(const char* drive, const char* sys_file_name);
VFErr VFMountDriveNANDFlashEx(const char* drive, const char* sys_file_name);
VFErr VFUnmountDrive(const char* drive);

VFFile* VFOpenFile(const char* path, const char* mode, u32 attr);
VFErr VFCloseFile(VFFile* file);

VFErr VFSeekFile(VFFile* file, s32 offset, s32 origin);
VFErr VFReadFile(VFFile* file, void* buf, u32 size, u32* read_size);
VFErr VFWriteFile(VFFile* file, void* buf, u32 size);

VFErr VFDeleteFile(const char* iath);

VFErr VFCreateDir(const char* dir_name);

s32 VFGetFileSizeByFd(VFFile* file);

VFErr VFGetLastError();
VFErr VFGetLastDeviceError(const char* drive);

s32 VFGetDriveFreeSize(const char* drive);

VFErr VFFormatDrive(const char* drive);

VFErr VFSetSyncMode(const char* drive, u32 mode);

#endif  // REVOLUTION_VF_H
