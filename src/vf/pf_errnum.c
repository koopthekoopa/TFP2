#include <private/vf/pf_errnum.h>

#include <private/vf/pf_api_util.h>
#include <private/vf/pf_volume.h>

pf_int32 VFipf2_errnum() {
    pf_s32 err = VFiPFVOL_errnum();
    return VFiPFAPI_convertError(err);
}
