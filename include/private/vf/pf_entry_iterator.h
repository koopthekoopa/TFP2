#ifndef VF_PF_ENTRY_ITERATOR_H
#define VF_PF_ENTRY_ITERATOR_H

#include <private/vf/pf_str.h>
#include <private/vf/pf_types.h>

typedef struct PF_ENT_ITER {
    // total size: 0x70
    unsigned long index;                    // offset 0x0, size 0x4
    struct PF_VOLUME* p_vol;                // offset 0x4, size 0x4
    struct PF_FFD ffd;                      // offset 0x8, size 0x38
    unsigned long file_sector_index;        // offset 0x40, size 0x4
    unsigned long sector;                   // offset 0x44, size 0x4
    unsigned short offset;                  // offset 0x48, size 0x2
    unsigned short offset_mask;             // offset 0x4A, size 0x2
    unsigned char buf[32];                  // offset 0x4C, size 0x20
    unsigned char log2_entries_per_sector;  // offset 0x6C, size 0x1
} PF_ENT_ITER;

long VFiPFENT_ITER_IteratorInitialize(struct PF_ENT_ITER* p_iter /* r31 */, unsigned long index_start_from /* r1+0x8 */);
unsigned long VFiPFENT_ITER_IsAtLogicalEnd(struct PF_ENT_ITER* p_iter /* r31 */);
long VFiPFENT_ITER_MoveTo(struct PF_ENT_ITER* p_iter /* r30 */, unsigned long index /* r28 */, unsigned long may_allocate /* r29 */);
long VFiPFENT_ITER_Advance(struct PF_ENT_ITER* p_iter /* r31 */, unsigned long may_allocate /* r1+0x8 */);
long VFiPFENT_ITER_Retreat(struct PF_ENT_ITER* p_iter /* r31 */, unsigned long may_allocate /* r28 */);
long VFiPFENT_ITER_FindEntry(struct PF_ENT_ITER* p_iter /* r1+0x8 */, struct PF_DIR_ENT* p_ent /* r26 */, struct PF_STR* p_pattern /* r29 */,
                             unsigned char attr_required /* r27 */, unsigned char attr_unwanted /* r28 */, unsigned long* p_is_found /* r30 */,
                             unsigned long is_skip /* r1+0xC */);
long VFiPFENT_ITER_GetEntryOfPath(struct PF_ENT_ITER* p_iter /* r1+0x8 */, struct PF_DIR_ENT* p_ent /* r1+0xC */,
                                  struct PF_VOLUME* p_vol /* r1+0x10 */, struct PF_STR* p_path /* r1+0x14 */,
                                  unsigned long no_look_last_token /* r1+0x18 */);

#endif  // VF_PF_ENTRY_ITERATOR_H
