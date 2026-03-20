#ifndef VF_PDM_DISK_H
#define VF_PDM_DISK_H

#include <private/vf/pf_types.h>
#include <private/vf/pdm_dskmng.h>

long VFipdm_disk_check_disk_handle(struct PDM_DISK * p_disk /* r31 */);
long VFipdm_disk_open_disk(struct PDM_INIT_DISK * p_init_disk_tbl /* r29 */, struct PDM_DISK * * pp_disk /* r30 */);
long VFipdm_disk_close_disk(struct PDM_DISK * p_disk /* r29 */);
long VFipdm_disk_get_part_permission(struct PDM_DISK * p_disk /* r30 */);
long VFipdm_disk_release_part_permission(struct PDM_DISK * p_disk /* r29 */, unsigned long mode /* r1+0x8 */);
long VFipdm_disk_physical_read(struct PDM_DISK * p_disk /* r28 */, unsigned char * buf /* r25 */, unsigned long psector /* r1+0x8 */, unsigned long num_sector /* r26 */, unsigned short bps /* r27 */, unsigned long * p_num_success /* r29 */);
long VFipdm_disk_physical_write(struct PDM_DISK * p_disk /* r28 */, const unsigned char * buf /* r25 */, unsigned long psector /* r1+0x8 */, unsigned long num_sector /* r26 */, unsigned short bps /* r27 */, unsigned long * p_num_success /* r29 */);
long VFipdm_disk_format(struct PDM_DISK * p_disk /* r29 */, const unsigned char * param /* r1+0x8 */);
long VFipdm_disk_get_lba_size(struct PDM_DISK * p_disk /* r28 */, unsigned short * p_lba_size /* r29 */);
long VFipdm_disk_get_media_information(struct PDM_DISK * p_disk /* r28 */, struct PDM_DISK_INFO * p_disk_info /* r29 */);
long VFipdm_disk_check_media_insert(struct PDM_DISK * p_disk /* r28 */, unsigned long * is_insert /* r31 */);
long VFipdm_disk_set_disk(struct PDM_DISK * p_disk /* r29 */, struct PDM_PARTITION * p_part /* r28 */);
void VFipdm_disk_notify_media_insert(struct PDM_DISK * p_disk /* r30 */);

#endif // VF_PDM_DISK_H
