#ifndef VF_PF_DIR_H
#define VF_PF_DIR_H

#include <private/vf/pf_file.h>
#include <private/vf/pf_str.h>
#include <private/vf/pf_types.h>

typedef struct PF_DTA {
    PF_FILE* p_file;              // offset 0x0, size 0x4
    PF_DIR* p_dir;                // offset 0x4, size 0x4
    PF_VOLUME* p_vol;             // offset 0x8, size 0x4
    pf_u32 parent_start_cluster;  // offset 0xC, size 0x4
    pf_u32 parent_pos;            // offset 0x10, size 0x4
    pf_u32 status;                // offset 0x14, size 0x4
    pf_u8 num_entry_LFNs;         // offset 0x18, size 0x1
    pf_u8 ordinal;                // offset 0x19, size 0x1
    pf_u8 check_sum;              // offset 0x1A, size 0x1
    pf_u8 attr;                   // offset 0x1B, size 0x1
    pf_s8 reg_exp[520];           // offset 0x1C, size 0x208
    pf_u16 Time;                  // offset 0x224, size 0x2
    pf_u16 Date;                  // offset 0x226, size 0x2
    pf_u32 FileSize;              // offset 0x228, size 0x4
    pf_u8 Attribute;              // offset 0x22C, size 0x1
    pf_s8 FileName[13];           // offset 0x22D, size 0xD
    pf_s8 LongName[520];          // offset 0x23A, size 0x208
} PF_DTA;

typedef struct PF_DTAW {
    PF_FILE* p_file;              // offset 0x0, size 0x4
    PF_DIR* p_dir;                // offset 0x4, size 0x4
    PF_VOLUME* p_vol;             // offset 0x8, size 0x4
    pf_u32 parent_start_cluster;  // offset 0xC, size 0x4
    pf_u32 parent_pos;            // offset 0x10, size 0x4
    pf_u32 status;                // offset 0x14, size 0x4
    pf_u8 num_entry_LFNs;         // offset 0x18, size 0x1
    pf_u8 ordinal;                // offset 0x19, size 0x1
    pf_u8 check_sum;              // offset 0x1A, size 0x1
    pf_u8 attr;                   // offset 0x1B, size 0x1
    pf_s8 reg_exp[520];           // offset 0x1C, size 0x208
    pf_u16 Time;                  // offset 0x224, size 0x2
    pf_u16 Date;                  // offset 0x226, size 0x2
    pf_u32 FileSize;              // offset 0x228, size 0x4
    pf_u8 Attribute;              // offset 0x22C, size 0x1
    pf_s8 FileName[13];           // offset 0x22D, size 0xD
    pf_s8 LongName[522];          // offset 0x23A, size 0x208
    pf_u16 reg_expW[260];         // offset 0x444, size 0x208
    pf_u16 FileNameW[13];         // offset 0x64C, size 0x1A
    pf_u16 LongNameW[256];        // offset 0x666, size 0x200
} PF_DTAW;

void VFiPFDIR_FinalizeAllDirs(PF_VOLUME* p_vol);
pf_s32 VFiPFDIR_mkdir(PF_STR* p_path_str);

#endif  // VF_PF_DIR_H
