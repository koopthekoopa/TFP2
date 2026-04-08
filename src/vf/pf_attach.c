#include <private/vf/pf_attach.h>

#include <private/vf/pf_api_util.h>
#include <private/vf/pf_volume.h>

pf_int32 VFipf2_attach(PF_DRV_TBL** drv_tbl) {
    pf_s32 err;
    if (drv_tbl == 0 || !*drv_tbl) {
        err = 0xA;
        VFipf_vol_set.last_error = 0xA;
    } else {
        while (*drv_tbl) {
            err = VFiPFVOL_attach(*drv_tbl);
            if (err != 0) {
                return VFiPFAPI_convertReturnValue(err);
            }
            drv_tbl++;
        }
    }
    return VFiPFAPI_convertReturnValue(err);
}
