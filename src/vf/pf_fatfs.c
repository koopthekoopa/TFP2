#include <private/vf/pf_fatfs.h>
#include <private/vf/pf_volume.h>

pf_s32 VFiPFFATFS_initializeFATFS(pf_u32 config, void* param) {
    return VFiPFVOL_InitModule(config, param);
}
