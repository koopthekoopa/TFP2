#include <private/atok/atok_eng.h>
#include <revolution/os.h>

#ifdef DEBUG
const char* __JUSTSYSTEMS_ATOKVersion = "<< RVL_MWM - JUSTSYSTEMS_ATOK \tdebug build: Jul  3 2007 15:28:25 (0x4199_60726) >>";
#else
const char* __JUSTSYSTEMS_ATOKVersion = "<< RVL_MWM - JUSTSYSTEMS_ATOK \trelease build: Jul  3 2007 15:28:21 (0x4199_60726) >>";
#endif

s32 ATOKOpen(void* openPack) {
    OSRegisterVersion(__JUSTSYSTEMS_ATOKVersion);
    return ATOK_open(openPack);
}

s32 ATOKClose() {
    return ATOK_close();
}

s32 ATOKDrive(void* commandPack) {
    return ATOK_drive(commandPack);
}
