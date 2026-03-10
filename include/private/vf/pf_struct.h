#ifndef VF_PF_UNSORTED_STRUCTS_H
#define VF_PF_UNSORTED_STRUCTS_H

// unsorted structs
#include <private/vf/pf_types.h>

typedef enum /* @enum$182pf_str_c */ {
    FAT_12 = 0,
    FAT_16 = 1,
    FAT_32 = 2,
    FAT_ERR = -1,
} PF_FAT_TYPE;
struct PF_BPB {
    // total size: 0x38
    unsigned short bytes_per_sector; // offset 0x0, size 0x2
    unsigned short num_reserved_sectors; // offset 0x2, size 0x2
    unsigned short num_root_dir_entries; // offset 0x4, size 0x2
    unsigned char sectors_per_cluster; // offset 0x6, size 0x1
    unsigned char num_FATs; // offset 0x7, size 0x1
    unsigned long total_sectors; // offset 0x8, size 0x4
    unsigned long sectors_per_FAT; // offset 0xC, size 0x4
    unsigned long root_dir_cluster; // offset 0x10, size 0x4
    unsigned short fs_info_sector; // offset 0x14, size 0x2
    unsigned short backup_boot_sector; // offset 0x16, size 0x2
    unsigned short ext_flags; // offset 0x18, size 0x2
    unsigned char media; // offset 0x1A, size 0x1
    PF_FAT_TYPE fat_type; // offset 0x1C, size 0x4
    unsigned char log2_bytes_per_sector; // offset 0x20, size 0x1
    unsigned char log2_sectors_per_cluster; // offset 0x21, size 0x1
    unsigned char num_active_FATs; // offset 0x22, size 0x1
    unsigned short num_root_dir_sectors; // offset 0x24, size 0x2
    unsigned long active_FAT_sector; // offset 0x28, size 0x4
    unsigned long first_root_dir_sector; // offset 0x2C, size 0x4
    unsigned long first_data_sector; // offset 0x30, size 0x4
    unsigned long num_clusters; // offset 0x34, size 0x4
};
struct PF_LAST_CLUSTER {
    // total size: 0x8
    unsigned long num_last_cluster; // offset 0x0, size 0x4
    unsigned long max_chain_index; // offset 0x4, size 0x4
};
struct PF_FAT_LAST_ACCESS {
    // total size: 0x8
    unsigned long chain_index; // offset 0x0, size 0x4
    unsigned long cluster; // offset 0x4, size 0x4
};
struct PF_CLUSTER_LINK {
    // total size: 0x14
    unsigned long * buffer; // offset 0x0, size 0x4
    unsigned short interval; // offset 0x4, size 0x2
    unsigned short interval_offset; // offset 0x6, size 0x2
    unsigned long position; // offset 0x8, size 0x4
    unsigned long max_count; // offset 0xC, size 0x4
    unsigned long save_index; // offset 0x10, size 0x4
};
struct PF_FAT_HINT {
    // total size: 0xC
    unsigned long chain_index; // offset 0x0, size 0x4
    unsigned long cluster; // offset 0x4, size 0x4
    unsigned long file_version; // offset 0x8, size 0x4
};
struct PF_FFD {
    // total size: 0x38
    unsigned long file_version; // offset 0x0, size 0x4
    unsigned long start_cluster; // offset 0x4, size 0x4
    unsigned long * p_start_cluster; // offset 0x8, size 0x4
    struct PF_LAST_CLUSTER last_cluster; // offset 0xC, size 0x8
    struct PF_FAT_LAST_ACCESS last_access_cluster; // offset 0x14, size 0x8
    struct PF_CLUSTER_LINK cluster_link; // offset 0x1C, size 0x14
    struct PF_FAT_HINT * p_hint; // offset 0x30, size 0x4
    struct PF_VOLUME * p_vol; // offset 0x34, size 0x4
};
struct PF_DIR_ENT {
    // total size: 0x240
    unsigned short long_name[261]; // offset 0x0, size 0x20A
    unsigned char num_entry_LFNs; // offset 0x20A, size 0x1
    unsigned char ordinal; // offset 0x20B, size 0x1
    unsigned char check_sum; // offset 0x20C, size 0x1
    unsigned char align_pad[1]; // offset 0x20D, size 0x1
    signed char short_name[13]; // offset 0x20E, size 0xD
    unsigned char small_letter_flag; // offset 0x21B, size 0x1
    unsigned char attr; // offset 0x21C, size 0x1
    unsigned char create_time_ms; // offset 0x21D, size 0x1
    unsigned short create_time; // offset 0x21E, size 0x2
    unsigned short create_date; // offset 0x220, size 0x2
    unsigned short access_date; // offset 0x222, size 0x2
    unsigned short modify_time; // offset 0x224, size 0x2
    unsigned short modify_date; // offset 0x226, size 0x2
    unsigned long file_size; // offset 0x228, size 0x4
    struct PF_VOLUME * p_vol; // offset 0x22C, size 0x4
    unsigned long path_len; // offset 0x230, size 0x4
    unsigned long start_cluster; // offset 0x234, size 0x4
    unsigned long entry_sector; // offset 0x238, size 0x4
    unsigned short entry_offset; // offset 0x23C, size 0x2
};
struct PF_CURSOR {
    // total size: 0x10
    unsigned long position; // offset 0x0, size 0x4
    unsigned long sector; // offset 0x4, size 0x4
    unsigned long file_sector_index; // offset 0x8, size 0x4
    unsigned short offset_in_sector; // offset 0xC, size 0x2
};
struct PF_FILE {
    // total size: 0x30
    unsigned long stat; // offset 0x0, size 0x4
    long open_mode; // offset 0x4, size 0x4
    struct PF_SFD * p_sfd; // offset 0x8, size 0x4
    struct PF_FAT_HINT hint; // offset 0xC, size 0xC
    long last_error; // offset 0x18, size 0x4
    struct PF_CURSOR cursor; // offset 0x1C, size 0x10
    unsigned short lock_count; // offset 0x2C, size 0x2
};
struct PF_LOCK {
    // total size: 0x10
    unsigned short mode; // offset 0x0, size 0x2
    unsigned short count; // offset 0x2, size 0x2
    unsigned long wcount; // offset 0x4, size 0x4
    struct PF_FILE * owner; // offset 0x8, size 0x4
    long resource; // offset 0xC, size 0x4
};
struct PF_SFD {
    // total size: 0x290
    unsigned long stat; // offset 0x0, size 0x4
    struct PF_FFD ffd; // offset 0x4, size 0x38
    struct PF_DIR_ENT dir_entry; // offset 0x3C, size 0x240
    struct PF_LOCK lock; // offset 0x27C, size 0x10
    unsigned short num_handlers; // offset 0x28C, size 0x2
};
struct PF_SDD {
    // total size: 0x280
    unsigned long stat; // offset 0x0, size 0x4
    unsigned short num_handlers; // offset 0x4, size 0x2
    struct PF_FFD ffd; // offset 0x8, size 0x38
    struct PF_DIR_ENT dir_entry; // offset 0x40, size 0x240
};
struct PF_DIR_CURSOR {
    // total size: 0xC
    unsigned long physical_entry_index; // offset 0x0, size 0x4
    unsigned long logical_entry_index; // offset 0x4, size 0x4
    unsigned long logical_seek_index; // offset 0x8, size 0x4
};
struct PF_DIR {
    // total size: 0x20
    unsigned long stat; // offset 0x0, size 0x4
    struct PF_SDD * p_sdd; // offset 0x4, size 0x4
    struct PF_FAT_HINT hint; // offset 0x8, size 0xC
    struct PF_DIR_CURSOR cursor; // offset 0x14, size 0xC
};
struct PF_CACHE_PAGE {
    // total size: 0x28
    unsigned short stat; // offset 0x0, size 0x2
    unsigned short option; // offset 0x2, size 0x2
    unsigned char * buffer; // offset 0x4, size 0x4
    unsigned char * p_buf; // offset 0x8, size 0x4
    unsigned char * p_mod_sbuf; // offset 0xC, size 0x4
    unsigned char * p_mod_ebuf; // offset 0x10, size 0x4
    unsigned long size; // offset 0x14, size 0x4
    unsigned long sector; // offset 0x18, size 0x4
    void * signature; // offset 0x1C, size 0x4
    struct PF_CACHE_PAGE * p_next; // offset 0x20, size 0x4
    struct PF_CACHE_PAGE * p_prev; // offset 0x24, size 0x4
};
struct PF_SECTOR_CACHE {
    // total size: 0x24
    unsigned long mode; // offset 0x0, size 0x4
    unsigned short num_fat_pages; // offset 0x4, size 0x2
    unsigned short num_data_pages; // offset 0x6, size 0x2
    struct PF_CACHE_PAGE * pages; // offset 0x8, size 0x4
    struct PF_CACHE_PAGE * p_current_fat; // offset 0xC, size 0x4
    struct PF_CACHE_PAGE * p_current_data; // offset 0x10, size 0x4
    unsigned char (* buffers)[512]; // offset 0x14, size 0x4
    unsigned long fat_buff_size; // offset 0x18, size 0x4
    unsigned long data_buff_size; // offset 0x1C, size 0x4
    void * signature; // offset 0x20, size 0x4
};
struct PF_CUR_DIR {
    // total size: 0x248
    unsigned long stat; // offset 0x0, size 0x4
    long context_id; // offset 0x4, size 0x4
    struct PF_DIR_ENT directory; // offset 0x8, size 0x240
};
struct PF_DIR_TAIL {
    // total size: 0xC
    unsigned long tracker_size; // offset 0x0, size 0x4
    unsigned long tracker_buff[1]; // offset 0x4, size 0x4
    unsigned long * tracker_bits; // offset 0x8, size 0x4
};
struct PF_CLUSTER_LINK_VOL {
    // total size: 0xC
    unsigned short flag; // offset 0x0, size 0x2
    unsigned short interval; // offset 0x2, size 0x2
    unsigned long * buffer; // offset 0x4, size 0x4
    unsigned long link_max; // offset 0x8, size 0x4
};
struct PF_CHARCODE {
    // total size: 0x18
    long (* oem2unicode)(signed char *, unsigned short *); // offset 0x0, size 0x4
    long (* unicode2oem)(unsigned short *, signed char *); // offset 0x4, size 0x4
    long (* oem_char_width)(signed char *); // offset 0x8, size 0x4
    unsigned long (* is_oem_mb_char)(signed char, unsigned long); // offset 0xC, size 0x4
    long (* unicode_char_width)(unsigned short *); // offset 0x10, size 0x4
    unsigned long (* is_unicode_mb_char)(unsigned short, unsigned long); // offset 0x14, size 0x4
};
struct PF_CONTEXT {
    // total size: 0x8
    unsigned long stat; // offset 0x0, size 0x4
    long context_id; // offset 0x4, size 0x4
};

#endif // VF_PF_UNSORTED_STRUCTS_H