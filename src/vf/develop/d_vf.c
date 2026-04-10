
#include <private/vf/develop/d_vf_sys.h>

#include <revolution/vf.h>

#include <private/vf/develop/d_hash.h>

#include <private/vf/PrFILE2/common/pf_clib.h>

#include <private/vf/PrFILE2/standard/pf_attach.h>
#include <private/vf/PrFILE2/standard/pf_errnum.h>
#include <private/vf/PrFILE2/standard/pf_init_prfile2.h>

#include <revolution/os.h>

static pf_bool /* ? */ l_vf_init = PF_FALSE;

static BOOL l_InitedMutex = FALSE;
static OSMutex l_Mutex;

static void _VFInitMutex() {
    if (!l_InitedMutex) {
        OSInitMutex(&l_Mutex);
        l_InitedMutex = TRUE;
    }
}

static void _VFLockMutex() {
    if (l_InitedMutex) {
        OSLockMutex(&l_Mutex);
    }
}

static void _VFUnlockMutex() {
    if (l_InitedMutex) {
        OSUnlockMutex(&l_Mutex);
    }
}

s32 VFIsAvailable() {
    return l_vf_init == PF_FALSE ? PF_FALSE : PF_TRUE;
}

void VFInitEx(void* i_heap_start_address_p, u32 i_size) {
    _VFInitMutex();

    _VFLockMutex();
    {
        if (!l_vf_init) {
            l_vf_init = PF_TRUE;
            VFSysInit(i_heap_start_address_p, i_size);
            VFipdm_init_diskmanager(0U, NULL);
            VFipf2_init_prfile2(0, NULL);
            dHash_InitHashTable();
            VFSysSetTimeStampCallback(NULL);
        }
    }
    _VFUnlockMutex();
}

static char l_vf_drive_work[0x68000];

void VFInit() {
    VFInitEx(l_vf_drive_work, sizeof(l_vf_drive_work));
}

void VFFinalize() {
    _VFLockMutex();
    {
        if (l_vf_init) {
            VFSysFinalize();
            l_vf_init = PF_FALSE;
        }
    }
    _VFUnlockMutex();
}

s32 VFAttachDriveNANDFlash(const char* i_drive) {
    s32 err;
    s32 idx;

    err = 0xB004;
    idx = -1;
    _VFLockMutex();
    {
        if (dHash_GetArg(i_drive) == -1) {
            err = VFSysSetDeviceNANDFlash(&idx, NULL, 0U);
            if (err == 0) {
                dHash_SetArg(i_drive, idx);
            }
        }
        VFSysSetLastError(err);
    }
    _VFUnlockMutex();
    return err;
}

static s32 VFDetachDrive_common(const char* i_drive, u8 i_set_err) {
    s32 err;
    _VFLockMutex();
    {
        s32 idx;
        idx = dHash_GetArg(i_drive);
        err = VFSysUnsetDevice(idx);
        if (err == 0) {
            dHash_DeleteData(i_drive);
        }
        if (i_set_err) {
            VFSysSetLastError(err);
        }
    }
    _VFUnlockMutex();
    return err;
}

s32 VFCreateSystemFileNANDFlashEx(const char* i_sys_file_name_p, u32 i_file_size) {
    s32 DevErr;

    _VFLockMutex();
    DevErr = VFSysCreatePrfFileNANDFlashEx(i_sys_file_name_p, i_file_size);
    _VFUnlockMutex();

    return DevErr;
}

static s32 VF_activate_drive_common(s32 i_handle_idx, const char* i_sys_file_name_p, void* i_memory_p) {
    {
        s32 err;
        s32 errChk;
        err = 0;
        errChk = 0;
        errChk = VFSysCheckExistPrfFile(i_handle_idx, i_sys_file_name_p, i_memory_p);
        if (errChk != 0) {
            VFSysSetLastError(errChk);
            return errChk;
        }
        err = VFSysMountDrv(i_handle_idx, i_sys_file_name_p, i_memory_p);
        if (err != 0) {
            VFSysSetLastError(err);
            return err;
        }
    }

    {
        VFSys_drive* drive_p;
        PF_DRV_TBL* drv_tbl[2];
        s32 err;
        drive_p = VFSysGetDriveP(i_handle_idx);
        if (drive_p == NULL) {
            VFSysSetLastError(0xB002);
            return 0xB002;
        }
        drv_tbl[0] = &drive_p->pf_drv;
        drv_tbl[1] = 0;
        err = VFipf2_attach(drv_tbl);
        if (err != 0) {
            err = VFipf2_errnum();
            VFSysSetLastError(err);
            VFipdm_close_partition(drive_p->pf_part_p);
            return err;
        }
    }
    return 0;
}

