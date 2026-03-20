#ifndef VF_PF_FAT16_H
#define VF_PF_FAT16_H

#include <private/vf/pf_types.h>

long VFiPFFAT16_ReadFATEntry(struct PF_VOLUME * p_vol /* r31 */, unsigned long cluster /* r27 */, unsigned long * p_value /* r30 */);
long VFiPFFAT16_ReadFATEntryPage(struct PF_VOLUME * p_vol /* r31 */, unsigned long cluster /* r25 */, unsigned long * p_value /* r23 */, struct PF_CACHE_PAGE * * pp_page /* r30 */);
long VFiPFFAT16_WriteFATEntry(struct PF_VOLUME * p_vol /* r31 */, unsigned long cluster /* r30 */, unsigned long value /* r25 */);
long VFiPFFAT16_WriteFATEntryPage(struct PF_VOLUME * p_vol /* r31 */, unsigned long cluster /* r25 */, unsigned long value /* r22 */, struct PF_CACHE_PAGE * * pp_page /* r30 */);

#endif // VF_PF_FAT16_H
