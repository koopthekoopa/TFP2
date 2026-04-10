#ifndef PRFILE2_VFMOD_PDM_UNSORTED_STRUCTS_H
#define PRFILE2_VFMOD_PDM_UNSORTED_STRUCTS_H

#include <private/vf/PrFILE2/pf_types.h>

typedef enum {
    PDM_FAT_12 = 0,
    PDM_FAT_16 = 1,
    PDM_FAT_32 = 2,
    PDM_FAT_ERR = -1,
} PDM_FAT_TYPE;

typedef struct PDM_DISK PDM_DISK;
typedef struct PDM_DISK_INFO PDM_DISK_INFO;

typedef struct PDM_FUNCTBL {
    // total size: 0x20
    pf_s32 (*init)(PDM_DISK*);                                                   // offset 0x0, size 0x4
    pf_s32 (*finalize)(PDM_DISK*);                                               // offset 0x4, size 0x4
    pf_s32 (*mount)(PDM_DISK*);                                                  // offset 0x8, size 0x4
    pf_s32 (*unmount)(PDM_DISK*);                                                // offset 0xC, size 0x4
    pf_s32 (*format)(PDM_DISK*, const pf_u8*);                                   // offset 0x10, size 0x4
    pf_s32 (*physical_read)(PDM_DISK*, pf_u8*, pf_u32, pf_u32, pf_u32*);         // offset 0x14, size 0x4
    pf_s32 (*physical_write)(PDM_DISK*, const pf_u8*, pf_u32, pf_u32, pf_u32*);  // offset 0x18, size 0x4
    pf_s32 (*get_disk_info)(PDM_DISK*, PDM_DISK_INFO*);                          // offset 0x1C, size 0x4
} PDM_FUNCTBL;

typedef struct PDM_DISK_TBL {
    // total size: 0x8
    struct PDM_FUNCTBL* p_func;  // offset 0x0, size 0x4
    pf_u32 ui_ext;               // offset 0x4, size 0x4
} PDM_DISK_TBL;

typedef struct PDM_INIT_DISK {
    // total size: 0x8
    pf_s32 (*p_func)(PDM_DISK_TBL*, pf_u32);  // offset 0x0, size 0x4
    pf_u32 ui_ext;                            // offset 0x4, size 0x4
} PDM_INIT_DISK;

typedef struct PDM_PART_TBL {
    // total size: 0x14
    pf_u8 boot_flag;          // offset 0x0, size 0x1
    pf_u8 partition_type;     // offset 0x1, size 0x1
    pf_u16 s_cylinder;        // offset 0x2, size 0x2
    pf_u8 s_head;             // offset 0x4, size 0x1
    pf_u8 s_sector;           // offset 0x5, size 0x1
    pf_u16 e_cylinder;        // offset 0x6, size 0x2
    pf_u8 e_head;             // offset 0x8, size 0x1
    pf_u8 e_sector;           // offset 0x9, size 0x1
    pf_u8 pad[2];             // offset 0xA, size 0x2
    pf_u32 lba_start_sector;  // offset 0xC, size 0x4
    pf_u32 lba_num_sectors;   // offset 0x10, size 0x4
} PDM_PART_TBL;

typedef struct PDM_FSINFO {
    // total size: 0x8
    pf_u32 free_count;  // offset 0x0, size 0x4
    pf_u32 next_free;   // offset 0x4, size 0x4
} PDM_FSINFO;

/*typedef*/ struct PDM_DISK_INFO {
    // total size: 0x14
    pf_u32 total_sectors;     // offset 0x0, size 0x4
    pf_u16 cylinders;         // offset 0x4, size 0x2
    pf_u8 heads;              // offset 0x6, size 0x1
    pf_u8 sectors_per_track;  // offset 0x7, size 0x1
    pf_u16 bytes_per_sector;  // offset 0x8, size 0x2
    pf_u32 media_attr;        // offset 0xC, size 0x4
    void* format_param;       // offset 0x10, size 0x4
} /*PDM_DISK_INFO*/;

#endif  // PRFILE2_VFMOD_PDM_UNSORTED_STRUCTS_H
