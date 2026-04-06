#ifndef VF_PF_FILE_H
#define VF_PF_FILE_H

#include <private/vf/pf_entry.h>
#include <private/vf/pf_str.h>
#include <private/vf/pf_types.h>
#include <private/vf/pf_volume.h>

void VFiPFFILE_Cursor_MoveToEnd(PF_FILE* p_file);
void VFiPFFILE_Cursor_MoveToClusterEnd(PF_FILE* p_file, pf_u32 size);

pf_s32 VFiPFFILE_GetOpenedFile(struct PF_DIR_ENT* p_ent, struct PF_DIR_ENT** pp_open_ent);
pf_u32 VFiPFFILE_IsOpened(struct PF_DIR_ENT* p_ent);
void VFiPFFILE_FinalizeAllFiles(PF_VOLUME* p_vol);
pf_s32 VFiPFFILE_DoRemoveFile(struct PF_DIR_ENT* p_ent, struct PF_ENT_ITER* p_iter);
pf_s32 VFiPFFILE_RemoveFile(PF_VOLUME* p_vol, PF_DIR_ENT* p_ent, PF_ENT_ITER* p_iter);
pf_s32 VFiPFFILE_remove(PF_STR* p_path_str);
pf_s32 VFiPFFILE_fopen(PF_STR* p_path_str, pf_s32 mode, PF_FILE** pp_file);
pf_s32 VFiPFFILE_fclose(PF_FILE* p_file);
pf_s32 VFiPFFILE_fread(pf_u8* p_buf, pf_u32 size, pf_u32 count, PF_FILE* p_file, pf_u32* p_count_read);
pf_s32 VFiPFFILE_fwrite(pf_u8* p_buf, pf_u32 size, pf_u32 count, PF_FILE* p_file, pf_u32* p_count_written);
pf_s32 VFiPFFILE_fseek(PF_FILE* p_file, pf_s32 lOffset, pf_s32 nOrigin);
pf_s32 VFiPFFILE_finfo(PF_FILE* p_file, struct PF_INFO* p_info);

#endif  // VF_PF_FILE_H
