#ifndef VF_PDM_PARTITION_H
#define VF_PDM_PARTITION_H

#include <private/vf/pf_types.h>

long VFipdm_part_open_partition(struct PDM_DISK* p_disk /* r29 */, unsigned short part_id /* r1+0x8 */, struct PDM_PARTITION** pp_part /* r30 */);
long VFipdm_part_close_partition(struct PDM_PARTITION* p_part /* r29 */);
long VFipdm_part_get_permission(struct PDM_PARTITION* p_part /* r29 */);
long VFipdm_part_release_permission(struct PDM_PARTITION* p_part /* r28 */, unsigned long mode /* r27 */);
long VFipdm_part_format(struct PDM_PARTITION* p_part /* r29 */, const unsigned char* param /* r1+0x8 */);
long VFipdm_part_logical_read(struct PDM_PARTITION* p_part /* r27 */, unsigned char* buf /* r22 */, unsigned long lsector /* r28 */,
                              unsigned long num_sector /* r29 */, unsigned short bps /* r24 */, unsigned long* p_num_success /* r23 */);
long VFipdm_part_logical_write(struct PDM_PARTITION* p_part /* r27 */, const unsigned char* buf /* r22 */, unsigned long lsector /* r28 */,
                               unsigned long num_sector /* r29 */, unsigned short bps /* r24 */, unsigned long* p_num_success /* r23 */);
long VFipdm_part_get_media_information(struct PDM_PARTITION* p_part /* r29 */, struct PDM_DISK_INFO* p_disk_info /* r28 */);
long VFipdm_part_check_media_write_protect(struct PDM_PARTITION* p_part /* r28 */, unsigned long* is_wprotect /* r31 */);
long VFipdm_part_check_media_insert(struct PDM_PARTITION* p_part /* r28 */, unsigned long* is_insert /* r31 */);
long VFipdm_part_check_media_detect(struct PDM_PARTITION* p_part /* r28 */, unsigned long* is_detect /* r31 */);
void VFipdm_part_set_change_media_state(struct PDM_DISK* p_disk /* r3 */, unsigned long event /* r4 */);
void VFipdm_part_set_driver_error_code(struct PDM_PARTITION* p_part /* r3 */, long error_code /* r4 */);
long VFipdm_part_get_driver_error_code(struct PDM_PARTITION* p_part /* r3 */);

#endif  // VF_PDM_PARTITION_H
