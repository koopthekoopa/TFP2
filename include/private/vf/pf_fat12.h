#ifndef VF_PF_FAT12_H
#define VF_PF_FAT12_H

#include <private/vf/pf_types.h>

long VFiPFFAT12_ReadFATEntry(struct PF_VOLUME * p_vol /* r31 */, unsigned short cluster /* r27 */, unsigned long * p_value /* r30 */);
long VFiPFFAT12_ReadFATEntryPage(struct PF_VOLUME * p_vol /* r31 */, unsigned short cluster /* r25 */, unsigned long * p_value /* r26 */, struct PF_CACHE_PAGE * * pp_page /* r30 */);
long VFiPFFAT12_WriteFATEntry(struct PF_VOLUME * p_vol /* r31 */, unsigned short cluster /* r28 */, unsigned short value /* r24 */);
long VFiPFFAT12_WriteFATEntryPage(struct PF_VOLUME * p_vol /* r31 */, unsigned short cluster /* r24 */, unsigned short value /* r23 */, struct PF_CACHE_PAGE * * pp_page /* r30 */);

#endif // VF_PF_FAT12_H
