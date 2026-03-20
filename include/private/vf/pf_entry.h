#ifndef VF_PF_ENTRY_H
#define VF_PF_ENTRY_H

#include <private/vf/pf_types.h>
#include <private/vf/pf_entry_iterator.h>

void VFiPFENT_SetDotEntry(unsigned char * entry /* r3 */);
void VFiPFENT_SetDotDotEntry(unsigned char * entry /* r3 */);
unsigned char VFiPFENT_CalcCheckSum(struct PF_DIR_ENT * p_ent /* r1+0x8 */);
void VFiPFENT_LoadShortNameFromBuf(struct PF_DIR_ENT * p_ent /* r31 */, const unsigned char * buf /* r30 */);
void VFiPFENT_loadEntryNumericFieldsFromBuf(struct PF_DIR_ENT * p_ent /* r3 */, const unsigned char * buf /* r4 */);
void VFiPFENT_StoreEntryNumericFieldsToBuf(unsigned char * buf /* r3 */, const struct PF_DIR_ENT * p_ent /* r4 */);
long VFiPFENT_LoadLFNEntryFieldsFromBuf(struct PF_DIR_ENT * p_ent /* r31 */, const unsigned char * buf /* r27 */);
void VFiPFENT_storeLFNEntryFieldsToBuf(unsigned char * buf /* r31 */, struct PF_DIR_ENT * p_ent /* r1+0x8 */, unsigned char ord /* r27 */, unsigned char sum /* r1+0xC */, unsigned long is_last /* r26 */);
long VFiPFENT_findEntryPos(struct PF_FFD * p_ffd /* r27 */, struct PF_DIR_ENT * p_ent /* r29 */, unsigned long index_search_from /* r1+0x8 */, struct PF_STR * p_pattern /* r26 */, unsigned char attr_required /* r23 */, unsigned char attr_unwanted /* r24 */, unsigned long * p_lpos /* r30 */, unsigned long * p_ppos /* r31 */);
long VFiPFENT_findEntry(struct PF_FFD * p_ffd /* r1+0x8 */, struct PF_DIR_ENT * p_ent /* r1+0xC */, unsigned long index_search_from /* r1+0x10 */, struct PF_STR * p_pattern /* r1+0x14 */, unsigned char attr_required /* r1+0x18 */, unsigned char attr_unwanted /* r1+0x19 */);
long VFiPFENT_allocateEntryPos(struct PF_DIR_ENT * p_ent /* r27 */, unsigned char num_entries /* r24 */, struct PF_FFD * p_ffd /* r31 */, unsigned long * p_next_chain /* r28 */, struct PF_STR * p_filename /* r22 */, unsigned long * p_pos /* r23 */);
long VFiPFENT_allocateEntry(struct PF_DIR_ENT * p_ent /* r1+0x8 */, unsigned char num_entries /* r1+0xC */, struct PF_FFD * p_ffd /* r1+0x10 */, unsigned long * p_next_chain /* r1+0x14 */, struct PF_STR * p_filename /* r1+0x18 */);
long VFiPFENT_GetRootDir(struct PF_VOLUME * p_vol /* r3 */, struct PF_DIR_ENT * p_ent /* r4 */);
long VFiPFENT_MakeRootDir(struct PF_VOLUME * p_vol /* r31 */);
long VFiPFENT_updateEntry(struct PF_DIR_ENT * p_ent /* r31 */, unsigned long flag /* r1+0x8 */);
long VFiPFENT_AdjustSFN(struct PF_DIR_ENT * p_ent /* r1+0x8 */, signed char * p_short_name /* r30 */);
long VFiPFENT_RemoveEntry(struct PF_DIR_ENT * p_ent /* r31 */, struct PF_ENT_ITER * p_iter /* r28 */);
unsigned char VFiPFENT_getcurrentDateTimeForEnt(unsigned short * p_date /* r30 */, unsigned short * p_time /* r31 */);

#endif // VF_PF_ENTRY_H
