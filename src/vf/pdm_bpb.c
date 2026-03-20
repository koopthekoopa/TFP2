#include <private/vf/pdm_bpb.h>

static void VFipdm_bpb_calculate_common_bpb_fields(struct PDM_BPB * p_bpb /* r3 */) {
    // Local variables
    unsigned long num_data_sectors; // r30
    unsigned short val; // r31

    p_bpb->log2_bytes_per_sector = 0;
    val = p_bpb->bytes_per_sector;

    while (val >>= 1) {
        p_bpb->log2_bytes_per_sector++;
    }

    p_bpb->log2_sectors_per_cluster = 0;
    val = p_bpb->sectors_per_cluster;
    while (val >>= 1) {
        p_bpb->log2_sectors_per_cluster++;
    }

    p_bpb->num_root_dir_sectors = ((p_bpb->num_root_dir_entries * 32) + (p_bpb->bytes_per_sector-1)) >> p_bpb->log2_bytes_per_sector;
    p_bpb->first_data_sector = (p_bpb->num_FATs * p_bpb->sectors_per_FAT) + (p_bpb->num_root_dir_sectors + p_bpb->num_reserved_sectors);
    num_data_sectors = p_bpb->total_sectors - p_bpb->first_data_sector;
    p_bpb->num_clusters = num_data_sectors >> p_bpb->log2_sectors_per_cluster;

    if (p_bpb->num_clusters < 0xFF5) {
        p_bpb->fat_type = PDM_FAT_12;
        return;
    }
    if (p_bpb->num_clusters < 0xFFF5) {
        p_bpb->fat_type = PDM_FAT_16;
        return;
    }
    p_bpb->fat_type = PDM_FAT_32;
}

// Range: 0x803C1308 -> 0x803C13B8
static void VFipdm_bpb_calculate_specific_bpb_fields(struct PDM_BPB * p_bpb /* r3 */) {
    switch (p_bpb->fat_type) {
        case PDM_FAT_12:
        case PDM_FAT_16: {
            p_bpb->first_root_dir_sector = p_bpb->num_reserved_sectors + (p_bpb->num_FATs * p_bpb->sectors_per_FAT);
            p_bpb->num_active_FATs = p_bpb->num_FATs;
            p_bpb->active_FAT_sector = p_bpb->num_reserved_sectors;
            break;
        }
        case PDM_FAT_32: {
            p_bpb->first_root_dir_sector = p_bpb->first_data_sector + ((p_bpb->root_dir_cluster - 2) << p_bpb->log2_sectors_per_cluster);
            if ((p_bpb->ext_flags & 0x80) != 0) {
                p_bpb->num_active_FATs = 1;
                p_bpb->active_FAT_sector = p_bpb->num_reserved_sectors + ((p_bpb->ext_flags & 7) * p_bpb->sectors_per_FAT);
                return;
            }
            p_bpb->num_active_FATs = p_bpb->num_FATs;
            p_bpb->active_FAT_sector = p_bpb->num_reserved_sectors;
            break;
        }
        default: {
            break;
        }
    }
}

// Range: 0x803C13B8 -> 0x803C140C
long VFipdm_bpb_load_string(const unsigned char * buf /* r3 */, unsigned long length /* r4 */, unsigned char * p_string /* r5 */) {
    // Local variables
    unsigned long i; // r31

    if (buf == PF_NULL || p_string == PF_NULL || length == 0) {
        return 1;
    }

    for (i = 0; i < length; i++) {
        p_string[i] = buf[i];
    }

    return 0;
}

