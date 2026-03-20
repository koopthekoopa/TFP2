#ifndef VF_PF_DIR_H
#define VF_PF_DIR_H

#include <private/vf/pf_str.h>
#include <private/vf/pf_types.h>

void VFiPFDIR_FinalizeAllDirs(struct PF_VOLUME* p_vol /* r30 */);
long VFiPFDIR_mkdir(struct PF_STR* p_path_str /* r29 */);

#endif  // VF_PF_DIR_H
