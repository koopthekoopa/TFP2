#ifndef PRIVATE_NAND_H
#define PRIVATE_NAND_H

#include <revolution/nand.h>

#ifdef __cplusplus
extern "C" {
#endif

s32 NANDPrivateCreate(const char* path, u8 perm, u8 attr);

s32 NANDPrivateOpen(const char* path, NANDFileInfo* info, u8 accType);

s32 NANDPrivateDelete(const char* path);

s32 NANDPrivateCreateDir(const char* path, u8 perm, u8 attr);

#ifdef __cplusplus
}
#endif

#endif  // REVOLUTION_NAND_H
