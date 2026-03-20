#ifndef VF_PF_SECTOR_H
#define VF_PF_SECTOR_H

#include <private/vf/pf_str.h>
#include <private/vf/pf_types.h>

pf_s32 VFiPFSEC_ReadFAT(PF_VOLUME* p_vol, pf_u8* p_buf, pf_u32 sector, pf_u16 offset);
pf_s32 VFiPFSEC_ReadData(PF_VOLUME* p_vol, pf_u8* p_buf, pf_u32 sector, pf_u16 offset, pf_u32 size, pf_u32* p_success_size, pf_u32 set_sig);
pf_s32 VFiPFSEC_WriteFAT(PF_VOLUME* p_vol, const pf_u8* p_buf, pf_u32 sector, pf_u16 offset);
pf_s32 VFiPFSEC_WriteData(PF_VOLUME* p_vol, const pf_u8* p_buf, pf_u32 sector, pf_u16 offset, pf_u32 size, pf_u32* p_success_size, pf_u32 set_sig);

#endif  // VF_PF_SECTOR_H
