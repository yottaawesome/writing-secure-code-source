// SecurityExample.h : Declaration of the CSecurityExample

#ifndef __SECURITYEXAMPLE_H_
#define __SECURITYEXAMPLE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSecurityExample
class ATL_NO_VTABLE CSecurityExample : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSecurityExample, &CLSID_SecurityExample>,
	public IDispatchImpl<ISecurityExample, &IID_ISecurityExample, &LIBID_DCOM_SECURITYLib>
{
public:
	CSecurityExample()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SECURITYEXAMPLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSecurityExample)
	COM_INTERFACE_ENTRY(ISecurityExample)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ISecurityExample
public:
//	STDMETHOD(GetServerBlanket)(DWORD* AuthNSvc, DWORD* AuthZSvc, DWORD* AuthLevel, DWORD* ImpLevel, OLECHAR* NameBuf, DWORD size);
	STDMETHOD(GetServerBlanket)(DWORD* AuthNSvc, DWORD* AuthZSvc, DWORD* AuthLevel, DWORD* ImpLevel);
};

#endif //__SECURITYEXAMPLE_H_
