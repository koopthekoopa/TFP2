#include <private/vf/pf_format.h>

#include <private/vf/pf_api_util.h>
#include <private/vf/pf_volume.h>

pf_int32 VFipf2_format(pf_ch8 drive, const pf_ch8* param) {
    pf_s32 err = VFiPFVOL_format(drive, (pf_u8*)param);
    return VFiPFAPI_convertReturnValue(err);
}
