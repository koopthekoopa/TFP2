#include <private/vf/pf_fopen.h>

#include <private/vf/pf_api_util.h>
#include <private/vf/pf_volume.h>

PF_FILE* VFipf2_fopen(const pf_ch8* path, const pf_ch8* mode) {
    pf_s32 open_mode;
    PF_FILE* p_file;
    PF_STR path_str;
    pf_s32 err;

    open_mode = VFiPFAPI_ParseOpenModeString(mode);
    if (open_mode == 0) {
        VFipf_vol_set.last_error = 0xA;
        return PF_NULL;
    }
    err = VFiPFSTR_InitStr(&path_str, (pf_s8*)path, 1U);
    if (err == 0) {
        err = VFiPFFILE_fopen(&path_str, open_mode, &p_file);
    } else {
        VFipf_vol_set.last_error = err;
    }
    return VFiPFAPI_convertReturnValue2NULL(err, p_file);
}