static s32 VF_activate_drive(const char* i_drive, const char* i_sys_file_name_p, void* i_memory_p) {
    s32 handle_idx;

    handle_idx = dHash_GetArg(i_drive);
    VFSysSetNandFuncNormal(handle_idx);
    return VF_activate_drive_common(handle_idx, i_sys_file_name_p, i_memory_p);
}

static s32 VF_activate_driveEx(const char* i_drive, const char* i_sys_file_name_p, void* i_memory_p) {
    s32 handle_idx;

    handle_idx = dHash_GetArg(i_drive);
    VFSysSetNandFuncEx(handle_idx);
    return VF_activate_drive_common(handle_idx, i_sys_file_name_p, i_memory_p);
}

s32 VFActivateDriveNANDFlash(const char* i_drive, const char* i_sys_file_name_p) {
    s32 Err;

    _VFLockMutex();
    Err = VF_activate_drive(i_drive, i_sys_file_name_p, NULL);
    _VFUnlockMutex();
    return Err;
}

s32 VFActivateDriveNANDFlashEx(const char* i_drive, const char* i_sys_file_name_p) {
    s32 Err;

    _VFLockMutex();
    Err = VF_activate_driveEx(i_drive, i_sys_file_name_p, NULL);
    _VFUnlockMutex();
    return Err;
}

static s32 VFInactivateDrive_common(s32 i_handle_idx, u32 i_mode) {
    s32 Err;

    Err = VFSysUnmountDrv(i_handle_idx, i_mode);
    VFSysSetLastError(Err);
    return Err;
}

s32 VFInactivateDrive(const char* i_drive) {
    s32 err;

    _VFLockMutex();
    {
        s32 handle_idx;
        handle_idx = dHash_GetArg(i_drive);
        err = VFInactivateDrive_common(handle_idx, 0U);
    }
    _VFUnlockMutex();
    return err;
}

s32 VFMountDriveNANDFlash(const char* i_drive, const char* i_sys_file_name_p) {
    s32 err;

    err = VFAttachDriveNANDFlash(i_drive);
    if ((err == 0) || (err == 0xB004)) {
        err = VFActivateDriveNANDFlash(i_drive, i_sys_file_name_p);
        if ((err != 0) && (err != 0xB005)) {
            VFDetachDrive_common(i_drive, 0U);
        }
    }
    return err;
}

s32 VFMountDriveNANDFlashEx(const char* i_drive, const char* i_sys_file_name_p) {
    s32 err;

    err = VFAttachDriveNANDFlash(i_drive);
    if ((err == 0) || (err == 0xB004)) {
        err = VFActivateDriveNANDFlashEx(i_drive, i_sys_file_name_p);
        if ((err != 0) && (err != 0xB005)) {
            VFDetachDrive_common(i_drive, 0U);
        }
    }
    return err;
}

s32 VFUnmountDrive(const char* i_drive) {
    s32 err;

    err = VFInactivateDrive(i_drive);
    if (err == 0) {
        err = VFDetachDrive_common(i_drive, 1U);
    }
    return err;
}

static char* VF_path2handleidx(s32* o_handle_idx_p, const char* i_path_p) {
    char drive[8];
    const char* str_p;
    s32 idx;
    const char* ret_p;

    str_p = i_path_p;
    idx = 0;
    ret_p = i_path_p;
    *o_handle_idx_p = -1;
    VFipf_memset(drive, 0, 8U);
    for (; *str_p != '\0'; str_p++, idx++) {
        if (*str_p == '\\' || *str_p == '/') {
            break;
        }
        if (*str_p == ':') {
            *o_handle_idx_p = dHash_GetArg(drive);
            if (((s32)*o_handle_idx_p == -1) || (idx > 7)) {
                ret_p = NULL;
            } else {
                ret_p = str_p + 1;
            }
            break;
        }
        if (idx < 7) {
            drive[idx] = *str_p;
        }
    }
    return (char*)ret_p;
}

void* VFOpenFile(const char* i_path_p, const char* i_mode, u32 i_attr) {
    s32 handle_idx;
    const char* path_p;
    void* pFile;

    (void)i_attr;

    handle_idx = -1;
    path_p = NULL;
    _VFLockMutex();
    {
        path_p = VF_path2handleidx(&handle_idx, i_path_p);
        if (path_p == NULL) {
            VFSysSetLastError(0xB003);
            _VFUnlockMutex();
            return NULL;
        }
        if (handle_idx != -1) {
            pFile = VFSysOpenFile(handle_idx, path_p, i_mode);
        } else {
            pFile = VFSysOpenFile_current(path_p, i_mode);
        }
    }
    _VFUnlockMutex();
    return pFile;
}

