#ifndef VF_PF_CODE_H
#define VF_PF_CODE_H

#include <private/vf/pf_types.h>

pf_s32  VFiPFCODE_Combine_Width(pf_s16 oem_width, pf_s16 uni_width);
void    VFiPFCODE_Divide_Width(pf_s32 width, pf_s16* oem_width, pf_s16* uni_width);

#endif // VF_PF_CODE_H
