#ifndef VF_PF_CP932_H
#define VF_PF_CP932_H

#include <private/vf/pf_types.h>

long VFiPFCODE_CP932_OEM2Unicode(const signed char* cp932_src /* r26 */, unsigned short* uc_dst /* r30 */);
long VFiPFCODE_CP932_Unicode2OEM(const unsigned short* uc_src /* r26 */, signed char* cp932_dst /* r30 */);
long VFiPFCODE_CP932_OEMCharWidth(const signed char* buf /* r1+0x8 */);
unsigned long VFiPFCODE_CP932_isOEMMBchar(signed char cp932 /* r3 */, unsigned long num /* r4 */);
long VFiPFCODE_CP932_UnicodeCharWidth(const unsigned short* buf /* r1+0x8 */);
unsigned long VFiPFCODE_CP932_isUnicodeMBchar(unsigned short uc_src /* r3 */, unsigned long num /* r4 */);

#endif  // VF_PF_CP932_H
