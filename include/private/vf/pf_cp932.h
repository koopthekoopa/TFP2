#ifndef VF_PF_CP932_H
#define VF_PF_CP932_H

#include <private/vf/pf_types.h>

pf_s32 VFiPFCODE_CP932_OEM2Unicode(const pf_s8* cp932_src, pf_u16* uc_dst);
pf_s32 VFiPFCODE_CP932_Unicode2OEM(const pf_u16* uc_src, pf_s8* cp932_dst);
pf_s32 VFiPFCODE_CP932_OEMCharWidth(const pf_s8* buf);
pf_u32 VFiPFCODE_CP932_isOEMMBchar(pf_s8 cp932, pf_u32 num);
pf_s32 VFiPFCODE_CP932_UnicodeCharWidth(const pf_u16* buf);
pf_u32 VFiPFCODE_CP932_isUnicodeMBchar(pf_u16 uc_src, pf_u32 num);

#endif  // VF_PF_CP932_H
