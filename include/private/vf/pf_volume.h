#ifndef VF_PF_VOLUME_H
#define VF_PF_VOLUME_H

// unsorted structs
#include <private/vf/pf_cache.h>
#include <private/vf/pf_entry.h>
#include <private/vf/pf_types.h>

typedef struct PF_BPB {
    // total size: 0x38
    pf_u16 bytes_per_sector;         // offset 0x0, size 0x2
    pf_u16 num_reserved_sectors;     // offset 0x2, size 0x2
    pf_u16 num_root_dir_entries;     // offset 0x4, size 0x2
    pf_u8 sectors_per_cluster;       // offset 0x6, size 0x1
    pf_u8 num_FATs;                  // offset 0x7, size 0x1
    pf_u32 total_sectors;            // offset 0x8, size 0x4
    pf_u32 sectors_per_FAT;          // offset 0xC, size 0x4
    pf_u32 root_dir_cluster;         // offset 0x10, size 0x4
    pf_u16 fs_info_sector;           // offset 0x14, size 0x2
    pf_u16 backup_boot_sector;       // offset 0x16, size 0x2
    pf_u16 ext_flags;                // offset 0x18, size 0x2
    pf_u8 media;                     // offset 0x1A, size 0x1
    PF_FAT_TYPE fat_type;            // offset 0x1C, size 0x4
    pf_u8 log2_bytes_per_sector;     // offset 0x20, size 0x1
    pf_u8 log2_sectors_per_cluster;  // offset 0x21, size 0x1
    pf_u8 num_active_FATs;           // offset 0x22, size 0x1
    pf_u16 num_root_dir_sectors;     // offset 0x24, size 0x2
    pf_u32 active_FAT_sector;        // offset 0x28, size 0x4
    pf_u32 first_root_dir_sector;    // offset 0x2C, size 0x4
    pf_u32 first_data_sector;        // offset 0x30, size 0x4
    pf_u32 num_clusters;             // offset 0x34, size 0x4
} PF_BPB;

typedef struct PF_CURSOR {
    // total size: 0x10
    pf_u32 position;           // offset 0x0, size 0x4
    pf_u32 sector;             // offset 0x4, size 0x4
    pf_u32 file_sector_index;  // offset 0x8, size 0x4
    pf_u16 offset_in_sector;   // offset 0xC, size 0x2
} PF_CURSOR;

typedef struct PF_SFD PF_SFD;
typedef struct PF_FILE {
    // total size: 0x30
    pf_u32 stat;        // offset 0x0, size 0x4
    pf_s32 open_mode;   // offset 0x4, size 0x4
    PF_SFD* p_sfd;      // offset 0x8, size 0x4
    PF_FAT_HINT hint;   // offset 0xC, size 0xC
    pf_s32 last_error;  // offset 0x18, size 0x4
    PF_CURSOR cursor;   // offset 0x1C, size 0x10
    pf_u16 lock_count;  // offset 0x2C, size 0x2
} PF_FILE;

typedef struct PF_INFO {
    // total size: 0x20
    pf_u32 file_size;       // offset 0x0, size 0x4
    pf_u32 io_pointer;      // offset 0x4, size 0x4
    pf_u32 empty_size;      // offset 0x8, size 0x4
    pf_u32 allocated_size;  // offset 0xC, size 0x4
    pf_u32 lock_mode;       // offset 0x10, size 0x4
    PF_FILE* lock_owner;    // offset 0x14, size 0x4
    pf_u32 lock_count;      // offset 0x18, size 0x4
    pf_u32 lock_tcount;     // offset 0x1C, size 0x4
} PF_INFO;

typedef struct PF_DIR_CURSOR {
    // total size: 0xC
    pf_u32 physical_entry_index;  // offset 0x0, size 0x4
    pf_u32 logical_entry_index;   // offset 0x4, size 0x4
    pf_u32 logical_seek_index;    // offset 0x8, size 0x4
} PF_DIR_CURSOR;

typedef struct PF_LOCK {
    // total size: 0x10
    pf_u16 mode;      // offset 0x0, size 0x2
    pf_u16 count;     // offset 0x2, size 0x2
    pf_u32 wcount;    // offset 0x4, size 0x4
    PF_FILE* owner;   // offset 0x8, size 0x4
    pf_s32 resource;  // offset 0xC, size 0x4
} PF_LOCK;

typedef struct PF_CUR_VOLUME {
    // total size: 0xC
    pf_u32 stat;        // offset 0x0, size 0x4
    pf_s32 context_id;  // offset 0x4, size 0x4
    PF_VOLUME* p_vol;   // offset 0x8, size 0x4
} PF_CUR_VOLUME;

struct PF_SFD {
    // total size: 0x290
    pf_u32 stat;           // offset 0x0, size 0x4
    PF_FFD ffd;            // offset 0x4, size 0x38
    PF_DIR_ENT dir_entry;  // offset 0x3C, size 0x240
    PF_LOCK lock;          // offset 0x27C, size 0x10
    pf_u16 num_handlers;   // offset 0x28C, size 0x2
};

typedef struct PF_SDD {
    // total size: 0x280
    pf_u32 stat;           // offset 0x0, size 0x4
    pf_u16 num_handlers;   // offset 0x4, size 0x2
    PF_FFD ffd;            // offset 0x8, size 0x38
    PF_DIR_ENT dir_entry;  // offset 0x40, size 0x240
} PF_SDD;

