/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Sep 07 10:01:09 2001
 */
/* Compiler settings for I:\compdisc\Chapter 10\DCOM_Security\DCOM_Security.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_ISecurityExample = {0xFAC42B1C,0xA883,0x45FD,{0x94,0x22,0x0B,0xD7,0x3E,0xC2,0x6E,0xCD}};


const IID LIBID_DCOM_SECURITYLib = {0xFA433FAF,0x4A94,0x49E1,{0xA6,0xCB,0x3F,0x09,0x2F,0x6D,0xA5,0x38}};


const CLSID CLSID_SecurityExample = {0xBBE980C5,0xD465,0x4281,{0x92,0x0F,0x5B,0xBB,0x5C,0xBD,0xB0,0x3F}};


#ifdef __cplusplus
}
#endif

