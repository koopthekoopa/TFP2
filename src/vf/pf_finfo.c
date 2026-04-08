#include <private/vf/pf_finfo.h>

#include <private/vf/pf_api_util.h>
#include <private/vf/pf_volume.h>

pf_int32 VFipf2_finfo(PF_FILE* p_file, PF_INFO* p_info) {
    pf_s32 err = VFiPFFILE_finfo(p_file, p_info);
    return VFiPFAPI_convertReturnValue(err);
}
