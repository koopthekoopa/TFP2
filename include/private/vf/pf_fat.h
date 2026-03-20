#ifndef VF_PF_FAT_H
#define VF_PF_FAT_H

#include <private/vf/pf_types.h>
#include <private/vf/pf_str.h>

long VFiPFFAT_UpdateFATEntry(struct PF_VOLUME * p_vol /* r1+0x8 */, struct PF_CACHE_PAGE * p_page /* r30 */);
long VFiPFFAT_UpdateAlternateFATEntry(struct PF_VOLUME * p_vol /* r31 */, unsigned char * p_buf /* r1+0x8 */, unsigned long sector /* r30 */, unsigned long size /* r23 */);
long VFiPFFAT_GetSectorSpecified(struct PF_FFD * p_ffd /* r31 */, unsigned long file_sector_index /* r28 */, unsigned long may_allocate /* r1+0x8 */, unsigned long * p_sector /* r1+0xC */);
long VFiPFFAT_GetSectorAllocated(struct PF_FFD * p_ffd /* r31 */, unsigned long file_sector_index /* r29 */, unsigned long size /* r1+0x8 */, unsigned long * p_sector /* r1+0xC */, unsigned long * p_num_sector /* r1+0x10 */);
long VFiPFFAT_GetContinuousSector(struct PF_FFD * p_ffd /* r31 */, unsigned long file_sector_index /* r24 */, unsigned long size /* r23 */, unsigned long * p_sector /* r29 */, unsigned long * p_num_sector /* r27 */);
long VFiPFFAT_CountAllocatedClusters(struct PF_FFD * p_ffd /* r31 */, unsigned long size /* r29 */, unsigned long * p_num_alloc_clusters /* r30 */);
long VFiPFFAT_CountFreeClusters(struct PF_VOLUME * p_vol /* r31 */, unsigned long * p_num_free_clusters /* r29 */);
long VFiPFFAT_FreeChain(struct PF_FFD * p_ffd /* r25 */, unsigned long start_cluster /* r29 */, unsigned long chain_index /* r26 */, unsigned long size /* r27 */);
long VFiPFFAT_GetBeforeChain(struct PF_VOLUME * p_vol /* r29 */, unsigned long start_cluster /* r31 */, unsigned long lActive /* r26 */, unsigned long * p_cluster /* r30 */);
long VFiPFFAT_InitFATRegion(struct PF_VOLUME * p_vol /* r31 */);
long VFiPFFAT_MakeRootDir(struct PF_VOLUME * p_vol /* r31 */);
long VFiPFFAT_RefreshFSINFO(struct PF_VOLUME * p_vol /* r31 */);
void VFiPFFAT_InitHint(struct PF_FAT_HINT * p_hint /* r3 */);
long VFiPFFAT_TraceClustersChain(struct PF_FFD * p_ffd /* r31 */, unsigned long start_clst /* r28 */, unsigned long size /* r22 */, unsigned long * p_target_clst /* r25 */, unsigned long * p_next_clst /* r26 */);
long VFiPFFAT_ReadValueToSpecifiedCluster(struct PF_VOLUME * p_vol /* r1+0x8 */, unsigned long cluster /* r1+0xC */, unsigned long * value /* r1+0x10 */);
long VFiPFFAT_ResetFFD(struct PF_FFD * p_ffd /* r3 */, unsigned long * p_start_cluster /* r4 */);
long VFiPFFAT_InitFFD(struct PF_FFD * p_ffd /* r31 */, struct PF_FAT_HINT * p_hint /* r1+0x8 */, struct PF_VOLUME * p_vol /* r1+0xC */, unsigned long * p_start_cluster /* r30 */);
long VFiPFFAT_FinalizeFFD(struct PF_FFD * p_ffd /* r3 */);
unsigned long VFiPFFAT_GetValueOfEOC2(struct PF_VOLUME * p_vol /* r3 */);

#endif // VF_PF_FAT_H
