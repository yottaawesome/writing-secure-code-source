/*
 * PrintableRand.cpp
*/
#include “windows.h"
#include “wincrypt.h"

DWORD CreateRandomData(LPBYTE lpBuff, DWORD cbBuff, BOOL fPrintable) {
    DWORD dwErr = 0;
    HCRYPTPROV hProv = NULL;

    if (CryptAcquireContext(&hProv, NULL, NULL,
                            PROV_RSA_FULL,
                            CRYPT_VERIFYCONTEXT) == FALSE) 
        return GetLastError();

    ZeroMemory(lpBuff, cbBuff);
    if (CryptGenRandom(hProv, cbBuff, lpBuff)) {
        if (fPrintable) { 
            char *szValid="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                          “abcdefghijklmnopqrstuvwxyz"
                          “0123456789"
                          “~`!@#$%^&*()_- +={}[];:’<>,.?|\\/";

            DWORD cbValid = lstrlen(szValid);

            //Convert each byte (0- 255) to a different byte
            //from the list of valid characters above.
            //There is a slight skew because strlen(szValid) is not 
            //an exact multiple of 255.
            for (DWORD i=0; i<cbBuff; i++)
                lpBuff[i] = szValid[lpBuff[i] % cbValid];

            //Close off the string if it’s printable.
            //The data is not zero- terminated if it’s not printable.
            lpBuff[cbBuff-1] = ‘\0’;
        }
    } else {
        dwErr = GetLastError();
    }

    if (hProv != NULL) 
        CryptReleaseContext(hProv, 0);

    return dwErr;
}

void main(void) {
   BYTE bBuff[16];
   if (CreateRandomData(bBuff, sizeof bBuff, FALSE) == 0) {
			//Cool, it worked!
		}
}
