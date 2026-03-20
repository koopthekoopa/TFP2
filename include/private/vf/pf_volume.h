#ifndef VF_PF_VOLUME_H
#define VF_PF_VOLUME_H

// unsorted structs
#include <private/vf/pf_types.h>

struct PF_VOLUME {
    // total size: 0x1898
    struct PF_BPB bpb; // offset 0x0, size 0x38
    unsigned long num_free_clusters; // offset 0x38, size 0x4
    unsigned long last_free_cluster; // offset 0x3C, size 0x4
    struct PF_SFD sfds[5]; // offset 0x40, size 0xCD0
    struct PF_FILE ufds[5]; // offset 0xD10, size 0xF0
    struct PF_SDD sdds[3]; // offset 0xE00, size 0x780
    struct PF_DIR udds[3]; // offset 0x1580, size 0x60
    long num_opened_files; // offset 0x15E0, size 0x4
    long num_opened_directories; // offset 0x15E4, size 0x4
    struct PF_SECTOR_CACHE cache; // offset 0x15E8, size 0x24
    signed char label[12]; // offset 0x160C, size 0xC
    struct PF_CUR_DIR current_dir[1]; // offset 0x1618, size 0x248
    struct PF_DIR_TAIL tail_entry; // offset 0x1860, size 0xC
    long last_error; // offset 0x186C, size 0x4
    long last_driver_error; // offset 0x1870, size 0x4
    unsigned long file_config; // offset 0x1874, size 0x4
    unsigned short flags; // offset 0x1878, size 0x2
    signed char drv_char; // offset 0x187A, size 0x1
    unsigned short fsi_flag; // offset 0x187C, size 0x2
    struct PF_CLUSTER_LINK_VOL cluster_link; // offset 0x1880, size 0xC
    void * p_part; // offset 0x188C, size 0x4
    void (* p_callback)(); // offset 0x1890, size 0x4
    const unsigned char * format_param; // offset 0x1894, size 0x4
};
struct PF_CUR_VOLUME {
    // total size: 0xC
    unsigned long stat; // offset 0x0, size 0x4
    long context_id; // offset 0x4, size 0x4
    struct PF_VOLUME * p_vol; // offset 0x8, size 0x4
};
struct PF_VOLUME_SET {
    // total size: 0x27FB8
    struct PF_CUR_VOLUME current_vol[1]; // offset 0x0, size 0xC
    long num_attached_drives; // offset 0xC, size 0x4
    long num_mounted_volumes; // offset 0x10, size 0x4
    unsigned long config; // offset 0x14, size 0x4
    void * param; // offset 0x18, size 0x4
    long last_error; // offset 0x1C, size 0x4
    long last_driver_error; // offset 0x20, size 0x4
    struct PF_CHARCODE codeset; // offset 0x24, size 0x18
    unsigned long setting; // offset 0x3C, size 0x4
    struct PF_CONTEXT context[1]; // offset 0x40, size 0x8
    struct PF_VOLUME volumes[26]; // offset 0x48, size 0x27F70
};

extern struct PF_VOLUME_SET VFipf_vol_set;

long VFiPFVOL_InitModule(unsigned long config /* r29 */, void * param /* r1+0x8 */);
long VFiPFVOL_CheckForRead(struct PF_VOLUME * p_vol /* r30 */);
long VFiPFVOL_CheckForWrite(struct PF_VOLUME * p_vol /* r31 */);
long VFiPFVOL_GetCurrentDir(struct PF_VOLUME * p_vol /* r31 */, struct PF_DIR_ENT * p_current_dir /* r29 */);
void VFiPFVOL_SetCurrentVolume(struct PF_VOLUME * p_vol /* r30 */);
struct PF_VOLUME * VFiPFVOL_GetCurrentVolume();
struct PF_VOLUME * VFiPFVOL_GetVolumeFromDrvChar(signed char drv_char /* r1+0x8 */);
void VFiPFVOL_LoadVolumeLabelFromBuf(const unsigned char * buf /* r1+0x8 */, struct PF_VOLUME * p_vol /* r31 */);
long VFiPFVOL_getdev(signed char drv_char /* r1+0x8 */, struct PF_DEV_INF * dev_inf /* r30 */);
long VFiPFVOL_attach(struct PF_DRV_TBL * p_drv /* r31 */);
long VFiPFVOL_detach(signed char drv_char /* r1+0x8 */);
long VFiPFVOL_format(signed char drv_char /* r1+0x8 */, const unsigned char * param /* r1+0xC */);
long VFiPFVOL_unmount(signed char drv_char /* r1+0x8 */, unsigned long mode /* r28 */);

#endif // VF_PF_VOLUME_H
