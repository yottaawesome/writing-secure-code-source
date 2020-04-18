// CreateRandomPrefix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define PREFIX_SIZE (3)

DWORD GetRandomPrefix(TCHAR *szPrefix) {
    HCRYPTPROV hProv = NULL;
    DWORD dwErr = 0;
    TCHAR *szValues = 
        TEXT("abcdefghijklmnopqrstuvwxyz0123456789");

    if (CryptAcquireContext(&hProv,
                            NULL, NULL,
                            PROV_RSA_FULL,
                            CRYPT_VERIFYCONTEXT) == FALSE) 
        return GetLastError();

    for (int i = 0; i < PREFIX_SIZE; i++) {
        DWORD dwTemp;
        CryptGenRandom(hProv, sizeof DWORD, (LPBYTE)&dwTemp);
        szPrefix[i] = szValues[dwTemp % lstrlen(szValues)];
    }

    szPrefix[PREFIX_SIZE] = '\0';

    if (hProv) 
        CryptReleaseContext(hProv, 0);

    return dwErr;
}

void main(void) {		
	TCHAR szPre[PREFIX_SIZE+1];
	for (int i = 0; i < 100; i++) {
		DWORD err = GetRandomPrefix(szPre);
		if (err == 0)
			puts(szPre);
	}
}

