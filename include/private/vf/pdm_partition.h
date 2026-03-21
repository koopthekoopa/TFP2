#ifndef VF_PDM_PARTITION_H
#define VF_PDM_PARTITION_H

#include <private/vf/pdm_disk.h>
#include <private/vf/pdm_struct.h>

#define GET_PART_NO(p_part) ((pf_u32)p_part & 0xFF)

pf_s32 VFipdm_part_open_partition(PDM_DISK* p_disk, pf_u16 part_id, PDM_PARTITION** pp_part);
pf_s32 VFipdm_part_close_partition(PDM_PARTITION* p_part);
pf_s32 VFipdm_part_get_permission(PDM_PARTITION* p_part);
pf_s32 VFipdm_part_release_permission(PDM_PARTITION* p_part, pf_u32 mode);
pf_s32 VFipdm_part_format(PDM_PARTITION* p_part, const pf_u8* param);
pf_s32 VFipdm_part_logical_read(PDM_PARTITION* p_part, pf_u8* buf, pf_u32 lsector, pf_u32 num_sector, pf_u16 bps, pf_u32* p_num_success);
pf_s32 VFipdm_part_logical_write(PDM_PARTITION* p_part, const pf_u8* buf, pf_u32 lsector, pf_u32 num_sector, pf_u16 bps, pf_u32* p_num_success);
pf_s32 VFipdm_part_get_media_information(PDM_PARTITION* p_part, PDM_DISK_INFO* p_disk_info);
pf_s32 VFipdm_part_check_media_write_protect(PDM_PARTITION* p_part, pf_u32* is_wprotect);
pf_s32 VFipdm_part_check_media_insert(PDM_PARTITION* p_part, pf_u32* is_insert);
pf_s32 VFipdm_part_check_media_detect(PDM_PARTITION* p_part, pf_u32* is_detect);
void VFipdm_part_set_change_media_state(PDM_DISK* p_disk, pf_u32 event);
void VFipdm_part_set_driver_error_code(PDM_PARTITION* p_part, pf_s32 error_code);
pf_s32 VFipdm_part_get_driver_error_code(PDM_PARTITION* p_part);

#endif  // VF_PDM_PARTITION_H
