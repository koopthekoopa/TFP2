#ifndef PRFILE2_VFMOD_PF_DRIVER_H
#define PRFILE2_VFMOD_PF_DRIVER_H

#include <private/vf/PrFILE2/pf_types.h>

pf_s32 VFiPFDRV_GetFSINFOInformation(PF_VOLUME* p_vol);
pf_s32 VFiPFDRV_StoreFreeCountToFSINFO(PF_VOLUME* p_vol);
pf_u32 VFiPFDRV_IsInserted(PF_VOLUME* p_vol);
pf_u32 VFiPFDRV_IsDetected(PF_VOLUME* p_vol);
pf_u32 VFiPFDRV_IsWProtected(PF_VOLUME* p_vol);
pf_s32 VFiPFDRV_init(PF_VOLUME* p_vol);
pf_s32 VFiPFDRV_finalize(PF_VOLUME* p_vol);
pf_s32 VFiPFDRV_mount(PF_VOLUME* p_vol);
pf_s32 VFiPFDRV_unmount(PF_VOLUME* p_vol, pf_u32 mode);
pf_s32 VFiPFDRV_format(PF_VOLUME* p_vol, const pf_u8* param);
pf_s32 VFiPFDRV_lread(PF_VOLUME* p_vol, pf_u8* buf, pf_u32 sector, pf_u32 num_sectors, pf_u32* p_num_success);
pf_s32 VFiPFDRV_lwrite(PF_VOLUME* p_vol, const pf_u8* buf, pf_u32 sector, pf_u32 num_sectors, pf_u32* p_num_success);

#endif  // PRFILE2_VFMOD_PF_DRIVER_H
