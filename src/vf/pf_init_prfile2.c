#include <private/vf/pf_init_prfile2.h>

#include <private/vf/pf_api_util.h>
#include <private/vf/pf_fatfs.h>
#include <private/vf/pf_system.h>

pf_int32 VFipf2_init_prfile2(pf_s32 config, void* param) {
    pf_s32 err = VFiPFFATFS_initializeFATFS(config, param);
    if (err == 0) {
        VFiPFSYS_initializeSYS();
    }
    return VFiPFAPI_convertReturnValue(err);
}
