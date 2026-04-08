#include <private/vf/pf_fwrite.h>

#include <private/vf/pf_api_util.h>
#include <private/vf/pf_volume.h>

pf_u32 VFipf2_fwrite(void* p_buf, pf_u32 size, pf_u32 count, PF_FILE* p_file) {
    pf_u32 count_written;
    VFiPFFILE_fwrite(p_buf, size, count, p_file, &count_written);
    return count_written;
}
