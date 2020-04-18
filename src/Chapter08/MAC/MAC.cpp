/*
  MAC.cpp
*/
#include "stdafx.h"
DWORD HMACStuff(void *szKey, DWORD cbKey, 
                void *pbData, DWORD cbData,
                LPBYTE *pbHMAC, LPDWORD pcbHMAC) {
   
    DWORD dwErr = 0;
    HCRYPTPROV hProv;
    HCRYPTKEY hKey;
    HCRYPTHASH hHash, hKeyHash;

    try {
        if (!CryptAcquireContext(&hProv, 0, 0,
            PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) 
            throw;
      
        // Derive the hash key.
        if (!CryptCreateHash(hProv, CALG_SHA1, 0, 0, &hKeyHash))
            throw;

        if (!CryptHashData(hKeyHash, (LPBYTE)szKey, cbKey, 0))
            throw;

        if (!CryptDeriveKey(hProv, CALG_DES,
            hKeyHash, 0, &hKey))
            throw;

        // Create a hash object.
        if(!CryptCreateHash(hProv, CALG_HMAC, hKey, 0, &hHash))
            throw;    

        HMAC_INFO hmacInfo;
        ZeroMemory(&hmacInfo, sizeof(HMAC_INFO));
        hmacInfo.HashAlgid = CALG_SHA1;
    
        if(!CryptSetHashParam(hHash, HP_HMAC_INFO, 
                             (LPBYTE)&hmacInfo, 
                              0)) 
            throw;   
 
        // Compute the HMAC for the data.
        if(!CryptHashData(hHash, (LPBYTE)pbData, cbData, 0))
            throw;

        // Allocate memory, and get the HMAC.
        DWORD cbHMAC = 0;
        if(!CryptGetHashParam(hHash, HP_HASHVAL, NULL, &cbHMAC, 0))
            throw;

        // Retrieve the size of the hash. 
        *pcbHMAC = cbHMAC;
        *pbHMAC = new BYTE[cbHMAC];
        if (NULL == *pbHMAC)
            throw;

        if(!CryptGetHashParam(hHash, HP_HASHVAL, *pbHMAC, &cbHMAC, 0))
            throw;

    } catch(...) {
        printf("Error - %d", GetLastError());
        dwErr = GetLastError();
    }

    if (hProv)      CryptReleaseContext(hProv, 0);
    if (hKeyHash)   CryptDestroyKey(hKeyHash);
    if (hKey)       CryptDestroyKey(hKey);
    if (hHash)      CryptDestroyHash(hHash);

    return dwErr;
}

void main() {
    // Key comes from the user.
    char *szKey = GetKeyFromUser();
    DWORD cbKey = lstrlen(szKey);
    if (cbKey == 0) {
        printf("Error – you did not provide a key.\n");
        return -1;
    }

    char *szData="In a hole in the ground...";
    DWORD cbData = lstrlen(szData);

    // pbHMAC will contain the HMAC.
    // The HMAC is cbHMAC bytes in length.
    LPBYTE pbHMAC = NULL;
    DWORD cbHMAC = 0;
    DWORD dwErr = HMACStuff(szKey, cbKey,
                            szData, cbData,
                            &pbHMAC, &cbHMAC);

    // Do something with pbHMAC.

    delete [] pbHMAC;
}
