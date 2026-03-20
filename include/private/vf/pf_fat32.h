#ifndef VF_PF_FAT32_H
#define VF_PF_FAT32_H

#include <private/vf/pf_types.h>

long VFiPFFAT32_ReadFATEntry(struct PF_VOLUME * p_vol /* r31 */, unsigned long cluster /* r26 */, unsigned long * p_value /* r30 */);
long VFiPFFAT32_ReadFATEntryPage(struct PF_VOLUME * p_vol /* r31 */, unsigned long cluster /* r25 */, unsigned long * p_value /* r23 */, struct PF_CACHE_PAGE * * pp_page /* r30 */);
long VFiPFFAT32_WriteFATEntry(struct PF_VOLUME * p_vol /* r31 */, unsigned long cluster /* r28 */, unsigned long value /* r1+0x8 */);
long VFiPFFAT32_WriteFATEntryPage(struct PF_VOLUME * p_vol /* r31 */, unsigned long cluster /* r24 */, unsigned long value /* r1+0x8 */, struct PF_CACHE_PAGE * * pp_page /* r30 */);

#endif // VF_PF_FAT32_H
