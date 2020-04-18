// SecurityExample.cpp : Implementation of CSecurityExample
#include "stdafx.h"
#include "DCOM_Security.h"
#include "SecurityExample.h"
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// CSecurityExample


//STDMETHODIMP CSecurityExample::GetServerBlanket(DWORD *AuthNSvc, DWORD *AuthZSvc, DWORD *AuthLevel, DWORD *ImpLevel, OLECHAR* NameBuf, DWORD size)
STDMETHODIMP CSecurityExample::GetServerBlanket(DWORD *AuthNSvc,
												DWORD *AuthZSvc,
												DWORD *AuthLevel,
												DWORD *ImpLevel)
{
	IServerSecurity* pServerSecurity;
	OLECHAR* PriName;

	if(CoGetCallContext(IID_IServerSecurity,
		(void**)&pServerSecurity) == S_OK)
	{
		HRESULT hr;

		hr = pServerSecurity->QueryBlanket(AuthNSvc, 
										   AuthZSvc, 
										   &PriName, 
										   AuthLevel, 
										   ImpLevel, 
										   NULL, 
										   NULL);

		if(hr == S_OK)
		{

			CoTaskMemFree(PriName);
		}

		return hr;
	}
	else
		return E_NOINTERFACE;
	
}

