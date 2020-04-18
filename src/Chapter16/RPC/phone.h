/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Aug 17 16:29:52 2001
 */
/* Compiler settings for phone.idl:
    Oicf (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __phone_h__
#define __phone_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __phone_INTERFACE_DEFINED__
#define __phone_INTERFACE_DEFINED__

/* interface phone */
/* [strict_context_handle][explicit_handle][unique][version][uuid] */ 

void Message( 
    /* [in] */ handle_t h,
    /* [string][in] */ unsigned char __RPC_FAR *pszString);



extern RPC_IF_HANDLE phone_v1_0_c_ifspec;
extern RPC_IF_HANDLE phone_v1_0_s_ifspec;
#endif /* __phone_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
