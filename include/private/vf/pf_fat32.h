#ifndef VF_PF_FAT32_H
#define VF_PF_FAT32_H

#include <private/vf/pf_cache.h>
#include <private/vf/pf_types.h>

pf_s32 VFiPFFAT32_ReadFATEntry(PF_VOLUME* p_vol, pf_u32 cluster, pf_u32* p_value);
pf_s32 VFiPFFAT32_ReadFATEntryPage(PF_VOLUME* p_vol, pf_u32 cluster, pf_u32* p_value, PF_CACHE_PAGE** pp_page);
pf_s32 VFiPFFAT32_WriteFATEntry(PF_VOLUME* p_vol, pf_u32 cluster, pf_u32 value);
pf_s32 VFiPFFAT32_WriteFATEntryPage(PF_VOLUME* p_vol, pf_u32 cluster, pf_u32 value, PF_CACHE_PAGE** pp_page);

#endif  // VF_PF_FAT32_H
