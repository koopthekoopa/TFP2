#ifndef VF_PF_FILE_H
#define VF_PF_FILE_H

#include <private/vf/pf_types.h>
#include <private/vf/pf_str.h>
#include <private/vf/pf_entry.h>

void VFiPFFILE_Cursor_MoveToEnd(struct PF_FILE * p_file /* r31 */);
void VFiPFFILE_Cursor_MoveToClusterEnd(struct PF_FILE * p_file /* r30 */, unsigned long size /* r1+0x8 */);

long VFiPFFILE_GetOpenedFile(struct PF_DIR_ENT * p_ent /* r3 */, struct PF_DIR_ENT * * pp_open_ent /* r4 */);
unsigned long VFiPFFILE_IsOpened(struct PF_DIR_ENT * p_ent /* r30 */);
void VFiPFFILE_FinalizeAllFiles(struct PF_VOLUME * p_vol /* r30 */);
long VFiPFFILE_DoRemoveFile(struct PF_DIR_ENT * p_ent /* r30 */, struct PF_ENT_ITER * p_iter /* r28 */);
long VFiPFFILE_RemoveFile(struct PF_VOLUME * p_vol /* r1+0x8 */, struct PF_DIR_ENT * p_ent /* r30 */, struct PF_ENT_ITER * p_iter /* r1+0xC */);
long VFiPFFILE_remove(struct PF_STR * p_path_str /* r29 */);
long VFiPFFILE_fopen(struct PF_STR * p_path_str /* r28 */, long mode /* r27 */, struct PF_FILE * * pp_file /* r29 */);
long VFiPFFILE_fread(unsigned char * p_buf /* r24 */, unsigned long size /* r25 */, unsigned long count /* r26 */, struct PF_FILE * p_file /* r31 */, unsigned long * p_count_read /* r28 */);
long VFiPFFILE_fwrite(unsigned char * p_buf /* r24 */, unsigned long size /* r25 */, unsigned long count /* r26 */, struct PF_FILE * p_file /* r31 */, unsigned long * p_count_written /* r28 */);
long VFiPFFILE_fseek(struct PF_FILE * p_file /* r31 */, long lOffset /* r26 */, long nOrigin /* r1+0x8 */);
long VFiPFFILE_finfo(struct PF_FILE * p_file /* r31 */, struct PF_INFO * p_info /* r27 */);

#endif // VF_PF_FILE_H