// Range: 0x803C140C -> 0x803C1824
long VFipdm_bpb_get_bpb_information(unsigned char * buf /* r30 */, struct PDM_BPB * p_bpb /* r31 */) {
    // Local variables
    long err; // r29

    if ((buf == PF_NULL) || (p_bpb == PF_NULL)) {
        return 1;
    }
    err = 0;
    VFipdm_bpb_load_string(buf, 3U, p_bpb->jump_boot);
    VFipdm_bpb_load_string(buf + 3, 8U, p_bpb->oem_name);
    p_bpb->bytes_per_sector = (pf_u16)buf[11] | ((pf_u16)buf[12] << 8);
    p_bpb->sectors_per_cluster = buf[13];
    p_bpb->num_reserved_sectors = buf[14] | ((pf_u16)buf[15] << 8);
    p_bpb->num_FATs = buf[16];
    p_bpb->num_root_dir_entries = buf[17] | ((pf_u16)buf[18] << 8);
    p_bpb->total_sectors16 = buf[19] | ((pf_u16)buf[20] << 8);
    p_bpb->media = buf[21];
    p_bpb->sectors_per_FAT16 = buf[22] | ((pf_u16)buf[23] << 8);
    p_bpb->sector_per_track = buf[24] | ((pf_u16)buf[25] << 8);
    p_bpb->num_heads = buf[26] | ((pf_u16)buf[27] << 8);
    p_bpb->num_hidden_sectors = (buf[31] << 0x18) | ((buf[30] << 0x10) | (buf[28] | (buf[29] << 8)));
    p_bpb->total_sectors32 = (buf[35] << 0x18) | ((buf[34] << 0x10) | (buf[32] | (buf[33] << 8)));

    p_bpb->total_sectors = p_bpb->total_sectors16 == 0 ? p_bpb->total_sectors32 : p_bpb->total_sectors16;

    if (p_bpb->sectors_per_FAT16 == 0) {
        p_bpb->sectors_per_FAT32 = (buf[39] << 0x18) | ((buf[38] << 0x10) | (buf[36] | (buf[37] << 8)));
        p_bpb->sectors_per_FAT = p_bpb->sectors_per_FAT32;
    } else {
        p_bpb->sectors_per_FAT32 = 0;
        p_bpb->sectors_per_FAT = p_bpb->sectors_per_FAT16;
    }

    VFipdm_bpb_calculate_common_bpb_fields(p_bpb);

    switch (p_bpb->fat_type) {
        case PDM_FAT_12:
        case PDM_FAT_16: {
            if (p_bpb->sectors_per_FAT16 == 0) {
                err = 4;
            }
            p_bpb->ext_flags = 0;
            p_bpb->fs_version = 0;
            p_bpb->root_dir_cluster = 0;
            p_bpb->fs_info_sector = 0;
            p_bpb->backup_boot_sector = 0;
            p_bpb->drive = buf[0x24];
            p_bpb->boot_sig = buf[0x26];
            p_bpb->vol_id = ((buf[0x2A] << 0x18) | ((buf[0x29] << 0x10) | (buf[0x27] | (buf[0x28] << 8))));

            VFipdm_bpb_load_string(&buf[0x2B], 11, p_bpb->vol_label);
            VFipdm_bpb_load_string(&buf[0x36], 8, p_bpb->fs_type);

            break;
        }
        case PDM_FAT_32: {
            if (p_bpb->total_sectors16 != 0 || p_bpb->sectors_per_FAT16 != 0) {
                err = 4;
            }
            p_bpb->ext_flags = (buf[40] | ((pf_u16)buf[41] << 8));
            p_bpb->fs_version = (buf[0x2A] | ((pf_u16)buf[0x2B] << 8));
            p_bpb->root_dir_cluster = (buf[47] << 24) | ((buf[46] << 16) | (buf[44] | (buf[45] << 8)));
            p_bpb->fs_info_sector = (buf[48] | ((pf_u16)buf[49] << 8));
            p_bpb->backup_boot_sector = (buf[50] | ((pf_u16)buf[51] << 8));
            p_bpb->drive = buf[0x40];
            p_bpb->boot_sig = buf[0x42];
            p_bpb->vol_id = ((buf[0x46] << 0x18) | ((buf[0x45] << 0x10) | (buf[0x43] | (buf[0x44] << 8))));

            VFipdm_bpb_load_string(&buf[0x47], 11, p_bpb->vol_label);
            VFipdm_bpb_load_string(&buf[0x52], 8, p_bpb->fs_type);

            if (p_bpb->fs_version != 0) {
                err = 4;
            }
            break;
        }
        default: {
            err = 4;
            break;
        }
    }

    VFipdm_bpb_calculate_specific_bpb_fields(p_bpb);
    return err;
}

// Range: 0x803C1824 -> 0x803C189C
long VFipdm_bpb_get_fsinfo_information(unsigned char * buf /* r3 */, struct PDM_FSINFO * p_fsinfo /* r4 */) {

}

// Range: 0x803C189C -> 0x803C1994
long VFipdm_bpb_set_fsinfo_information(struct PDM_FSINFO * p_fsinfo /* r3 */, unsigned char * buf /* r4 */) {}

// Range: 0x803C1994 -> 0x803C1B58
long VFipdm_bpb_check_boot_sector(unsigned char * buf /* r3 */, unsigned long * is_boot /* r4 */) {
    // Local variables
    unsigned short byte_per_sector; // r29
    unsigned short sector_per_cluster; // r30
    unsigned char media; // r31
}

// Range: 0x803C1B58 -> 0x803C1C48
long VFipdm_bpb_check_fsinfo_sector(unsigned char * buf /* r3 */, unsigned long * is_fsinfo /* r4 */) {
    // Local variables
    unsigned long lead_sig; // r31
    unsigned long struct_sig; // r30
    unsigned long trail_sig; // r29
}
