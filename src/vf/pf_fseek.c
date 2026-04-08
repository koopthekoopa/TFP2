#include <private/vf/pf_fseek.h>

#include <private/vf/pf_api_util.h>
#include <private/vf/pf_volume.h>

pf_int32 VFipf2_fseek(PF_FILE* pFile, pf_s32 lOffset, pf_int32 nOrigin) {
    pf_s32 err = VFiPFFILE_fseek(pFile, lOffset, nOrigin);
    return VFiPFAPI_convertReturnValue(err);
}
