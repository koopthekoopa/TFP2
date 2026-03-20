#ifndef VF_PDM_BPB_H
#define VF_PDM_BPB_H

#include <private/vf/pf_types.h>

struct PDM_BPB {
    // total size: 0x70
    unsigned char oem_name[8]; // offset 0x0, size 0x8
    unsigned short bytes_per_sector; // offset 0x8, size 0x2
    unsigned char sectors_per_cluster; // offset 0xA, size 0x1
    unsigned char num_FATs; // offset 0xB, size 0x1
    unsigned short num_reserved_sectors; // offset 0xC, size 0x2
    unsigned short num_root_dir_entries; // offset 0xE, size 0x2
    unsigned short total_sectors16; // offset 0x10, size 0x2
    unsigned short sectors_per_FAT16; // offset 0x12, size 0x2
    unsigned short sector_per_track; // offset 0x14, size 0x2
    unsigned long num_hidden_sectors; // offset 0x18, size 0x4
    unsigned long total_sectors32; // offset 0x1C, size 0x4
    unsigned short num_heads; // offset 0x20, size 0x2
    unsigned char media; // offset 0x22, size 0x1
    unsigned char drive; // offset 0x23, size 0x1
    unsigned long vol_id; // offset 0x24, size 0x4
    unsigned char boot_sig; // offset 0x28, size 0x1
    unsigned char vol_label[11]; // offset 0x29, size 0xB
    unsigned char fs_type[8]; // offset 0x34, size 0x8
    unsigned long sectors_per_FAT32; // offset 0x3C, size 0x4
    unsigned short ext_flags; // offset 0x40, size 0x2
    unsigned short fs_version; // offset 0x42, size 0x2
    unsigned long root_dir_cluster; // offset 0x44, size 0x4
    unsigned short fs_info_sector; // offset 0x48, size 0x2
    unsigned short backup_boot_sector; // offset 0x4A, size 0x2
    unsigned char jump_boot[3]; // offset 0x4C, size 0x3
    unsigned char num_active_FATs; // offset 0x4F, size 0x1
    PDM_FAT_TYPE fat_type; // offset 0x50, size 0x4
    unsigned char log2_bytes_per_sector; // offset 0x54, size 0x1
    unsigned char log2_sectors_per_cluster; // offset 0x55, size 0x1
    unsigned short num_root_dir_sectors; // offset 0x56, size 0x2
    unsigned long active_FAT_sector; // offset 0x58, size 0x4
    unsigned long first_root_dir_sector; // offset 0x5C, size 0x4
    unsigned long first_data_sector; // offset 0x60, size 0x4
    unsigned long num_clusters; // offset 0x64, size 0x4
    unsigned long total_sectors; // offset 0x68, size 0x4
    unsigned long sectors_per_FAT; // offset 0x6C, size 0x4
};

long VFipdm_bpb_load_string(const unsigned char * buf /* r3 */, unsigned long length /* r4 */, unsigned char * p_string /* r5 */);
long VFipdm_bpb_get_bpb_information(unsigned char * buf /* r30 */, struct PDM_BPB * p_bpb /* r31 */);
long VFipdm_bpb_get_fsinfo_information(unsigned char * buf /* r3 */, struct PDM_FSINFO * p_fsinfo /* r4 */);
long VFipdm_bpb_set_fsinfo_information(struct PDM_FSINFO * p_fsinfo /* r3 */, unsigned char * buf /* r4 */);
long VFipdm_bpb_check_boot_sector(unsigned char * buf /* r3 */, unsigned long * is_boot /* r4 */);
long VFipdm_bpb_check_fsinfo_sector(unsigned char * buf /* r3 */, unsigned long * is_fsinfo /* r4 */);

#endif // VF_PDM_BPB_H
