#include <private/vf/pf_api_util.h>

pf_s32 VFipf_error_to_api_error[] = {0x00, 0x16, 0x16, 0x02, 0x10, 0x5A, 0x1C, 0x08, 0x11, 0x08, 0x16, 0x0D, 0x58, 0x08,
                                     0x08, 0x08, 0x0D, 0x05, 0x08, 0x0D, 0x02, 0x17, 0x18, 0x15, 0x0D, 0x01, 0x08, 0x08,
                                     0x08, 0x08, 0x0C, 0x16, 0x16, 0x08, 0x02, 0x08, 0x08, 0x1B, 0x09, 0x2E};

pf_s32 VFiPFAPI_ParseOpenModeString(const char* mode_str) {
    pf_s32 open_mode = 0;
    pf_u32 i = 0;

    if (mode_str == PF_NULL) {
        open_mode = 10;
        return open_mode;
    }

    switch (mode_str[i++]) {
        case 'r': {
            open_mode = 2;
            break;
        }
        case 'w': {
            open_mode = 1;
            break;
        }
        case 'a': {
            open_mode = 4;
            break;
        }
        default: {
            return 0;
        }
    }

    if (mode_str[i] == 'b') {
        i++;
    }
    switch (mode_str[i++]) {
        case 0: {
            return open_mode;
        }
        case '+': {
            open_mode |= 8;
            break;
        }
        case 't':
        default: {
            return 0;
        }
    }
    switch (mode_str[i++]) {
        case 0: {
            return open_mode;
        }
    }
    return 0;
}

pf_s32 VFiPFAPI_convertError(pf_s32 err) {
    if (err == 0) {
        return 0;
    }
    if (err == -1) {
        return -1;
    }
    if ((err > 0) && (err < 0xA0)) {
        return VFipf_error_to_api_error[err];
    }
    if (err == 0x1000) {
        err = 5;
        return err;
    }
    return err;
}

pf_s32 VFiPFAPI_convertReturnValue(pf_s32 err) {
    if (err == 0) {
        return 0;
    }
    return -1;
}

void* VFiPFAPI_convertReturnValue2NULL(pf_s32 err, void* p_stream) {
    if (err != 0) {
        return PF_NULL;
    }
    return p_stream;
}

pf_s32 VFiPFAPI_convertReturnValue4unmount(pf_s32 err) {
    if (err == 0) {
        return 0;
    }
    if (err == 1) {
        return 1;
    }
    return -1;
}
