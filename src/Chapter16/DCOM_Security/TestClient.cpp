/* TestClient.cpp

  This application shows the effects of various DCOM security settings
  We're going to use old-style calls
  */

#define _WIN32_WINNT 0x0500
#include "../DCOM_Security.h"
#include <objbase.h>
#include <stdio.h>

void DumpSecuritySettings(DWORD AuthNSvc, 
						  DWORD AuthZSvc, 
						  OLECHAR* PriName, 
						  DWORD AuthLevel, 
						  DWORD ImpLevel)
{
	//print the authentication service
	switch(AuthNSvc)
	{
	case RPC_C_AUTHN_NONE:
		printf("No authentication\n");
		break;
	case RPC_C_AUTHN_DCE_PRIVATE:
		printf("DCE private key authentication\n");
		break;
	case RPC_C_AUTHN_DCE_PUBLIC:
		printf("DCE public key authentication\n");
		break;
	case RPC_C_AUTHN_DEC_PUBLIC:
		printf("DEC public key authentication\n");
		break;
	case RPC_C_AUTHN_GSS_NEGOTIATE:
		printf("Snego security support provider\n");
		break;
	case RPC_C_AUTHN_WINNT:
		printf("NTLMSSP (Windows NT LAN Manager Security Support Provider)\n");
		break;
	case RPC_C_AUTHN_GSS_SCHANNEL:
		printf("SChannel security support provider\n");
		break;
	case RPC_C_AUTHN_DPA:
		printf("DPA - Not currently supported\n");
		break;
	case RPC_C_AUTHN_MSN:
		printf("MSN - Not currently supported\n");
		break;
	case RPC_C_AUTHN_GSS_KERBEROS:
		printf("Kerberos security support provider\n");
		break;
	case RPC_C_AUTHN_MQ:
		printf("MQ - Not currently supported\n");
		break;
	case RPC_C_AUTHN_DEFAULT:
		printf("Default auth\n");//shouldn't see this here
		break;
	default:
		printf("New authentication provider %d\n", AuthNSvc);
		break;
	}

	//now print the authorization service
	switch(AuthZSvc)
	{
	case RPC_C_AUTHZ_NONE:
		printf("No authorization\n");
		break;
	case RPC_C_AUTHZ_NAME:
		printf("Authorization based on the client's principal name\n");
		break;
	case RPC_C_AUTHZ_DCE:
		printf("Authorization checking using DCE privilege attribute certificate\n");
		break;
	default:
		printf("Unknown authorization provider %d\n", AuthZSvc);
		break;
	}

	//server name
	if(PriName != NULL)
		wprintf(L"Principal name: %s\n", PriName);

	//now for the authentication level
	switch(AuthLevel)
	{
	case RPC_C_AUTHN_LEVEL_NONE:
		printf("Auth level = none\n");
		break;
	case RPC_C_AUTHN_LEVEL_CONNECT:
		printf("Auth level = Connect\n");
		break;
	case RPC_C_AUTHN_LEVEL_CALL:
		printf("Auth level = Call\n");
		break;
	case RPC_C_AUTHN_LEVEL_PKT:
		printf("Auth level = Packet\n");
		break;
	case RPC_C_AUTHN_LEVEL_PKT_INTEGRITY:
		printf("Auth level = Packet integrity\n");
		break;
	case RPC_C_AUTHN_LEVEL_PKT_PRIVACY:
		printf("Auth level = Packet privacy\n");
		break;
	default:
		printf("Unknown auth level %d\n", AuthLevel);
		break;
	}

	//impersonation level
	switch(ImpLevel)
	{
	case RPC_C_IMP_LEVEL_ANONYMOUS:
		printf("Impersonation level = Anonymous\n");
		break;
	case RPC_C_IMP_LEVEL_IDENTIFY:
		printf("Impersonation level = Identify\n");
		break;
	case RPC_C_IMP_LEVEL_IMPERSONATE:
		printf("Impersonation level = Impersonate\n");
		break;
	case RPC_C_IMP_LEVEL_DELEGATE:
		printf("Impersonation level = Delegate\n");
		break;
	default:
		printf("Unknown impersonation level %d\n", ImpLevel);
		break;
	}
}

void DumpServerSecuritySettings(ISecurityExample* pSecExample)
{
	DWORD AuthNSvc;
	DWORD AuthZSvc;
	DWORD AuthLevel;
	DWORD ImpLevel;
	HRESULT hr;

	hr = pSecExample->GetServerBlanket(&AuthNSvc, &AuthZSvc, &AuthLevel, &ImpLevel);

	if(hr == S_OK)
	{
		printf("\nServer Security Information:\n");

		DumpSecuritySettings(AuthNSvc,
							 AuthZSvc, 
							 NULL, 
							 AuthLevel, 
							 ImpLevel);
	}
	else
	{
		printf("Cannot get server security settings\n");
	}

}

