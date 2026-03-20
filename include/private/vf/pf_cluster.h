#ifndef VF_PF_CLUSTER_H
#define VF_PF_CLUSTER_H

#include <private/vf/pf_types.h>

void VFiPFCLUSTER_UpdateLastAccessCluster(struct PF_FILE* p_file /* r3 */, unsigned long sector /* r4 */);
long VFiPFCLUSTER_AppendCluster(struct PF_FILE* p_file /* r31 */, unsigned long byte /* r26 */, unsigned long* p_success /* r29 */,
                                unsigned long* sector /* r24 */);
long VFiPFCLUSTER_GetAppendSize(struct PF_FILE* p_file /* r31 */, unsigned long* p_size /* r26 */);

#endif  // VF_PF_CLUSTER_H
