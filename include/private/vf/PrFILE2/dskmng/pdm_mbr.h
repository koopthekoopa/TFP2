#ifndef PRFILE2_VFMOD_PDM_MBR_H
#define PRFILE2_VFMOD_PDM_MBR_H

#include <private/vf/PrFILE2/dskmng/pdm_struct.h>

typedef struct PDM_MBR {
    // total size: 0x58
    pf_u32 current_sector;            // offset 0x0, size 0x4
    pf_u32 epbr_base_sector;          // offset 0x4, size 0x4
    PDM_PART_TBL partition_table[4];  // offset 0x8, size 0x50
} PDM_MBR;

typedef struct PDM_MBR_SEC {
    // total size: 0x200
    pf_u8 bootprg[446];       // offset 0x0, size 0x1BE
    pf_u8 partition_tbl[64];  // offset 0x1BE, size 0x40
    pf_u8 signature1;         // offset 0x1FE, size 0x1
    pf_u8 signature2;         // offset 0x1FF, size 0x1
} PDM_MBR_SEC;

pf_s32 VFipdm_mbr_get_table(pf_u8* buf, pf_u32 sector, PDM_MBR* p_mbr_tbl);
pf_s32 VFipdm_mbr_get_mbr_part_table(PDM_DISK* p_disk, PDM_MBR* p_mbr_tbl);
pf_s32 VFipdm_mbr_get_epbr_part_table(PDM_DISK* p_disk, PDM_MBR* p_mbr_tbl);
pf_s32 VFipdm_mbr_check_master_boot_record(PDM_DISK* p_disk, pf_u8* buf, pf_u32* is_master_boot);

#endif  // PRFILE2_VFMOD_PDM_MBR_H
