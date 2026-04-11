#ifndef REVOLUTION_VF_TYPES_H
#define REVOLUTION_VF_TYPES_H

#include <revolution/types.h>

/* Some apps have ErrInfoTbl which have all of the errors codes. */
enum {
    VF_ERR_SUCCESS = 0,     // Success

    // PrFILE2 errors
    VF_ERR_EPERM = 1,       // "Operation is not possible"
    VF_ERR_ENOENT = 2,      // "No such file or directory"
    VF_ERR_EIO = 5,         // "I/O Error(Driver Error)"
    VF_ERR_ENOEXEC = 8,     // "Not Executable by internal"
    VF_ERR_EBADF = 9,       // "Bad file descripto"
    VF_ERR_ENOMEM = 12,     // "Not enough system memory"
    VF_ERR_EACCES = 13,     // "Permission denied"
    VF_ERR_EBUSY = 16,      // "Can not use system resouces"
    VF_ERR_EEXIST = 17,     // "File already exists"
    VF_ERR_EISDIR = 21,     // "find directory when file req"
    VF_ERR_EINVAL = 22,     // "Invalid argument"
    VF_ERR_ENFILE = 23,     // "Too many open files(system)"
    VF_ERR_EMFILE = 24,     // "Too many open files(user)"
    VF_ERR_EFBIG = 27,      // "Over file size limit(4GB-1)"
    VF_ERR_ENOSPC = 28,     // "Device out of space"
    VF_ERR_ENOLCK = 46,     // "Can not lock the file"
    VF_ERR_ENOSYS = 88,     // "Not implement function"
    VF_ERR_ENOTEMPTY = 90,  // "Directory is not empty"

    // API exclusive errors
    VF_ERR_NOT_EXIST_FILE = 0xB001,
    VF_ERR_CANNOT_ALLOC_DRV = 0xB002,
    VF_ERR_NOT_ALLOCATED_DRV = 0xB003,
    VF_ERR_ALREADY_ATTACHED_DRV_NAME = 0xB004,
    VF_ERR_ALREADY_MOUNTED_DRV_NAME = 0xB005,
    VF_ERR_VFF_FILE_FORMAT = 0xB006,

    // Unknown
    VF_ERR_SYSTEM = -1  // "system error(general error)"
};

typedef void VF_FILE;

#endif  // REVOLUTION_VF_TYPES_H
