#ifndef VF_PF_UNSORTED_STRUCTS_H
#define VF_PF_UNSORTED_STRUCTS_H

#include <private/vf/pf_types.h>

typedef struct PF_VOLUME PF_VOLUME;

typedef enum /* @enum$182pf_str_c */ {
    FAT_12 = 0,
    FAT_16 = 1,
    FAT_32 = 2,
    FAT_ERR = -1,
} PF_FAT_TYPE;

typedef struct PF_SYS_DATE {
    // total size: 0x6
    pf_u16 sys_year;   // offset 0x0, size 0x2
    pf_u16 sys_month;  // offset 0x2, size 0x2
    pf_u16 sys_day;    // offset 0x4, size 0x2
} PF_SYS_DATE;

typedef struct PF_SYS_TIME {
    // total size: 0x8
    pf_u16 sys_hour;  // offset 0x0, size 0x2
    pf_u16 sys_min;   // offset 0x2, size 0x2
    pf_u16 sys_sec;   // offset 0x4, size 0x2
    pf_u16 sys_ms;    // offset 0x6, size 0x2
} PF_SYS_TIME;

typedef pf_u8 PF_CACHE_BUFFER[512];

typedef struct PF_CACHE_SETTING {
    // total size: 0x14
    struct PF_CACHE_PAGE* pages;  // offset 0x0, size 0x4
    PF_CACHE_BUFFER* buffers;     // offset 0x4, size 0x4
    pf_u16 num_fat_pages;         // offset 0x8, size 0x2
    pf_u16 num_data_pages;        // offset 0xA, size 0x2
    pf_u32 num_fat_buf_size;      // offset 0xC, size 0x4
    pf_u32 num_data_buf_size;     // offset 0x10, size 0x4
} PF_CACHE_SETTING;

typedef struct PF_DRV_TBL {
    // total size: 0xC
    void* p_part;             // offset 0x0, size 0x4
    PF_CACHE_SETTING* cache;  // offset 0x4, size 0x4
    pf_s8 drive;              // offset 0x8, size 0x1
    pf_u8 stat;               // offset 0x9, size 0x1
} PF_DRV_TBL;

typedef struct PF_DEV_INF {
    // total size: 0x10
    pf_u32 cls;  // offset 0x0, size 0x4
    pf_u32 ecl;  // offset 0x4, size 0x4
    pf_u32 bps;  // offset 0x8, size 0x4
    pf_u32 spc;  // offset 0xC, size 0x4
} PF_DEV_INF;

typedef struct PF_CHARCODE {
    // total size: 0x18
    pf_s32 (*oem2unicode)(pf_s8*, pf_u16*);        // offset 0x0, size 0x4
    pf_s32 (*unicode2oem)(pf_u16*, pf_s8*);        // offset 0x4, size 0x4
    pf_s32 (*oem_char_width)(pf_s8*);              // offset 0x8, size 0x4
    pf_u32 (*is_oem_mb_char)(pf_s8, pf_u32);       // offset 0xC, size 0x4
    pf_s32 (*unicode_char_width)(pf_u16*);         // offset 0x10, size 0x4
    pf_u32 (*is_unicode_mb_char)(pf_u16, pf_u32);  // offset 0x14, size 0x4
} PF_CHARCODE;

typedef struct PF_CONTEXT {
    // total size: 0x8
    pf_u32 stat;        // offset 0x0, size 0x4
    pf_s32 context_id;  // offset 0x4, size 0x4
} PF_CONTEXT;

#endif  // VF_PF_UNSORTED_STRUCTS_H
