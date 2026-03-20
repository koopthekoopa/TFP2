#ifndef VF_PDM_MBR_H
#define VF_PDM_MBR_H

#include <private/vf/pf_types.h>

struct PDM_MBR {
    // total size: 0x58
    unsigned long current_sector;            // offset 0x0, size 0x4
    unsigned long epbr_base_sector;          // offset 0x4, size 0x4
    struct PDM_PART_TBL partition_table[4];  // offset 0x8, size 0x50
};

struct PDM_MBR_SEC {
    // total size: 0x200
    unsigned char bootprg[446];       // offset 0x0, size 0x1BE
    unsigned char partition_tbl[64];  // offset 0x1BE, size 0x40
    unsigned char signature1;         // offset 0x1FE, size 0x1
    unsigned char signature2;         // offset 0x1FF, size 0x1
};

long VFipdm_mbr_get_table(unsigned char* buf /* r3 */, unsigned long sector /* r4 */, struct PDM_MBR* p_mbr_tbl /* r5 */);
long VFipdm_mbr_get_mbr_part_table(struct PDM_DISK* p_disk /* r30 */, struct PDM_MBR* p_mbr_tbl /* r29 */);
long VFipdm_mbr_get_epbr_part_table(struct PDM_DISK* p_disk /* r27 */, struct PDM_MBR* p_mbr_tbl /* r30 */);
long VFipdm_mbr_check_master_boot_record(struct PDM_DISK* p_disk /* r25 */, unsigned char* buf /* r26 */, unsigned long* is_master_boot /* r31 */);

#endif  // VF_PDM_MBR_H
