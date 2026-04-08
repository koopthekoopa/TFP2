#ifndef VF_PF_SYSTEM_H
#define VF_PF_SYSTEM_H

#include <private/vf/pf_types.h>

typedef struct PF_SYSTEM_SET {
    pf_u32 flock_count;  // 0x00
} PF_SYSTEM_SET;

extern PF_SYSTEM_SET VFipf_sys_set;

void VFiPFSYS_initializeSYS();
pf_s32 VFiPFSYS_GetCurrentContextID(pf_s32* context_id);
void VFiPFSYS_TimeStamp(struct PF_SYS_DATE* sdate /* r30 */, struct PF_SYS_TIME* stime /* r31 */);

#endif  // VF_PF_SYSTEM_H
