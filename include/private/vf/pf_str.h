#ifndef VF_PF_STRING_H
#define VF_PF_STRING_H

#include <private/vf/pf_types.h>

struct PF_STR {
    // total size: 0x10
    const signed char * p_head; // offset 0x0, size 0x4
    const signed char * p_tail; // offset 0x4, size 0x4
    const signed char * p_local; // offset 0x8, size 0x4
    unsigned long code_mode; // offset 0xC, size 0x4
};

void    VFiPFSTR_SetCodeMode(struct PF_STR* p_str, pf_u32 code_mode);
pf_u32  VFiPFSTR_GetCodeMode(struct PF_STR* p_str);

void    VFiPFSTR_SetLocalStr(struct PF_STR* p_str, pf_s8* p_local);

pf_s8*  VFiPFSTR_GetStrPos(struct PF_STR* p_str, pf_u32 target);
void    VFiPFSTR_MoveStrPos(struct PF_STR* p_str, pf_s16 num_char);

pf_s32  VFiPFSTR_InitStr(struct PF_STR* p_str, const pf_s8* s, pf_u32 code_mode);

pf_u16  VFiPFSTR_StrLen(struct PF_STR* p_str);
pf_u16  VFiPFSTR_StrNumChar(struct PF_STR* p_str, pf_u32 target);

pf_s32  VFiPFSTR_StrCmp(const struct PF_STR* p_str, const pf_s8* s);
pf_s32  VFiPFSTR_StrNCmp(struct PF_STR* p_str, const pf_s8* s, pf_u32 target, pf_s16 offset, pf_u16 num);

void    VFiPFSTR_ToUpperNStr(struct PF_STR* p_str, pf_u16 num, pf_s8* dest);

#endif // VF_PF_STRING_H