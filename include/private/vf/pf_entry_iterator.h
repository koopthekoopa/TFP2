#ifndef VF_PF_ENTRY_ITERATOR_H
#define VF_PF_ENTRY_ITERATOR_H

#include <private/vf/pf_entry.h>
#include <private/vf/pf_str.h>
#include <private/vf/pf_types.h>

struct PF_ENT_ITER {
    // total size: 0x70
    pf_u32 index;                   // offset 0x0, size 0x4
    PF_VOLUME* p_vol;               // offset 0x4, size 0x4
    struct PF_FFD ffd;              // offset 0x8, size 0x38
    pf_u32 file_sector_index;       // offset 0x40, size 0x4
    pf_u32 sector;                  // offset 0x44, size 0x4
    pf_u16 offset;                  // offset 0x48, size 0x2
    pf_u16 offset_mask;             // offset 0x4A, size 0x2
    pf_u8 buf[32];                  // offset 0x4C, size 0x20
    pf_u8 log2_entries_per_sector;  // offset 0x6C, size 0x1
};

pf_s32 VFiPFENT_ITER_IteratorInitialize(PF_ENT_ITER* p_iter, pf_u32 index_start_from);
pf_u32 VFiPFENT_ITER_IsAtLogicalEnd(PF_ENT_ITER* p_iter);
pf_s32 VFiPFENT_ITER_MoveTo(PF_ENT_ITER* p_iter, pf_u32 index, pf_u32 may_allocate);
pf_s32 VFiPFENT_ITER_Advance(PF_ENT_ITER* p_iter, pf_u32 may_allocate);
pf_s32 VFiPFENT_ITER_Retreat(PF_ENT_ITER* p_iter, pf_u32 may_allocate);
pf_s32 VFiPFENT_ITER_FindEntry(PF_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, PF_STR* p_pattern, pf_u8 attr_required, pf_u8 attr_unwanted,
                               pf_u32* p_is_found, pf_u32 is_skip);
pf_s32 VFiPFENT_ITER_GetEntryOfPath(PF_ENT_ITER* p_iter, PF_DIR_ENT* p_ent, PF_VOLUME* p_vol, PF_STR* p_path, pf_u32 no_look_last_token);

#endif  // VF_PF_ENTRY_ITERATOR_H