s32 VFCloseFile(void* i_file_p) {
    s32 Err;

    _VFLockMutex();
    {
        Err = VFSysCloseFile(i_file_p);
        VFSysSetLastError(Err);
    }
    _VFUnlockMutex();
    return Err;
}

s32 VFSeekFile(void* i_file_p, s32 i_offset, s32 i_origin) {
    s32 Err;

    _VFLockMutex();
    {
        Err = VFSysSeekFile((PF_FILE*)i_file_p, i_offset, i_origin);
        VFSysSetLastError(Err);
    }
    _VFUnlockMutex();
    return Err;
}

s32 VFReadFile(void* i_file_p, void* o_buf_p, u32 i_size, u32* o_read_size_p) {
    s32 Err;

    _VFLockMutex();
    {
        Err = VFSysReadFile(o_read_size_p, o_buf_p, i_size, i_file_p);
        VFSysSetLastError(Err);
    }
    _VFUnlockMutex();
    return Err;
}

s32 VFWriteFile(void* i_file_p, void* i_buf_p, u32 i_size) {
    s32 Err;

    _VFLockMutex();
    {
        Err = VFSysWriteFile(i_buf_p, i_size, i_file_p);
        VFSysSetLastError(Err);
    }
    _VFUnlockMutex();
    return Err;
}

s32 VFDeleteFile(const char* i_path_p) {
    s32 handle_idx;
    const char* path_p;
    s32 Err;

    handle_idx = -1;
    path_p = NULL;
    _VFLockMutex();
    {
        path_p = VF_path2handleidx(&handle_idx, i_path_p);
        if (path_p == NULL) {
            VFSysSetLastError(0xB003);
            _VFUnlockMutex();
            return 0xB003;
        }
        if (handle_idx != -1) {
            Err = VFSysDeleteFile(handle_idx, path_p);
        } else {
            Err = VFSysDeleteFile_current(path_p);
        }
        VFSysSetLastError(Err);
    }
    _VFUnlockMutex();
    return Err;
}

s32 VFCreateDir(const char* i_dir_name_p) {
    s32 handle_idx;
    const char* path_p;
    s32 Err;

    handle_idx = -1;
    path_p = NULL;
    _VFLockMutex();
    {
        path_p = VF_path2handleidx(&handle_idx, i_dir_name_p);
        if (path_p == NULL) {
            VFSysSetLastError(0xB003);
            _VFUnlockMutex();
            return 0xB003;
        }
        if (handle_idx != -1) {
            Err = VFSysCreateDir(handle_idx, path_p);
        } else {
            Err = VFSysCreateDir_current(path_p);
        }
        VFSysSetLastError(Err);
    }
    _VFUnlockMutex();
    return Err;
}

s32 VFGetFileSizeByFd(void* i_file_p) {
    s32 size;
    s32 Err;

    size = -1;
    Err = VFSysGetFileSizeByFd(&size, i_file_p);
    if (Err != 0) {
        VFSysSetLastError(Err);
    }
    return size;
}

s32 VFGetLastError() {
    return VFSysGetLastError();
}

s32 VFGetLastDeviceError(const char* i_drive) {
    s32 err;

    _VFLockMutex();
    {
        if (i_drive != NULL) {
            s32 handle_idx;
            handle_idx = dHash_GetArg(i_drive);
            err = VFSysGetLastDeviceError(handle_idx);
        } else {
            err = VFSysGetLastDeviceError_current();
        }
        VFSysSetLastError(err);
    }
    _VFUnlockMutex();
    return err;
}

s32 VFGetDriveFreeSize(const char* i_drive) {
    s32 size;

    _VFLockMutex();
    {
        if (i_drive != NULL) {
            s32 handle_idx;
            handle_idx = dHash_GetArg(i_drive);
            size = VFSysGetDriveFreeSize(handle_idx);
        } else {
            VFSysSetLastError(-1);
            size = -1;
        }
    }
    _VFUnlockMutex();
    return size;
}

s32 VFFormatDrive(const char* i_drive) {
    s32 err;

    _VFLockMutex();
    {
        s32 handle_idx;
        handle_idx = dHash_GetArg(i_drive);
        err = VFSysFormatDrive(handle_idx);
        VFSysSetLastError(err);
    }
    _VFUnlockMutex();
    return err;
}

s32 VFSetSyncMode(const char* i_drive, u32 i_mode) {
    s32 Err;

    _VFLockMutex();
    {
        if (i_drive != NULL) {
            s32 handle_idx;
            handle_idx = dHash_GetArg(i_drive);
            Err = VFSysSetSyncMode(handle_idx, i_mode);
        } else {
            Err = -1;
        }
        VFSysSetLastError(Err);
    }
    _VFUnlockMutex();
    return Err;
}
