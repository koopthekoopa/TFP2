#ifndef VF_PF_PATH_H
#define VF_PF_PATH_H

#include <private/vf/pf_str.h>
#include <private/vf/pf_types.h>

pf_s32 VFiPFPATH_cmpNameUni(const pf_u16* p_name);
pf_s32 VFiPFPATH_cmpName(const pf_s8* sShort);
pf_s32 VFiPFPATH_cmpTailSFN(const pf_s8* sfn_name);
void VFiPFPATH_InitTokenOfPath(PF_STR* p_str, pf_s8* path, pf_u32 code_mode);
pf_s32 VFiPFPATH_GetNextTokenOfPath(PF_STR* p_str, pf_u32 wildcard);
pf_s32 VFiPFPATH_SplitPath(PF_STR* p_path, PF_STR* p_dir_path, PF_STR* p_filename);
PF_VOLUME* VFiPFPATH_GetVolumeFromPath(PF_STR* p_path);
pf_u32 VFiPFPATH_MatchFileNameWithPattern(const pf_s8* file_name, PF_STR* p_pattern, pf_u32 is_long_name);
pf_s32 VFiPFPATH_putShortName(pf_u8* pDirEntry, const pf_s8* short_name, pf_u8 attr);
pf_s32 VFiPFPATH_getShortName(pf_s8* short_name, const pf_u8* pDirEntry, pf_u8 attr);
void VFiPFPATH_getLongNameformShortName(pf_s8* short_name, pf_s8* long_name, pf_u8 flag);
pf_u32 VFiPFPATH_GetLengthFromShortname(const pf_s8* sSrc);
pf_u32 VFiPFPATH_GetLengthFromUnicode(const pf_u16* sSrc);
pf_s32 VFiPFPATH_transformFromUnicodeToNormal(pf_s8* sDest, const pf_u16* sSrc);
pf_s32 VFiPFPATH_transformInUnicode(pf_u16* sDestStr, const pf_s8* sSrcStr);
pf_u32 VFiPFPATH_parseShortName(pf_s8* pDest, PF_STR* p_pattern);
pf_s32 VFiPFPATH_parseShortNameNumeric(pf_s8* p_char, pf_u32 count);
void VFiPFPATH_SetSearchPattern(pf_s8* p_buf_local, pf_u16* p_buf_unicode, PF_STR* p_pattern);
pf_u32 VFiPFPATH_CheckExtShortNameSignature(PF_STR* p_str);
pf_u32 VFiPFPATH_CheckExtShortName(PF_STR* p_str, pf_u32 target, pf_u32 wildcard);
pf_u32 VFiPFPATH_GetExtShortNameIndex(PF_STR* p_str, pf_u32* p_index);
pf_s32 VFiPFPATH_AdjustExtShortName(pf_s8* pName, pf_u32 position);

#endif  // VF_PF_PATH_H
