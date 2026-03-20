#ifndef VF_PDM_UNSORTED_STRUCTS_H
#define VF_PDM_UNSORTED_STRUCTS_H

#include <private/vf/pf_types.h>

typedef enum {
    PDM_FAT_12 = 0,
    PDM_FAT_16 = 1,
    PDM_FAT_32 = 2,
    PDM_FAT_ERR = -1,
} PDM_FAT_TYPE;

typedef struct PDM_DISK PDM_DISK;
typedef struct PDM_DISK_INFO PDM_DISK_INFO;

struct PDM_FUNCTBL {
    // total size: 0x20
    long (*init)(PDM_DISK*);                                                                          // offset 0x0, size 0x4
    long (*finalize)(PDM_DISK*);                                                                      // offset 0x4, size 0x4
    long (*mount)(PDM_DISK*);                                                                         // offset 0x8, size 0x4
    long (*unmount)(PDM_DISK*);                                                                       // offset 0xC, size 0x4
    long (*format)(PDM_DISK*, unsigned char*);                                                        // offset 0x10, size 0x4
    long (*physical_read)(PDM_DISK*, unsigned char*, unsigned long, unsigned long, unsigned long*);   // offset 0x14, size 0x4
    long (*physical_write)(PDM_DISK*, unsigned char*, unsigned long, unsigned long, unsigned long*);  // offset 0x18, size 0x4
    long (*get_disk_info)(PDM_DISK*, PDM_DISK_INFO*);                                                 // offset 0x1C, size 0x4
};

struct PDM_DISK_TBL {
    // total size: 0x8
    struct PDM_FUNCTBL* p_func;  // offset 0x0, size 0x4
    unsigned long ui_ext;        // offset 0x4, size 0x4
};

struct PDM_INIT_DISK {
    // total size: 0x8
    long (*p_func)(struct PDM_DISK_TBL*, unsigned long);  // offset 0x0, size 0x4
    unsigned long ui_ext;                                 // offset 0x4, size 0x4
};

struct PDM_PART_TBL {
    // total size: 0x14
    unsigned char boot_flag;         // offset 0x0, size 0x1
    unsigned char partition_type;    // offset 0x1, size 0x1
    unsigned short s_cylinder;       // offset 0x2, size 0x2
    unsigned char s_head;            // offset 0x4, size 0x1
    unsigned char s_sector;          // offset 0x5, size 0x1
    unsigned short e_cylinder;       // offset 0x6, size 0x2
    unsigned char e_head;            // offset 0x8, size 0x1
    unsigned char e_sector;          // offset 0x9, size 0x1
    unsigned char pad[2];            // offset 0xA, size 0x2
    unsigned long lba_start_sector;  // offset 0xC, size 0x4
    unsigned long lba_num_sectors;   // offset 0x10, size 0x4
};

typedef struct PDM_FSINFO {
    // total size: 0x8
    unsigned long free_count;  // offset 0x0, size 0x4
    unsigned long next_free;   // offset 0x4, size 0x4
} PDM_FSINFO;

struct PDM_DISK_INFO {
    // total size: 0x14
    unsigned long total_sectors;      // offset 0x0, size 0x4
    unsigned short cylinders;         // offset 0x4, size 0x2
    unsigned char heads;              // offset 0x6, size 0x1
    unsigned char sectors_per_track;  // offset 0x7, size 0x1
    unsigned short bytes_per_sector;  // offset 0x8, size 0x2
    unsigned long media_attr;         // offset 0xC, size 0x4
    void* format_param;               // offset 0x10, size 0x4
};

struct PDM_PARTITION {
    // total size: 0x2C
    unsigned long status;                    // offset 0x0, size 0x4
    struct PDM_DISK* p_disk;                 // offset 0x4, size 0x4
    unsigned long signature;                 // offset 0x8, size 0x4
    unsigned short part_id;                  // offset 0xC, size 0x2
    unsigned short open_part_cnt;            // offset 0xE, size 0x2
    struct PDM_PARTITION* part_lock_handle;  // offset 0x10, size 0x4
    unsigned long start_sector;              // offset 0x14, size 0x4
    unsigned long total_sector;              // offset 0x18, size 0x4
    unsigned long mbr_sector;                // offset 0x1C, size 0x4
    unsigned char partition_type;            // offset 0x20, size 0x1
    long driver_last_error;                  // offset 0x24, size 0x4
    void* p_vol;                             // offset 0x28, size 0x4
};

struct PDM_DISK {
    // total size: 0x34
    unsigned long status;                   // offset 0x0, size 0x4
    struct PDM_DISK_TBL disk_tbl;           // offset 0x4, size 0x8
    unsigned long signature;                // offset 0xC, size 0x4
    unsigned short open_disk_cnt;           // offset 0x10, size 0x2
    unsigned short disk_lock_cnt;           // offset 0x12, size 0x2
    struct PDM_DISK* disk_lock_handle;      // offset 0x14, size 0x4
    struct PDM_DISK_INFO disk_info;         // offset 0x18, size 0x14
    struct PDM_INIT_DISK* p_init_disk_tbl;  // offset 0x2C, size 0x4
    struct PDM_PARTITION* p_cur_part;       // offset 0x30, size 0x4
};

struct PDM_DISK_HANDLE {
    // total size: 0x8
    unsigned long signature;  // offset 0x0, size 0x4
    struct PDM_DISK* handle;  // offset 0x4, size 0x4
};
struct PDM_PARTITION_HANDLE {
    // total size: 0x8
    unsigned long signature;       // offset 0x0, size 0x4
    struct PDM_PARTITION* handle;  // offset 0x4, size 0x4
};

#endif  // VF_PDM_UNSORTED_STRUCTS_H
