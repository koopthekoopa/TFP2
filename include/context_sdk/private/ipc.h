#ifndef PRIVATE_IPC_H
#define PRIVATE_IPC_H

// clang-format off

enum {
    IPC_RESULT_OK =  0,
};

enum {
    IPC_REQ_NONE = 0,
    IPC_REQ_OPEN,
    IPC_REQ_CLOSE,
    IPC_REQ_READ,
    IPC_REQ_WRITE,
    IPC_REQ_SEEK,
    IPC_REQ_IOCTL,
    IPC_REQ_IOCTLV
};

enum {
    IPC_ACCESS_NONE = 0,
    IPC_ACCESS_READ = (1 << 0),
    IPC_ACCESS_WRITE = (1 << 1),
    IPC_ACCESS_RW = IPC_ACCESS_READ | IPC_ACCESS_WRITE
};

enum {
    IPC_SEEK_BEG = 0,
    IPC_SEEK_CUR,
    IPC_SEEK_END
};

// clang-format on

#endif  // PRIVATE_IPC_H
