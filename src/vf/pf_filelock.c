#include <private/vf/pf_file.h>
#include <private/vf/pf_filelock.h>

#include <private/vf/pf_system.h>

void VFiPF_InitLockFile() {
    VFipf_sys_set.flock_count = 0;
}

long VFiPF_UnLockFile(PF_FILE* p_file) {
    return -1;
}
