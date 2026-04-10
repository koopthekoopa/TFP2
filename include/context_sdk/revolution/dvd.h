#ifndef REVOLUTION_DVD_H
#define REVOLUTION_DVD_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    DVD_RESULT_COVER_CLOSED = -4,
    DVD_RESULT_CANCELED,
    DVD_RESULT_M2,
    DVD_RESULT_FATAL,
    DVD_RESULT_OK,
};

struct DVDDiskID {
    // total size: 0x20
    char gameName[4];     // offset 0x0, size 0x4
    char company[2];      // offset 0x4, size 0x2
    u8 diskNumber;        // offset 0x6, size 0x1
    u8 gameVersion;       // offset 0x7, size 0x1
    u8 streaming;         // offset 0x8, size 0x1
    u8 streamingBufSize;  // offset 0x9, size 0x1
    u8 padding[14];       // offset 0xA, size 0xE
    u32 rvlMagic;         // offset 0x18, size 0x4
    u32 gcMagic;          // offset 0x1C, size 0x4
};
struct DVDCommandBlock {
    // total size: 0x30
    struct DVDCommandBlock* next;                     // offset 0x0, size 0x4
    struct DVDCommandBlock* prev;                     // offset 0x4, size 0x4
    u32 command;                                      // offset 0x8, size 0x4
    long state;                                       // offset 0xC, size 0x4
    u32 offset;                                       // offset 0x10, size 0x4
    u32 length;                                       // offset 0x14, size 0x4
    void* addr;                                       // offset 0x18, size 0x4
    u32 currTransferSize;                             // offset 0x1C, size 0x4
    u32 transferredSize;                              // offset 0x20, size 0x4
    struct DVDDiskID* id;                             // offset 0x24, size 0x4
    void (*callback)(long, struct DVDCommandBlock*);  // offset 0x28, size 0x4
    void* userData;                                   // offset 0x2C, size 0x4
};
typedef struct DVDFileInfo {
    // total size: 0x3C
    struct DVDCommandBlock cb;                    // offset 0x0, size 0x30
    u32 startAddr;                                // offset 0x30, size 0x4
    u32 length;                                   // offset 0x34, size 0x4
    void (*callback)(long, struct DVDFileInfo*);  // offset 0x38, size 0x4
} DVDFileInfo;

BOOL DVDOpen(const char* fileName, DVDFileInfo* fileInfo);
s32 DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio);
BOOL DVDClose(DVDFileInfo* fileInfo);

#ifdef __cplusplus
}
#endif

#endif  // REVOLUTION_DVD_H
