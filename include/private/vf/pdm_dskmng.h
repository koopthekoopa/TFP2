#ifndef VF_PDM_DISK_MANAGER_H
#define VF_PDM_DISK_MANAGER_H

#include <private/vf/pf_types.h>

struct PDM_DISK_SET {
    // total size: 0xB64
    unsigned short num_partition; // offset 0x0, size 0x2
    unsigned short num_allocated_disk; // offset 0x2, size 0x2
    struct PDM_DISK_HANDLE disk_handle[26]; // offset 0x4, size 0xD0
    struct PDM_PARTITION_HANDLE partition_handle[26]; // offset 0xD4, size 0xD0
    struct PDM_DISK disk[26]; // offset 0x1A4, size 0x548
    struct PDM_PARTITION partition[26]; // offset 0x6EC, size 0x478
};

struct PDM_DISK_SET VFipdm_disk_set; // size: 0xB64, address: 0x80889A98
// Range: 0x803C4654 -> 0x803C46F0
long VFipdm_init_diskmanager(unsigned long config /* r1+0x8 */, void * param /* r1+0xC */);
long VFipdm_open_disk(struct PDM_INIT_DISK * p_init_disk_tbl /* r1+0x8 */, struct PDM_DISK * * pp_disk /* r30 */);
long VFipdm_close_disk(struct PDM_DISK * p_disk /* r30 */);
long VFipdm_open_partition(struct PDM_DISK * p_disk /* r29 */, long part_id /* r1+0x8 */, struct PDM_PARTITION * * pp_part /* r30 */);
long VFipdm_close_partition(struct PDM_PARTITION * p_part /* r30 */);

#endif // VF_PDM_DISK_MANAGER_H
