#ifndef VF_PF_TYPES_H
#define VF_PF_TYPES_H

// unsorted structs
#include <private/vf/pf_struct.h>
#include <private/vf/pdm_struct.h>

typedef signed char         pf_s8;
typedef signed short        pf_s16;
typedef signed long         pf_s32;
typedef signed long long    pf_s64;
typedef unsigned char       pf_u8;
typedef unsigned short      pf_u16;
typedef unsigned long       pf_u32;
typedef unsigned long long  pf_u64;

typedef volatile pf_u8      pf_vu8;
typedef volatile pf_u16     pf_vu16;
typedef volatile pf_u32     pf_vu32;
typedef volatile pf_u64     pf_vu64;
typedef volatile pf_s8      pf_vs8;
typedef volatile pf_s16     pf_vs16;
typedef volatile pf_s32     pf_vs32;
typedef volatile pf_s64     pf_vs64;

typedef float               pf_f32;
typedef double              pf_f64;
typedef volatile pf_f32     pf_vf32;
typedef volatile pf_f64     pf_vf64;

typedef int                 pf_bool;

#define PF_TRUE             1
#define PF_FALSE            0

#define PF_NULL             0

#endif // VF_PF_TYPES_H
