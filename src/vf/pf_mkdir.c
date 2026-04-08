#include <private/vf/pf_mkdir.h>

#include <private/vf/pf_api_util.h>
#include <private/vf/pf_dir.h>

#include <private/vf/pf_str.h>

pf_int32 VFipf2_mkdir(const pf_ch8* sPath) {
    pf_s32 err;
    PF_STR path_str;

    err = VFiPFSTR_InitStr(&path_str, (pf_s8*)sPath, 1U);
    if (err == 0) {
        err = VFiPFDIR_mkdir(&path_str);
    } else {
        VFipf_vol_set.last_error = err;
    }
    return VFiPFAPI_convertReturnValue(err);
}