typedef struct PF_DIR_TAIL {
    // total size: 0xC
    pf_u32 tracker_size;     // offset 0x0, size 0x4
    pf_u32 tracker_buff[1];  // offset 0x4, size 0x4
    pf_u32* tracker_bits;    // offset 0x8, size 0x4
} PF_DIR_TAIL;

typedef struct PF_CUR_DIR {
    // total size: 0x248
    pf_u32 stat;                  // offset 0x0, size 0x4
    pf_s32 context_id;            // offset 0x4, size 0x4
    struct PF_DIR_ENT directory;  // offset 0x8, size 0x240
} PF_CUR_DIR;

typedef struct PF_DIR {
    // total size: 0x20
    pf_u32 stat;           // offset 0x0, size 0x4
    PF_SDD* p_sdd;         // offset 0x4, size 0x4
    PF_FAT_HINT hint;      // offset 0x8, size 0xC
    PF_DIR_CURSOR cursor;  // offset 0x14, size 0xC
} PF_DIR;

/*typedef*/ struct PF_VOLUME {
    // total size: 0x1898
    PF_BPB bpb;                        // offset 0x0, size 0x38
    pf_u32 num_free_clusters;          // offset 0x38, size 0x4
    pf_u32 last_free_cluster;          // offset 0x3C, size 0x4
    PF_SFD sfds[5];                    // offset 0x40, size 0xCD0
    PF_FILE ufds[5];                   // offset 0xD10, size 0xF0
    PF_SDD sdds[3];                    // offset 0xE00, size 0x780
    PF_DIR udds[3];                    // offset 0x1580, size 0x60
    pf_s32 num_opened_files;           // offset 0x15E0, size 0x4
    pf_s32 num_opened_directories;     // offset 0x15E4, size 0x4
    PF_SECTOR_CACHE cache;             // offset 0x15E8, size 0x24
    pf_s8 label[12];                   // offset 0x160C, size 0xC
    PF_CUR_DIR current_dir[1];         // offset 0x1618, size 0x248
    PF_DIR_TAIL tail_entry;            // offset 0x1860, size 0xC
    pf_s32 last_error;                 // offset 0x186C, size 0x4
    pf_s32 last_driver_error;          // offset 0x1870, size 0x4
    pf_u32 file_config;                // offset 0x1874, size 0x4
    pf_u16 flags;                      // offset 0x1878, size 0x2
    pf_s8 drv_char;                    // offset 0x187A, size 0x1
    pf_u16 fsi_flag;                   // offset 0x187C, size 0x2
    PF_CLUSTER_LINK_VOL cluster_link;  // offset 0x1880, size 0xC
    void* p_part;                      // offset 0x188C, size 0x4
    void (*p_callback)();              // offset 0x1890, size 0x4
    const pf_u8* format_param;         // offset 0x1894, size 0x4
} /*PF_VOLUME*/;

typedef struct PF_VOLUME_SET {
    // total size: 0x27FB8
    PF_CUR_VOLUME current_vol[1];  // offset 0x0, size 0xC
    pf_s32 num_attached_drives;    // offset 0xC, size 0x4
    pf_s32 num_mounted_volumes;    // offset 0x10, size 0x4
    pf_u32 config;                 // offset 0x14, size 0x4
    void* param;                   // offset 0x18, size 0x4
    pf_s32 last_error;             // offset 0x1C, size 0x4
    pf_s32 last_driver_error;      // offset 0x20, size 0x4
    PF_CHARCODE codeset;           // offset 0x24, size 0x18
    pf_u32 setting;                // offset 0x3C, size 0x4
    PF_CONTEXT context[1];         // offset 0x40, size 0x8
    PF_VOLUME volumes[26];         // offset 0x48, size 0x27F70
} PF_VOLUME_SET;

extern PF_VOLUME_SET VFipf_vol_set;

pf_s32 VFiPFVOL_InitModule(pf_u32 config, void* param);
pf_s32 VFiPFVOL_CheckForRead(PF_VOLUME* p_vol);
pf_s32 VFiPFVOL_CheckForWrite(PF_VOLUME* p_vol);
pf_s32 VFiPFVOL_GetCurrentDir(PF_VOLUME* p_vol, PF_DIR_ENT* p_current_dir);
void VFiPFVOL_SetCurrentVolume(PF_VOLUME* p_vol);
PF_VOLUME* VFiPFVOL_GetCurrentVolume();
PF_VOLUME* VFiPFVOL_GetVolumeFromDrvChar(pf_s8 drv_char);
void VFiPFVOL_LoadVolumeLabelFromBuf(const pf_u8* buf, PF_VOLUME* p_vol);
pf_s32 VFiPFVOL_getdev(pf_s8 drv_char, PF_DEV_INF* dev_inf);
pf_s32 VFiPFVOL_attach(PF_DRV_TBL* p_drv);
pf_s32 VFiPFVOL_detach(pf_s8 drv_char);
pf_s32 VFiPFVOL_format(pf_s8 drv_char, const pf_u8* param);
pf_s32 VFiPFVOL_unmount(pf_s8 drv_char, pf_u32 mode);

#endif  // VF_PF_VOLUME_H
