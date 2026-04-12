#include <private/atok/atok_eng.h>
#include <revolution/os.h>

const char* __JUSTSYSTEMS_ATOKVersion = "<< RVL_MWM - JUSTSYSTEMS_ATOK \tdebug build: Jul  3 2007 15:28:25 (0x4199_60726) >>";

s32 ATOKOpen(void* openPack) {
    OSRegisterVersion(__JUSTSYSTEMS_ATOKVersion);
    ATOK_open(openPack);
}

s32 ATOKClose() {
    ATOK_close();
}

s32 ATOKDrive(void* commandPack) {
    ATOK_drive(commandPack);
}
