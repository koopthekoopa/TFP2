#ifndef VF_PF_ENTRY_H
#define VF_PF_ENTRY_H

#include <private/vf/pf_fat.h>
#include <private/vf/pf_types.h>

typedef struct PF_ENT_ITER PF_ENT_ITER;

typedef struct PF_DIR_ENT {
    // total size: 0x240
    pf_u16 long_name[261];    // offset 0x0, size 0x20A
    pf_u8 num_entry_LFNs;     // offset 0x20A, size 0x1
    pf_u8 ordinal;            // offset 0x20B, size 0x1
    pf_u8 check_sum;          // offset 0x20C, size 0x1
    pf_u8 align_pad[1];       // offset 0x20D, size 0x1
    pf_s8 short_name[13];     // offset 0x20E, size 0xD
    pf_u8 small_letter_flag;  // offset 0x21B, size 0x1
    pf_u8 attr;               // offset 0x21C, size 0x1
    pf_u8 create_time_ms;     // offset 0x21D, size 0x1
    pf_u16 create_time;       // offset 0x21E, size 0x2
    pf_u16 create_date;       // offset 0x220, size 0x2
    pf_u16 access_date;       // offset 0x222, size 0x2
    pf_u16 modify_time;       // offset 0x224, size 0x2
    pf_u16 modify_date;       // offset 0x226, size 0x2
    pf_u32 file_size;         // offset 0x228, size 0x4
    PF_VOLUME* p_vol;         // offset 0x22C, size 0x4
    pf_u32 path_len;          // offset 0x230, size 0x4
    pf_u32 start_cluster;     // offset 0x234, size 0x4
    pf_u32 entry_sector;      // offset 0x238, size 0x4
    pf_u16 entry_offset;      // offset 0x23C, size 0x2
} PF_DIR_ENT;

void VFiPFENT_SetDotEntry(pf_u8* entry);
void VFiPFENT_SetDotDotEntry(pf_u8* entry);
pf_u8 VFiPFENT_CalcCheckSum(PF_DIR_ENT* p_ent);
void VFiPFENT_LoadShortNameFromBuf(PF_DIR_ENT* p_ent, const pf_u8* buf);
void VFiPFENT_loadEntryNumericFieldsFromBuf(PF_DIR_ENT* p_ent, const pf_u8* buf);
void VFiPFENT_StoreEntryNumericFieldsToBuf(pf_u8* buf, const PF_DIR_ENT* p_ent);
pf_s32 VFiPFENT_LoadLFNEntryFieldsFromBuf(PF_DIR_ENT* p_ent, const pf_u8* buf);
void VFiPFENT_storeLFNEntryFieldsToBuf(pf_u8* buf, PF_DIR_ENT* p_ent, pf_u8 ord, pf_u8 sum, pf_u32 is_last);
pf_s32 VFiPFENT_findEntryPos(PF_FFD* p_ffd, PF_DIR_ENT* p_ent, pf_u32 index_search_from, PF_STR* p_pattern, pf_u8 attr_required, pf_u8 attr_unwanted,
                             pf_u32* p_lpos, pf_u32* p_ppos);
pf_s32 VFiPFENT_findEntry(PF_FFD* p_ffd, pf_u32 index_search_from, PF_STR* p_pattern);
pf_s32 VFiPFENT_allocateEntryPos(PF_DIR_ENT* p_ent, pf_u8 num_entries, PF_FFD* p_ffd, pf_u32* p_next_chain, PF_STR* p_filename, pf_u32* p_pos);
pf_s32 VFiPFENT_allocateEntry(PF_DIR_ENT* p_ent, PF_FFD* p_ffd, pf_u32* p_next_chain);
pf_s32 VFiPFENT_GetRootDir(PF_VOLUME* p_vol, PF_DIR_ENT* p_ent);
pf_s32 VFiPFENT_MakeRootDir(PF_VOLUME* p_vol);
pf_s32 VFiPFENT_updateEntry(PF_DIR_ENT* p_ent, pf_u32 flag);
pf_s32 VFiPFENT_AdjustSFN(PF_DIR_ENT* p_ent, pf_s8* p_short_name);
pf_s32 VFiPFENT_RemoveEntry(PF_DIR_ENT* p_ent, PF_ENT_ITER* p_iter);
pf_u8 VFiPFENT_getcurrentDateTimeForEnt(pf_u16* p_date, pf_u16* p_time);

#endif  // VF_PF_ENTRY_H
