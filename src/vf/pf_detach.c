#include <private/vf/pf_detach.h>

#include <private/vf/pf_api_util.h>
#include <private/vf/pf_volume.h>

pf_int32 VFipf2_detach(pf_ch8 drive) {
    pf_s32 err = VFiPFVOL_detach(drive);
    return VFiPFAPI_convertReturnValue(err);
}
