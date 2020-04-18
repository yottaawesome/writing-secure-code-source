// LSASecrets.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <stdio.h>
#include "ntsecapi.h"

bool InitUnicodeString(LSA_UNICODE_STRING* pUs, const WCHAR* input){
     DWORD len = 0;
 
     if(!pUs)
         return false;
 
     if(input){
         len = wcslen(input);
         if(len > 0x7ffe) //32k -1
             return false;
     }
     
     pUs->Buffer = (WCHAR*)input;
     pUs->Length = (USHORT)len * sizeof(WCHAR);
     pUs->MaximumLength = (USHORT)(len + 1) * sizeof(WCHAR);
     return true;
}

LSA_HANDLE GetLSAPolicyHandle(WCHAR *wszSystemName) {

	LSA_OBJECT_ATTRIBUTES ObjectAttributes;
	ZeroMemory(&ObjectAttributes, sizeof(ObjectAttributes));

	LSA_UNICODE_STRING lusSystemName;

	if(!InitUnicodeString(&lusSystemName, wszSystemName))
		return NULL;

	LSA_HANDLE hLSAPolicy = NULL;
	NTSTATUS ntsResult = LsaOpenPolicy(&lusSystemName,    
							&ObjectAttributes, 
							POLICY_ALL_ACCESS, 
							&hLSAPolicy);
	DWORD dwStatus = LsaNtStatusToWinError(ntsResult);
	if (dwStatus != ERROR_SUCCESS) {
		wprintf(L"OpenPolicy returned %lu\n",dwStatus);
		return NULL;
	}
	return hLSAPolicy;
}

DWORD WriteLsaSecret(LSA_HANDLE hLSA, 
					 WCHAR *wszSecret, 
					 WCHAR *wszName) {

	LSA_UNICODE_STRING lucName;
	if(!InitUnicodeString(&lucName, wszName))
		return ERROR_INVALID_PARAMETER;

	LSA_UNICODE_STRING lucSecret;
	if(!InitUnicodeString(&lucSecret, wszSecret))
		return ERROR_INVALID_PARAMETER;

	NTSTATUS ntsResult = LsaStorePrivateData(hLSA,
		                     &lucName, &lucSecret);

	DWORD dwStatus = LsaNtStatusToWinError(ntsResult);

	if (dwStatus != ERROR_SUCCESS) 
		wprintf(L"Store private object failed %lu\n",dwStatus);

	return dwStatus;
}

DWORD ReadLsaSecret(LSA_HANDLE hLSA,
					 DWORD dwBuffLen,
					 WCHAR *wszSecret, 
					 WCHAR *wszName) {
	LSA_UNICODE_STRING lucName;
	if(!InitUnicodeString(&lucName, wszName))
		return ERROR_INVALID_PARAMETER;

	PLSA_UNICODE_STRING plucSecret = NULL;
	NTSTATUS ntsResult = LsaRetrievePrivateData(hLSA, 
		                     &lucName, &plucSecret);

	DWORD dwStatus = LsaNtStatusToWinError(ntsResult);

	if (dwStatus != ERROR_SUCCESS) 
		wprintf(L"Store private object failed %lu\n",dwStatus);
	else
		wcsncpy(wszSecret, plucSecret->Buffer, 
				min((plucSecret->Length)/sizeof WCHAR,dwBuffLen));

	if (plucSecret) 
		LsaFreeMemory(plucSecret);

	return dwStatus;
}

int main(int argc, char* argv[]) {
	LSA_HANDLE hLSA = GetLSAPolicyHandle(NULL);

	WCHAR *wszName = L"L$WritingSecureCode";
	WCHAR *wszSecret = L"My Secret Data!";

	if (WriteLsaSecret(hLSA, wszSecret, wszName) == ERROR_SUCCESS) {
		WCHAR wszSecretRead[128];

		if (ReadLsaSecret(hLSA,
					 sizeof wszSecretRead / sizeof WCHAR,
					 wszSecretRead,
					 wszName) == ERROR_SUCCESS) 
			wprintf(L"LSA Secret '%s' is '%s'\n",wszName,wszSecretRead);
	}
 
	if (hLSA) 
		LsaClose(hLSA);
	return 0;
}
