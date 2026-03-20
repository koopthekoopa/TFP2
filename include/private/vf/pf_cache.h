#ifndef VF_PF_CACHE_H
#define VF_PF_CACHE_H

#include <private/vf/pf_types.h>

void VFiPFCACHE_SetCache(struct PF_VOLUME* p_vol /* r3 */, struct PF_CACHE_PAGE* p_cache_page /* r4 */, unsigned char (*p_cache_buf)[512] /* r5 */,
                         unsigned short num_fat_pages /* r6 */, unsigned short num_data_pages /* r7 */);
void VFiPFCACHE_SetFATBufferSize(struct PF_VOLUME* p_vol /* r3 */, unsigned long size /* r4 */);
void VFiPFCACHE_SetDataBufferSize(struct PF_VOLUME* p_vol /* r3 */, unsigned long size /* r4 */);
long VFiPFCACHE_InitCaches(struct PF_VOLUME* p_vol /* r31 */);
long VFiPFCACHE_UpdateModifiedSector(struct PF_CACHE_PAGE* p_page /* r3 */);
long VFiPFCACHE_AllocateFATPage(struct PF_VOLUME* p_vol /* r31 */, unsigned long sector /* r1+0x8 */, struct PF_CACHE_PAGE** pp_page /* r29 */);
long VFiPFCACHE_AllocateDataPage(struct PF_VOLUME* p_vol /* r31 */, unsigned long sector /* r1+0x8 */, struct PF_CACHE_PAGE** pp_page /* r29 */);
void VFiPFCACHE_FreeFATPage(struct PF_VOLUME* p_vol /* r30 */, struct PF_CACHE_PAGE* p_page /* r31 */);
void VFiPFCACHE_FreeDataPage(struct PF_VOLUME* p_vol /* r30 */, struct PF_CACHE_PAGE* p_page /* r31 */);
long VFiPFCACHE_ReadFATPage(struct PF_VOLUME* p_vol /* r30 */, unsigned long sector /* r1+0x8 */, struct PF_CACHE_PAGE** pp_page /* r1+0xC */);
long VFiPFCACHE_ReadDataPage(struct PF_VOLUME* p_vol /* r30 */, unsigned long sector /* r1+0x8 */, struct PF_CACHE_PAGE** pp_page /* r1+0xC */,
                             unsigned long set_sig /* r1+0x10 */);
long VFiPFCACHE_ReadDataPageAndFlushIfNeeded(struct PF_VOLUME* p_vol /* r30 */, unsigned long sector /* r1+0x8 */,
                                             struct PF_CACHE_PAGE** pp_page /* r1+0xC */, unsigned long set_sig /* r1+0x10 */);
long VFiPFCACHE_ReadDataNumSector(struct PF_VOLUME* p_vol /* r30 */, unsigned char* p_buf /* r1+0x8 */, unsigned long sector /* r29 */,
                                  unsigned long num_sector /* r1+0xC */, unsigned long* p_num_success /* r1+0x10 */);
long VFiPFCACHE_WriteFATPage(struct PF_VOLUME* p_vol /* r30 */, struct PF_CACHE_PAGE* p_page /* r1+0x8 */);
long VFiPFCACHE_WriteDataPage(struct PF_VOLUME* p_vol /* r30 */, struct PF_CACHE_PAGE* p_page /* r1+0x8 */, unsigned long set_sig /* r1+0xC */);
long VFiPFCACHE_WriteFATSectorAndFreeIfNeeded(struct PF_VOLUME* p_vol /* r30 */, const unsigned char* p_buf /* r1+0x8 */,
                                              unsigned long sector /* r29 */);
long VFiPFCACHE_WriteDataNumSectorAndFreeIfNeeded(struct PF_VOLUME* p_vol /* r30 */, const unsigned char* p_buf /* r1+0x8 */,
                                                  unsigned long sector /* r29 */, unsigned long num_sector /* r1+0xC */,
                                                  unsigned long* p_num_success /* r1+0x10 */);
struct PF_CACHE_PAGE* VFiPFCACHE_SearchDataCache(struct PF_VOLUME* p_vol /* r31 */, unsigned long sector /* r1+0x8 */);
long VFiPFCACHE_FlushFATCache(struct PF_VOLUME* p_vol /* r30 */);
long VFiPFCACHE_FlushDataCacheSpecific(struct PF_VOLUME* p_vol /* r29 */, void* signature /* r26 */);
long VFiPFCACHE_FlushAllCaches(struct PF_VOLUME* p_vol /* r30 */);
void VFiPFCACHE_FreeAllCaches(struct PF_VOLUME* p_vol /* r31 */);

#endif  // VF_PF_CACHE_H
