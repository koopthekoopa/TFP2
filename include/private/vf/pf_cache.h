#ifndef VF_PF_CACHE_H
#define VF_PF_CACHE_H

#include <private/vf/pf_types.h>

typedef struct PF_CACHE_PAGE PF_CACHE_PAGE;
struct PF_CACHE_PAGE {
    // total size: 0x28
    pf_u16 stat;            // offset 0x0, size 0x2
    pf_u16 option;          // offset 0x2, size 0x2
    pf_u8* buffer;          // offset 0x4, size 0x4
    pf_u8* p_buf;           // offset 0x8, size 0x4
    pf_u8* p_mod_sbuf;      // offset 0xC, size 0x4
    pf_u8* p_mod_ebuf;      // offset 0x10, size 0x4
    pf_u32 size;            // offset 0x14, size 0x4
    pf_u32 sector;          // offset 0x18, size 0x4
    void* signature;        // offset 0x1C, size 0x4
    PF_CACHE_PAGE* p_next;  // offset 0x20, size 0x4
    PF_CACHE_PAGE* p_prev;  // offset 0x24, size 0x4
};

typedef struct PF_SECTOR_CACHE {
    // total size: 0x24
    pf_u32 mode;                    // offset 0x0, size 0x4
    pf_u16 num_fat_pages;           // offset 0x4, size 0x2
    pf_u16 num_data_pages;          // offset 0x6, size 0x2
    PF_CACHE_PAGE* pages;           // offset 0x8, size 0x4
    PF_CACHE_PAGE* p_current_fat;   // offset 0xC, size 0x4
    PF_CACHE_PAGE* p_current_data;  // offset 0x10, size 0x4
    PF_CACHE_BUFFER* buffers;       // offset 0x14, size 0x4
    pf_u32 fat_buff_size;           // offset 0x18, size 0x4
    pf_u32 data_buff_size;          // offset 0x1C, size 0x4
    void* signature;                // offset 0x20, size 0x4
} PF_SECTOR_CACHE;

void VFiPFCACHE_SetCache(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_cache_page, PF_CACHE_BUFFER* p_cache_buf, pf_u16 num_fat_pages, pf_u16 num_data_pages);
void VFiPFCACHE_SetFATBufferSize(PF_VOLUME* p_vol, pf_u32 size);
void VFiPFCACHE_SetDataBufferSize(PF_VOLUME* p_vol, pf_u32 size);
pf_s32 VFiPFCACHE_InitCaches(PF_VOLUME* p_vol);
pf_s32 VFiPFCACHE_UpdateModifiedSector(PF_CACHE_PAGE* p_page);
pf_s32 VFiPFCACHE_AllocateFATPage(PF_VOLUME* p_vol, pf_u32 sector, PF_CACHE_PAGE** pp_page);
pf_s32 VFiPFCACHE_AllocateDataPage(PF_VOLUME* p_vol, pf_u32 sector, PF_CACHE_PAGE** pp_page);
void VFiPFCACHE_FreeFATPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page);
void VFiPFCACHE_FreeDataPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page);
pf_s32 VFiPFCACHE_ReadFATPage(PF_VOLUME* p_vol, pf_u32 sector);
pf_s32 VFiPFCACHE_ReadDataPage(PF_VOLUME* p_vol, pf_u32 sector, pf_u32 set_sig);
pf_s32 VFiPFCACHE_ReadDataPageAndFlushIfNeeded(PF_VOLUME* p_vol, pf_u32 sector, PF_CACHE_PAGE** pp_page, pf_u32 set_sig);
pf_s32 VFiPFCACHE_ReadDataNumSector(PF_VOLUME* p_vol, pf_u8* p_buf, pf_u32 sector, pf_u32 num_sector, pf_u32* p_num_success);
pf_s32 VFiPFCACHE_WriteFATPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page);
pf_s32 VFiPFCACHE_WriteDataPage(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page);
pf_s32 VFiPFCACHE_WriteFATSectorAndFreeIfNeeded(PF_VOLUME* p_vol, const pf_u8* p_buf, pf_u32 sector);
pf_s32 VFiPFCACHE_WriteDataNumSectorAndFreeIfNeeded(PF_VOLUME* p_vol, const pf_u8* p_buf, pf_u32 sector, pf_u32 num_sector, pf_u32* p_num_success);
PF_CACHE_PAGE* VFiPFCACHE_SearchDataCache(PF_VOLUME* p_vol, pf_u32 sector);
pf_s32 VFiPFCACHE_FlushFATCache(PF_VOLUME* p_vol);
pf_s32 VFiPFCACHE_FlushDataCacheSpecific(PF_VOLUME* p_vol, void* signature);
pf_s32 VFiPFCACHE_FlushAllCaches(PF_VOLUME* p_vol);
void VFiPFCACHE_FreeAllCaches(PF_VOLUME* p_vol);

#endif  // VF_PF_CACHE_H
