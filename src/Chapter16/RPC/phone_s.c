/* this ALWAYS GENERATED file contains the RPC server stubs */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Aug 17 16:29:52 2001
 */
/* Compiler settings for phone.idl:
    Oicf (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#include "phone.h"

#define TYPE_FORMAT_STRING_SIZE   7                                 
#define PROC_FORMAT_STRING_SIZE   35                                

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;

extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;

/* Standard interface: phone, ver. 1.0,
   GUID={0x18F88F5A,0x4B19,0x4b7b,{0xBA,0xD5,0x4F,0x27,0x24,0xDD,0x2F,0xD9}} */


extern const MIDL_SERVER_INFO phone_ServerInfo;

extern RPC_DISPATCH_TABLE phone_v1_0_DispatchTable;

static const RPC_SERVER_INTERFACE phone___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0x18F88F5A,0x4B19,0x4b7b,{0xBA,0xD5,0x4F,0x27,0x24,0xDD,0x2F,0xD9}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    &phone_v1_0_DispatchTable,
    0,
    0,
    0,
    &phone_ServerInfo,
    0
    };
RPC_IF_HANDLE phone_v1_0_s_ifspec = (RPC_IF_HANDLE)& phone___RpcServerInterface;

extern const MIDL_STUB_DESC phone_StubDesc;


static const MIDL_STUB_DESC phone_StubDesc = 
    {
    (void __RPC_FAR *)& phone___RpcServerInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static RPC_DISPATCH_FUNCTION phone_table[] =
    {
    NdrServerCall2,
    0
    };
RPC_DISPATCH_TABLE phone_v1_0_DispatchTable = 
    {
    1,
    phone_table
    };

static const SERVER_ROUTINE phone_ServerRoutineTable[] = 
    {
    (SERVER_ROUTINE)Message
    };

static const unsigned short phone_FormatStringOffsetTable[] = 
    {
    0
    };

static const MIDL_SERVER_INFO phone_ServerInfo = 
    {
    &phone_StubDesc,
    phone_ServerRoutineTable,
    __MIDL_ProcFormatString.Format,
    phone_FormatStringOffsetTable,
    0,
    0,
    0,
    0
    };

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows NT 5.0 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Message */

			0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
#ifndef _ALPHA_
/*  8 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 10 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
#ifndef _ALPHA_
/* 12 */	NdrFcShort( 0x0 ),	/* x86, MIPS, PPC Stack size/offset = 0 */
#else
			NdrFcShort( 0x0 ),	/* Alpha Stack size/offset = 0 */
#endif
/* 14 */	NdrFcShort( 0x0 ),	/* 0 */
/* 16 */	NdrFcShort( 0x0 ),	/* 0 */
/* 18 */	0x42,		/* Oi2 Flags:  clt must size, has ext, */
			0x1,		/* 1 */
/* 20 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */
/* 26 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter h */

/* 28 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 30 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 32 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  4 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */

			0x0
        }
    };
