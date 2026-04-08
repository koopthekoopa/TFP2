#include <private/vf/pf_fclose.h>

#include <private/vf/pf_api_util.h>
#include <private/vf/pf_volume.h>

pf_int32 VFipf2_fclose(PF_FILE* p_file) {
    pf_s32 err = VFiPFFILE_fclose(p_file);
    return VFiPFAPI_convertReturnValue(err);
}
