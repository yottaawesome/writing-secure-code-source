/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Sep 07 10:01:09 2001
 */
/* Compiler settings for I:\compdisc\Chapter 10\DCOM_Security\DCOM_Security.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DCOM_Security_h__
#define __DCOM_Security_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISecurityExample_FWD_DEFINED__
#define __ISecurityExample_FWD_DEFINED__
typedef interface ISecurityExample ISecurityExample;
#endif 	/* __ISecurityExample_FWD_DEFINED__ */


#ifndef __SecurityExample_FWD_DEFINED__
#define __SecurityExample_FWD_DEFINED__

#ifdef __cplusplus
typedef class SecurityExample SecurityExample;
#else
typedef struct SecurityExample SecurityExample;
#endif /* __cplusplus */

#endif 	/* __SecurityExample_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISecurityExample_INTERFACE_DEFINED__
#define __ISecurityExample_INTERFACE_DEFINED__

/* interface ISecurityExample */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISecurityExample;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FAC42B1C-A883-45FD-9422-0BD73EC26ECD")
    ISecurityExample : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetServerBlanket( 
            DWORD __RPC_FAR *AuthNSvc,
            DWORD __RPC_FAR *AuthZSvc,
            DWORD __RPC_FAR *AuthLevel,
            DWORD __RPC_FAR *ImpLevel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISecurityExampleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISecurityExample __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISecurityExample __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISecurityExample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISecurityExample __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISecurityExample __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISecurityExample __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISecurityExample __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetServerBlanket )( 
            ISecurityExample __RPC_FAR * This,
            DWORD __RPC_FAR *AuthNSvc,
            DWORD __RPC_FAR *AuthZSvc,
            DWORD __RPC_FAR *AuthLevel,
            DWORD __RPC_FAR *ImpLevel);
        
        END_INTERFACE
    } ISecurityExampleVtbl;

    interface ISecurityExample
    {
        CONST_VTBL struct ISecurityExampleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISecurityExample_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISecurityExample_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISecurityExample_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISecurityExample_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISecurityExample_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISecurityExample_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISecurityExample_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISecurityExample_GetServerBlanket(This,AuthNSvc,AuthZSvc,AuthLevel,ImpLevel)	\
    (This)->lpVtbl -> GetServerBlanket(This,AuthNSvc,AuthZSvc,AuthLevel,ImpLevel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISecurityExample_GetServerBlanket_Proxy( 
    ISecurityExample __RPC_FAR * This,
    DWORD __RPC_FAR *AuthNSvc,
    DWORD __RPC_FAR *AuthZSvc,
    DWORD __RPC_FAR *AuthLevel,
    DWORD __RPC_FAR *ImpLevel);


void __RPC_STUB ISecurityExample_GetServerBlanket_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISecurityExample_INTERFACE_DEFINED__ */



#ifndef __DCOM_SECURITYLib_LIBRARY_DEFINED__
#define __DCOM_SECURITYLib_LIBRARY_DEFINED__

/* library DCOM_SECURITYLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DCOM_SECURITYLib;

EXTERN_C const CLSID CLSID_SecurityExample;

#ifdef __cplusplus

class DECLSPEC_UUID("BBE980C5-D465-4281-920F-5BBB5CBDB03F")
SecurityExample;
#endif
#endif /* __DCOM_SECURITYLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
