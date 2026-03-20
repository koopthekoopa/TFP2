#ifndef VF_PF_PATH_H
#define VF_PF_PATH_H

#include <private/vf/pf_types.h>
#include <private/vf/pf_str.h>

long VFiPFPATH_cmpNameUni(const unsigned short * p_name /* r1+0x8 */, struct PF_STR * sPattern /* r1+0xC */);
long VFiPFPATH_cmpName(const signed char * sShort /* r1+0x8 */, struct PF_STR * p_pattern /* r29 */, unsigned long is_short_search /* r1+0xC */);
long VFiPFPATH_cmpTailSFN(const signed char * sfn_name /* r1+0x8 */, const signed char * pattern /* r1+0xC */);
void VFiPFPATH_InitTokenOfPath(struct PF_STR * p_str /* r3 */, signed char * path /* r4 */, unsigned long code_mode /* r5 */);
long VFiPFPATH_GetNextTokenOfPath(struct PF_STR * p_str /* r31 */, unsigned long wildcard /* r24 */);
long VFiPFPATH_SplitPath(struct PF_STR * p_path /* r1+0x8 */, struct PF_STR * p_dir_path /* r1+0xC */, struct PF_STR * p_filename /* r1+0x10 */);
unsigned long VFiPFPATH_MatchFileNameWithPattern(const signed char * file_name /* r26 */, struct PF_STR * p_pattern /* r30 */, unsigned long is_long_name /* r29 */);
long VFiPFPATH_putShortName(unsigned char * pDirEntry /* r3 */, const signed char * short_name /* r4 */, unsigned char attr /* r5 */);
long VFiPFPATH_getShortName(signed char * short_name /* r3 */, const unsigned char * pDirEntry /* r4 */, unsigned char attr /* r5 */);
void VFiPFPATH_getLongNameformShortName(signed char * short_name /* r3 */, signed char * long_name /* r4 */, unsigned char flag /* r5 */);
unsigned long VFiPFPATH_GetLengthFromShortname(const signed char * sSrc /* r3 */);
unsigned long VFiPFPATH_GetLengthFromUnicode(const unsigned short * sSrc /* r28 */);
long VFiPFPATH_transformFromUnicodeToNormal(signed char * sDest /* r31 */, const unsigned short * sSrc /* r29 */);
long VFiPFPATH_transformInUnicode(unsigned short * sDestStr /* r29 */, const signed char * sSrcStr /* r27 */);
unsigned long VFiPFPATH_parseShortName(signed char * pDest /* r30 */, struct PF_STR * p_pattern /* r27 */);
long VFiPFPATH_parseShortNameNumeric(signed char * p_char /* r3 */, unsigned long count /* r4 */);
void VFiPFPATH_SetSearchPattern(signed char * p_buf_local /* r29 */, unsigned short * p_buf_unicode /* r30 */, struct PF_STR * p_pattern /* r31 */);
unsigned long VFiPFPATH_CheckExtShortNameSignature(struct PF_STR * p_str /* r30 */);
unsigned long VFiPFPATH_CheckExtShortName(struct PF_STR * p_str /* r30 */, unsigned long target /* r29 */, unsigned long wildcard /* r23 */);
unsigned long VFiPFPATH_GetExtShortNameIndex(struct PF_STR * p_str /* r30 */, unsigned long * p_index /* r24 */);
long VFiPFPATH_AdjustExtShortName(signed char * pName /* r3 */, unsigned long position /* r4 */);

#endif // VF_PF_PATH_H
