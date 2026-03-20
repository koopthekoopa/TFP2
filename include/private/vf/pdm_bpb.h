#ifndef VF_PDM_BPB_H
#define VF_PDM_BPB_H

#include <private/vf/pdm_struct.h>

typedef struct PDM_BPB {
    // total size: 0x70
    pf_u8 oem_name[8];               // offset 0x0, size 0x8
    pf_u16 bytes_per_sector;         // offset 0x8, size 0x2
    pf_u8 sectors_per_cluster;       // offset 0xA, size 0x1
    pf_u8 num_FATs;                  // offset 0xB, size 0x1
    pf_u16 num_reserved_sectors;     // offset 0xC, size 0x2
    pf_u16 num_root_dir_entries;     // offset 0xE, size 0x2
    pf_u16 total_sectors16;          // offset 0x10, size 0x2
    pf_u16 sectors_per_FAT16;        // offset 0x12, size 0x2
    pf_u16 sector_per_track;         // offset 0x14, size 0x2
    pf_u32 num_hidden_sectors;       // offset 0x18, size 0x4
    pf_u32 total_sectors32;          // offset 0x1C, size 0x4
    pf_u16 num_heads;                // offset 0x20, size 0x2
    pf_u8 media;                     // offset 0x22, size 0x1
    pf_u8 drive;                     // offset 0x23, size 0x1
    pf_u32 vol_id;                   // offset 0x24, size 0x4
    pf_u8 boot_sig;                  // offset 0x28, size 0x1
    pf_u8 vol_label[11];             // offset 0x29, size 0xB
    pf_u8 fs_type[8];                // offset 0x34, size 0x8
    pf_u32 sectors_per_FAT32;        // offset 0x3C, size 0x4
    pf_u16 ext_flags;                // offset 0x40, size 0x2
    pf_u16 fs_version;               // offset 0x42, size 0x2
    pf_u32 root_dir_cluster;         // offset 0x44, size 0x4
    pf_u16 fs_info_sector;           // offset 0x48, size 0x2
    pf_u16 backup_boot_sector;       // offset 0x4A, size 0x2
    pf_u8 jump_boot[3];              // offset 0x4C, size 0x3
    pf_u8 num_active_FATs;           // offset 0x4F, size 0x1
    PDM_FAT_TYPE fat_type;           // offset 0x50, size 0x4
    pf_u8 log2_bytes_per_sector;     // offset 0x54, size 0x1
    pf_u8 log2_sectors_per_cluster;  // offset 0x55, size 0x1
    pf_u16 num_root_dir_sectors;     // offset 0x56, size 0x2
    pf_u32 active_FAT_sector;        // offset 0x58, size 0x4
    pf_u32 first_root_dir_sector;    // offset 0x5C, size 0x4
    pf_u32 first_data_sector;        // offset 0x60, size 0x4
    pf_u32 num_clusters;             // offset 0x64, size 0x4
    pf_u32 total_sectors;            // offset 0x68, size 0x4
    pf_u32 sectors_per_FAT;          // offset 0x6C, size 0x4
} PDM_BPB;

pf_s32 VFipdm_bpb_load_string(const pf_u8* buf, pf_u32 length, pf_u8* p_string);
pf_s32 VFipdm_bpb_get_bpb_information(pf_u8* buf, PDM_BPB* p_bpb);
pf_s32 VFipdm_bpb_get_fsinfo_information(pf_u8* buf, PDM_FSINFO* p_fsinfo);
pf_s32 VFipdm_bpb_set_fsinfo_information(PDM_FSINFO* p_fsinfo, pf_u8* buf);
pf_s32 VFipdm_bpb_check_boot_sector(pf_u8* buf, pf_u32* is_boot);
pf_s32 VFipdm_bpb_check_fsinfo_sector(pf_u8* buf, pf_u32* is_fsinfo);

#endif  // VF_PDM_BPB_H
