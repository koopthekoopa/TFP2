#ifndef VF_PF_CLUSTER_H
#define VF_PF_CLUSTER_H

#include <private/vf/pf_types.h>
#include <private/vf/pf_volume.h>

void VFiPFCLUSTER_UpdateLastAccessCluster(PF_FILE* p_file, pf_u32 sector);
pf_s32 VFiPFCLUSTER_AppendCluster(PF_FILE* p_file, pf_u32 byte, pf_u32* p_success, pf_u32* sector);
pf_s32 VFiPFCLUSTER_GetAppendSize(PF_FILE* p_file, pf_u32* p_size);

#endif  // VF_PF_CLUSTER_H
