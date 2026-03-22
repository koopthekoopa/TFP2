#ifndef VF_PF_FAT_H
#define VF_PF_FAT_H

#include <private/vf/pf_cache.h>
#include <private/vf/pf_str.h>
#include <private/vf/pf_types.h>

typedef struct PF_LAST_CLUSTER {
    // total size: 0x8
    pf_u32 num_last_cluster;  // offset 0x0, size 0x4
    pf_u32 max_chain_index;   // offset 0x4, size 0x4
} PF_LAST_CLUSTER;

typedef struct PF_FAT_LAST_ACCESS {
    // total size: 0x8
    pf_u32 chain_index;  // offset 0x0, size 0x4
    pf_u32 cluster;      // offset 0x4, size 0x4
} PF_FAT_LAST_ACCESS;

typedef struct PF_CLUSTER_LINK {
    // total size: 0x14
    pf_u32* buffer;          // offset 0x0, size 0x4
    pf_u16 interval;         // offset 0x4, size 0x2
    pf_u16 interval_offset;  // offset 0x6, size 0x2
    pf_u32 position;         // offset 0x8, size 0x4
    pf_u32 max_count;        // offset 0xC, size 0x4
    pf_u32 save_index;       // offset 0x10, size 0x4
} PF_CLUSTER_LINK;

typedef struct PF_FAT_HINT {
    // total size: 0xC
    pf_u32 chain_index;   // offset 0x0, size 0x4
    pf_u32 cluster;       // offset 0x4, size 0x4
    pf_u32 file_version;  // offset 0x8, size 0x4
} PF_FAT_HINT;

typedef struct PF_FFD {
    // total size: 0x38
    pf_u32 file_version;                            // offset 0x0, size 0x4
    pf_u32 start_cluster;                           // offset 0x4, size 0x4
    pf_u32* p_start_cluster;                        // offset 0x8, size 0x4
    struct PF_LAST_CLUSTER last_cluster;            // offset 0xC, size 0x8
    struct PF_FAT_LAST_ACCESS last_access_cluster;  // offset 0x14, size 0x8
    struct PF_CLUSTER_LINK cluster_link;            // offset 0x1C, size 0x14
    struct PF_FAT_HINT* p_hint;                     // offset 0x30, size 0x4
    PF_VOLUME* p_vol;                               // offset 0x34, size 0x4
} PF_FFD;

typedef struct PF_CLUSTER_LINK_VOL {
    // total size: 0xC
    pf_u16 flag;      // offset 0x0, size 0x2
    pf_u16 interval;  // offset 0x2, size 0x2
    pf_u32* buffer;   // offset 0x4, size 0x4
    pf_u32 link_max;  // offset 0x8, size 0x4
} PF_CLUSTER_LINK_VOL;

pf_s32 VFiPFFAT_UpdateFATEntry(PF_VOLUME* p_vol, PF_CACHE_PAGE* p_page);
pf_s32 VFiPFFAT_UpdateAlternateFATEntry(PF_VOLUME* p_vol, pf_u8* p_buf, pf_u32 sector, pf_u32 size);
pf_s32 VFiPFFAT_GetSectorSpecified(PF_FFD* p_ffd, pf_u32 file_sector_index, pf_u32 may_allocate, pf_u32* p_sector);
pf_s32 VFiPFFAT_GetSectorAllocated(PF_FFD* p_ffd, pf_u32 file_sector_index, pf_u32 size, pf_u32* p_sector, pf_u32* p_num_sector);
pf_s32 VFiPFFAT_GetContinuousSector(PF_FFD* p_ffd, pf_u32 file_sector_index, pf_u32 size, pf_u32* p_sector, pf_u32* p_num_sector);
pf_s32 VFiPFFAT_CountAllocatedClusters(PF_FFD* p_ffd, pf_u32 size, pf_u32* p_num_alloc_clusters);
pf_s32 VFiPFFAT_CountFreeClusters(PF_VOLUME* p_vol, pf_u32* p_num_free_clusters);
pf_s32 VFiPFFAT_FreeChain(PF_FFD* p_ffd, pf_u32 start_cluster, pf_u32 chain_index, pf_u32 size);
pf_s32 VFiPFFAT_GetBeforeChain(PF_VOLUME* p_vol, pf_u32 start_cluster, pf_u32 lActive, pf_u32* p_cluster);
pf_s32 VFiPFFAT_InitFATRegion(PF_VOLUME* p_vol);
pf_s32 VFiPFFAT_MakeRootDir(PF_VOLUME* p_vol);
pf_s32 VFiPFFAT_RefreshFSINFO(PF_VOLUME* p_vol);
void VFiPFFAT_InitHint(PF_FAT_HINT* p_hint);
pf_s32 VFiPFFAT_TraceClustersChain(PF_FFD* p_ffd, pf_u32 start_clst, pf_u32 size, pf_u32* p_target_clst, pf_u32* p_next_clst);
pf_s32 VFiPFFAT_ReadValueToSpecifiedCluster(PF_VOLUME* p_vol, pf_u32 cluster, pf_u32* value);
pf_s32 VFiPFFAT_ResetFFD(PF_FFD* p_ffd, pf_u32* p_start_cluster);
pf_s32 VFiPFFAT_InitFFD(PF_FFD* p_ffd, PF_FAT_HINT* p_hint, pf_u32* p_start_cluster);
pf_s32 VFiPFFAT_FinalizeFFD(PF_FFD* p_ffd);
pf_u32 VFiPFFAT_GetValueOfEOC2(PF_VOLUME* p_vol);

#endif  // VF_PF_FAT_H