void DumpClientSecuritySettings(IUnknown* pUnk)
{
	IClientSecurity* pClientSec;
	DWORD AuthNSvc;
	DWORD AuthZSvc;
	OLECHAR* PriName;
	DWORD AuthLevel;
	DWORD ImpLevel;

	HRESULT hr = pUnk->QueryInterface(IID_IClientSecurity, (void**)&pClientSec);

	printf("\nClient Security Information:\n");
	if(hr == S_OK)
	{
		hr = pClientSec->QueryBlanket(pUnk,         //interface pointer
									  &AuthNSvc,    //authentication service
									  &AuthZSvc,    //authorization service
									  &PriName,  //Principal name
									  &AuthLevel,   //Authentication level
									  &ImpLevel,    //Impersonation level
									  NULL,      //Auth info requested
									  NULL); //capabilities

		if(hr == S_OK)
		{
			DumpSecuritySettings(AuthNSvc, AuthZSvc, PriName, AuthLevel, ImpLevel);
			CoTaskMemFree(PriName);
		}
		else
		{
			printf("Cannot query client security blanket\n");
		}

		pClientSec->Release();
	}
	else
	{
		printf("Interface does not support IClientSecurity\n");
	}


}

bool SetClientAuthLevel(IUnknown* pUnk, DWORD Level)
{
	IClientSecurity* pClientSec;
	DWORD AuthNSvc;
	DWORD AuthZSvc;
	DWORD AuthLevel;
	DWORD ImpLevel;

	HRESULT hr = pUnk->QueryInterface(IID_IClientSecurity, (void**)&pClientSec);

	//first we have to get the current settings
	if(hr == S_OK)
	{
		hr = pClientSec->QueryBlanket(pUnk,         //interface pointer
									  &AuthNSvc,    //authentication service
									  &AuthZSvc,    //authorization service
									  NULL,         //Principal name
									  &AuthLevel,   //Authentication level
									  &ImpLevel,    //Impersonation level
									  NULL,      //Auth info requested
									  NULL); //capabilities

		if(hr == S_OK)
		{
			//now we can set what we'd like
			hr = pClientSec->SetBlanket(pUnk, 
										AuthNSvc, 
										AuthZSvc, 
										NULL, 
										Level, 
										ImpLevel, 
										NULL, 
										EOAC_NONE);
			if(hr == S_OK)
				return true;
			else
				return false;
		}
		else
		{
			printf("Cannot query client security blanket\n");
		}

		pClientSec->Release();
	}
	else
	{
		printf("Interface does not support IClientSecurity\n");
	}

	return false;
}


//DCOM wants UNICODE for server names - using wmain makes this easier
int wmain(int argc, WCHAR* argv[])
{
	HRESULT hr;

	if(argc == 1)
	{
		wprintf(L"Usage is %s [server name]\n", argv[0]);
		return -1;
	}

	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if(hr != ERROR_SUCCESS)
	{
		printf("Cannot initialize?\n");
		return -1;
	}

	COSERVERINFO ServerInfo;

	//set up the COSERVERINFO struct
	ServerInfo.dwReserved1 = 0;  //the reserved fields must be 0
	ServerInfo.dwReserved2 = 0;
	ServerInfo.pAuthInfo = NULL; //change this later
	ServerInfo.pwszName = argv[1]; //server name

	//also need to set up our MULTI_QI struct - 
	MULTI_QI qi;

	qi.pIID = &IID_IUnknown; //the interface ID we want to open
	qi.pItf = NULL; //this returns the pointer to the interface - init to NULL
	qi.hr = 0;      //return for this interface

	hr = CoCreateInstanceEx(CLSID_SecurityExample, //CLSID to create
							NULL,                 //this isn't an aggregate
							CLSCTX_REMOTE_SERVER, //type of object
							&ServerInfo,          //server information
							1,                    //we only want 1 interface
							&qi);

	switch(hr)
	{
	case E_INVALIDARG:
		printf("Invalid argument\n");
		break;

	case S_OK:
		break;

	case CO_S_NOTALLINTERFACES:
		printf("Not all interfaces are available\n");
		break;

	case E_NOINTERFACE:
		printf("None of the interfaces requested are available\n");
		break;

	case REGDB_E_CLASSNOTREG:
		printf("Class not registered\n");
		break;
	default:
		printf("Unknown error %d (%x)\n", GetLastError(), GetLastError());
		break;
	}

	if(hr != S_OK || qi.hr != S_OK)
	{
		CoUninitialize();
		return -1;
	}

	IUnknown* pUnk = qi.pItf;
	ISecurityExample* pSecExample;

	//we now have an interface to IUnknown - let's get an interface that's useful
	hr = pUnk->QueryInterface(IID_ISecurityExample, (void**)&pSecExample);

	if(hr == S_OK)
	{
		//now let's examine our client-side security
		printf("Initial client security settings:\n");
		DumpClientSecuritySettings(pSecExample);

		//and what's up at the server?
		if(!SetClientAuthLevel(pSecExample, RPC_C_AUTHN_LEVEL_PKT_PRIVACY))
		{
			printf("Cannot set client auth level\n");
		}
		else
		{
			printf("\nSet auth level to Packet Privacy\n");
		}

		DumpServerSecuritySettings(pSecExample);

		pSecExample->Release();
	}
	else
	{
		printf("Cannot get pointer to ISecurityExample\n");
	}

	pUnk->Release();
	CoUninitialize();
	return 0;
}