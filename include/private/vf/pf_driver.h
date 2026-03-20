#ifndef VF_PF_DRIVER_H
#define VF_PF_DRIVER_H

#include <private/vf/pf_types.h>

long VFiPFDRV_GetFSINFOInformation(struct PF_VOLUME* p_vol /* r31 */);
long VFiPFDRV_StoreFreeCountToFSINFO(struct PF_VOLUME* p_vol /* r31 */);
unsigned long VFiPFDRV_IsInserted(struct PF_VOLUME* p_vol /* r31 */);
unsigned long VFiPFDRV_IsDetected(struct PF_VOLUME* p_vol /* r31 */);
unsigned long VFiPFDRV_IsWProtected(struct PF_VOLUME* p_vol /* r31 */);
long VFiPFDRV_init(struct PF_VOLUME* p_vol /* r3 */);
long VFiPFDRV_finalize(struct PF_VOLUME* p_vol /* r3 */);
long VFiPFDRV_mount(struct PF_VOLUME* p_vol /* r31 */);
long VFiPFDRV_unmount(struct PF_VOLUME* p_vol /* r31 */, unsigned long mode /* r1+0x8 */);
long VFiPFDRV_format(struct PF_VOLUME* p_vol /* r31 */, const unsigned char* param /* r1+0x8 */);
long VFiPFDRV_lread(struct PF_VOLUME* p_vol /* r31 */, unsigned char* buf /* r1+0x8 */, unsigned long sector /* r1+0xC */,
                    unsigned long num_sectors /* r1+0x10 */, unsigned long* p_num_success /* r1+0x14 */);
long VFiPFDRV_lwrite(struct PF_VOLUME* p_vol /* r31 */, const unsigned char* buf /* r1+0x8 */, unsigned long sector /* r1+0xC */,
                     unsigned long num_sectors /* r1+0x10 */, unsigned long* p_num_success /* r1+0x14 */);

#endif  // VF_PF_DRIVER_H
