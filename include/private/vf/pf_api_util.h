#ifndef VF_PF_API_UTILITIES_H
#define VF_PF_API_UTILITIES_H

#include <private/vf/pf_types.h>

long VFiPFAPI_ParseOpenModeString(const char* mode_str /* r3 */);
long VFiPFAPI_convertError(long err /* r3 */);
long VFiPFAPI_convertReturnValue(long err /* r3 */);
void* VFiPFAPI_convertReturnValue2NULL(long err /* r3 */, void* p_stream /* r4 */);
long VFiPFAPI_convertReturnValue4unmount(long err /* r3 */);

#endif  // VF_PF_API_UTILITIES_H
