#ifndef VF_PF_DIR_H
#define VF_PF_DIR_H

#include <private/vf/pf_str.h>
#include <private/vf/pf_types.h>

void VFiPFDIR_FinalizeAllDirs(PF_VOLUME* p_vol);
pf_s32 VFiPFDIR_mkdir(PF_STR* p_path_str);

#endif  // VF_PF_DIR_H
