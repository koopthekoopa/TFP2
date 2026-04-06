#ifndef VF_PF_FILE_LOCK_H
#define VF_PF_FILE_LOCK_H

#include <private/vf/pf_file.h>
#include <private/vf/pf_types.h>

void VFiPF_InitLockFile();
long VFiPF_UnLockFile(PF_FILE* p_file);

#endif  // VF_PF_FILE_LOCK_H
