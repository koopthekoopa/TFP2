#ifndef PRIVATE_IOS_TYPES_H
#define PRIVATE_IOS_TYPES_H

#include <revolution/types.h>

typedef s32 IOSError;
typedef s32 IOSFd;

typedef IOSError (*IOSIpcCb)(IOSError, void*);

typedef struct IOSIoVector {
    u8* base;    // 0x00
    u32 length;  // 0x04
} IOSIoVector;

#endif  // PRIVATE_IOS_TYPES_H
