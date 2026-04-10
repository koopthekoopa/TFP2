#ifndef REVOLUTION_VF_H
#define REVOLUTION_VF_H

#include <revolution/vf/types.h>

s32 VFIsAvailable();

void VFInitEx(void* heap_start_address, u32 size);
void VFInit();
void VFFinalize();

s32 VFAttachDriveNANDFlash(const char* drive);

s32 VFCreateSystemFileNANDFlashEx(const char* sys_file_name, u32 file_size);

s32 VFActivateDriveNANDFlash(const char* drive, const char* sys_file_name);
s32 VFActivateDriveNANDFlashEx(const char* drive, const char* sys_file_name);
s32 VFInactivateDrive(const char* drive);

s32 VFMountDriveNANDFlash(const char* drive, const char* sys_file_name);
s32 VFMountDriveNANDFlashEx(const char* drive, const char* sys_file_name);
s32 VFUnmountDrive(const char* drive);

VF_FILE* VFOpenFile(const char* iath, const char* mode, u32 attr);
s32 VFCloseFile(VF_FILE* file);

s32 VFSeekFile(VF_FILE* file, s32 offset, s32 origin);
s32 VFReadFile(VF_FILE* file, void* buf, u32 size, u32* read_size);
s32 VFWriteFile(VF_FILE* file, void* buf, u32 size);

s32 VFDeleteFile(const char* iath);

s32 VFCreateDir(const char* dir_name);

s32 VFGetFileSizeByFd(VF_FILE* file);

s32 VFGetLastError();
s32 VFGetLastDeviceError(const char* drive);

s32 VFGetDriveFreeSize(const char* drive);

s32 VFFormatDrive(const char* drive);

s32 VFSetSyncMode(const char* drive, u32 mode);

#endif  // REVOLUTION_VF_H
