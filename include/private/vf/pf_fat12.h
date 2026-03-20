#ifndef VF_PF_FAT12_H
#define VF_PF_FAT12_H

#include <private/vf/pf_cache.h>
#include <private/vf/pf_types.h>

pf_s32 VFiPFFAT12_ReadFATEntry(PF_VOLUME* p_vol, pf_u16 cluster, pf_u32* p_value);
pf_s32 VFiPFFAT12_ReadFATEntryPage(PF_VOLUME* p_vol, pf_u16 cluster, pf_u32* p_value, PF_CACHE_PAGE** pp_page);
pf_s32 VFiPFFAT12_WriteFATEntry(PF_VOLUME* p_vol, pf_u16 cluster, pf_u16 value);
pf_s32 VFiPFFAT12_WriteFATEntryPage(PF_VOLUME* p_vol, pf_u16 cluster, pf_u16 value, PF_CACHE_PAGE** pp_page);

#endif  // VF_PF_FAT12_H
