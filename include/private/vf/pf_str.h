#ifndef VF_PF_STRING_H
#define VF_PF_STRING_H

#include <private/vf/pf_types.h>

typedef struct PF_STR {
    // total size: 0x10
    const pf_s8* p_head;   // offset 0x0, size 0x4
    const pf_s8* p_tail;   // offset 0x4, size 0x4
    const pf_s8* p_local;  // offset 0x8, size 0x4
    pf_u32 code_mode;      // offset 0xC, size 0x4
} PF_STR;

void VFiPFSTR_SetCodeMode(PF_STR* p_str, pf_u32 code_mode);
pf_u32 VFiPFSTR_GetCodeMode(PF_STR* p_str);

void VFiPFSTR_SetLocalStr(PF_STR* p_str, pf_s8* p_local);

pf_s8* VFiPFSTR_GetStrPos(PF_STR* p_str, pf_u32 target);
void VFiPFSTR_MoveStrPos(PF_STR* p_str, pf_s16 num_char);

pf_s32 VFiPFSTR_InitStr(PF_STR* p_str, const pf_s8* s, pf_u32 code_mode);

pf_u16 VFiPFSTR_StrLen(PF_STR* p_str);
pf_u16 VFiPFSTR_StrNumChar(PF_STR* p_str, pf_u32 target);

pf_s32 VFiPFSTR_StrCmp(const PF_STR* p_str, const pf_s8* s);
pf_s32 VFiPFSTR_StrNCmp(PF_STR* p_str, const pf_s8* s, pf_u32 target, pf_s16 offset, pf_u16 num);

void VFiPFSTR_ToUpperNStr(PF_STR* p_str, pf_u16 num, pf_s8* dest);

#endif  // VF_PF_STRING_H
