#ifndef VF_PF_FAT_FILESYSTEM_H
#define VF_PF_FAT_FILESYSTEM_H

#include <private/vf/pf_types.h>

long VFiPFFATFS_initializeFATFS(unsigned long config /* r1+0x8 */, void * param /* r1+0xC */);

#endif // VF_PF_FAT_FILESYSTEM_H
