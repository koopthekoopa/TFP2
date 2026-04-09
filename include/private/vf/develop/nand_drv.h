#ifndef VF_NAND_DRIVER_H
#define VF_NAND_DRIVER_H

#include <private/vf/PrFILE2/dskmng/pdm_disk.h>

#include <revolution/nand.h>

s32 VFNandCreate(const char* path, u8 perm, u8 attr);
s32 VFNandPrivateCreate(const char* path, u8 perm, u8 attr);
s32 VFNandDelete(const char* path);
s32 VFNandPrivateDelete(const char* path);
s32 VFNandClose(NANDFileInfo* info);
s32 VFNandOpen(const char* path, NANDFileInfo* info, u8 accType);
s32 VFNandPrivateOpen(const char* path, NANDFileInfo* info, u8 accType);
s32 VFNandWrite(NANDFileInfo* info, void* buf, u32 length);
s32 VFNandRead(NANDFileInfo* info, void* buf, u32 length);
s32 VFNandCreateDir(const char* path, u8 perm, u8 attr);
s32 VFNandPrivateCreateDir(const char* path, u8 perm, u8 attr);
s32 VFNandSeek(NANDFileInfo* info, s32 offset, s32 whence);
s32 VFNandGetLength(NANDFileInfo* info, u32* length);
s32 VFNandCreateSp(const char* path, u8 perm, u8 attr, u32 handleIdx);
s32 VFNandOpenSp(const char* path, void* info, u8 accType, u32 handleIdx);
s32 VFNandDeleteSp(const char* path, u32 handleIdx);
void VFNandSetNANDFuncNormal(u32 handleIdx);
void VFNandSetNANDFuncEx(u32 handleIdx);

s32 NAND_CreatePrfFileEx(u32 fileSize, char* fullpath, u16 version);
s32 VFi_NandFlushNANDFromHandleIdx(s32 i_handleIdx, int i_setLastDeviceError);

s32 VFNandFlushNANDFromHandleIdx(s32 handleIdx, int setLastDeviceError);

s32 VFnanddrv_init_drv_tbl(PDM_DISK_TBL* p_disk_tbl, u32 uext);

#endif  // VF_NAND_DRIVER_H
