#ifndef VF_PF_SECTOR_H
#define VF_PF_SECTOR_H

#include <private/vf/pf_types.h>
#include <private/vf/pf_str.h>

long VFiPFSEC_ReadFAT(struct PF_VOLUME * p_vol /* r31 */, unsigned char * p_buf /* r29 */, unsigned long sector /* r1+0x8 */, unsigned short offset /* r1+0xC */, unsigned short size /* r1+0xE */);
long VFiPFSEC_ReadData(struct PF_VOLUME * p_vol /* r31 */, unsigned char * p_buf /* r24 */, unsigned long sector /* r26 */, unsigned short offset /* r23 */, unsigned long size /* r28 */, unsigned long * p_success_size /* r30 */, unsigned long set_sig /* r22 */);
long VFiPFSEC_WriteFAT(struct PF_VOLUME * p_vol /* r30 */, const unsigned char * p_buf /* r29 */, unsigned long sector /* r1+0x8 */, unsigned short offset /* r1+0xC */, unsigned short size /* r1+0xE */);
long VFiPFSEC_WriteData(struct PF_VOLUME * p_vol /* r31 */, const unsigned char * p_buf /* r24 */, unsigned long sector /* r25 */, unsigned short offset /* r22 */, unsigned long size /* r26 */, unsigned long * p_success_size /* r29 */, unsigned long set_sig /* r23 */);

#endif // VF_PF_SECTOR_H
