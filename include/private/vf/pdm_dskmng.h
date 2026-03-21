#ifndef VF_PDM_DISK_MANAGER_H
#define VF_PDM_DISK_MANAGER_H

#include <private/vf/pdm_struct.h>

typedef struct PDM_PARTITION PDM_PARTITION;

struct PDM_PARTITION {
    // total size: 0x2C
    pf_u32 status;                    // offset 0x0, size 0x4
    PDM_DISK* p_disk;                 // offset 0x4, size 0x4
    pf_u32 signature;                 // offset 0x8, size 0x4
    pf_u16 part_id;                   // offset 0xC, size 0x2
    pf_u16 open_part_cnt;             // offset 0xE, size 0x2
    PDM_PARTITION* part_lock_handle;  // offset 0x10, size 0x4
    pf_u32 start_sector;              // offset 0x14, size 0x4
    pf_u32 total_sector;              // offset 0x18, size 0x4
    pf_u32 mbr_sector;                // offset 0x1C, size 0x4
    pf_u8 partition_type;             // offset 0x20, size 0x1
    pf_s32 driver_last_error;         // offset 0x24, size 0x4
    void* p_vol;                      // offset 0x28, size 0x4
};

/*typedef*/ struct PDM_DISK {
    // total size: 0x34
    pf_u32 status;                   // offset 0x0, size 0x4
    PDM_DISK_TBL disk_tbl;           // offset 0x4, size 0x8
    pf_u32 signature;                // offset 0xC, size 0x4
    pf_u16 open_disk_cnt;            // offset 0x10, size 0x2
    pf_u16 disk_lock_cnt;            // offset 0x12, size 0x2
    PDM_DISK* disk_lock_handle;      // offset 0x14, size 0x4
    PDM_DISK_INFO disk_info;         // offset 0x18, size 0x14
    PDM_INIT_DISK* p_init_disk_tbl;  // offset 0x2C, size 0x4
    PDM_PARTITION* p_cur_part;       // offset 0x30, size 0x4
} /*PDM_DISK*/;

typedef struct PDM_DISK_HANDLE {
    // total size: 0x8
    pf_u32 signature;  // offset 0x0, size 0x4
    PDM_DISK* handle;  // offset 0x4, size 0x4
} PDM_DISK_HANDLE;

typedef struct PDM_PARTITION_HANDLE {
    // total size: 0x8
    pf_u32 signature;       // offset 0x0, size 0x4
    PDM_PARTITION* handle;  // offset 0x4, size 0x4
} PDM_PARTITION_HANDLE;

typedef struct PDM_DISK_SET {
    // total size: 0xB64
    pf_u16 num_partition;                       // offset 0x0, size 0x2
    pf_u16 num_allocated_disk;                  // offset 0x2, size 0x2
    PDM_DISK_HANDLE disk_handle[26];            // offset 0x4, size 0xD0
    PDM_PARTITION_HANDLE partition_handle[26];  // offset 0xD4, size 0xD0
    PDM_DISK disk[26];                          // offset 0x1A4, size 0x548
    PDM_PARTITION partition[26];                // offset 0x6EC, size 0x478
} PDM_DISK_SET;

extern PDM_DISK_SET VFipdm_disk_set;

pf_s32 VFipdm_init_diskmanager(pf_u32 config, void* param);
pf_s32 VFipdm_open_disk(PDM_INIT_DISK* p_init_disk_tbl, PDM_DISK** pp_disk);
pf_s32 VFipdm_close_disk(PDM_DISK* p_disk);
pf_s32 VFipdm_open_partition(PDM_DISK* p_disk, pf_s32 part_id, PDM_PARTITION** pp_part);
pf_s32 VFipdm_close_partition(PDM_PARTITION* p_part);

#endif  // VF_PDM_DISK_MANAGER_H
