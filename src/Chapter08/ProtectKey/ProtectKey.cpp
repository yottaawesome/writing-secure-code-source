/*
  ProtectKey.cpp
*/
#include "stdafx.h"
using namespace std;

//Get the symmetric exchange key used to encrypt the key.
void GetExchangeKey(HCRYPTPROV hProv, HCRYPTKEY *hXKey) {
    //The key-exchange key comes from an external source.
    HCRYPTHASH hHash; 
    BYTE bKey[16];
    if (!GetKeyFromStorage(bKey, sizeof bKey))
        throw GetLastError();

    if (!CryptCreateHash(hProv, CALG_SHA1, 0, 0, &hHash))
        throw GetLastError();

    if (!CryptHashData(hHash, bKey, sizeof bKey, 0))   
        throw GetLastError();

    if (!CryptDeriveKey(hProv, CALG_3DES, hHash, CRYPT_EXPORTABLE, 
                        hXKey))
        throw GetLastError();
}

void main() {

    HCRYPTPROV    hProv = NULL;
    HCRYPTKEY     hKey  = NULL;
    HCRYPTKEY     hExchangeKey  = NULL;
    LPBYTE        pbKey = NULL;

    try {
        if (!CryptAcquireContext(&hProv, NULL, NULL,
                                 PROV_RSA_FULL, 
                                 CRYPT_VERIFYCONTEXT))
            throw GetLastError();

        //Generate two 3DES keys, and mark them as exportable.
        //Note: these keys are kept in CryptoAPI at this point.
        if (!CryptGenKey(hProv, CALG_3DES, CRYPT_EXPORTABLE, &hKey))
            throw GetLastError();

        //Get a key that we can use to encrypt the two 3DES keys.
        GetExchangeKey(hProv, &hExchangeKey);

        //Determine blob size.
        DWORD dwLen = 0;
        if (!CryptExportKey(hKey, hExchangeKey,
                            SYMMETRICWRAPKEYBLOB, 
                            0, pb Key, &dwLen))
            throw GetLastError();

        pbKey = new BYTE[dwLen]; //  Array to hold 3DES keys
        ZeroMemory(pbKey, dwLen);

        //Now get the shrouded blob.
        if (!CryptExportKey(hKey, hExchangeKey,
            SYMMETRICWRAPKEYBLOB, 0, pbKey, &dwLen))
            throw GetLastError();

        cout << "Cool, " << dwLen 
             << " byte wrapped key is exported." 
             << endl;

        //Write shrouded key to Key.bin; overwrite if needed
        //using ostream::write() rather than operator<<,
        //as the data may contain NULLs.
        
        ofstream file("c:\\Keys\\key.bin", ios_base::binary);
        file.write(reinterpret_cast<const char *>(pbKey ), dwLen);
        file.close();

    } catch(DWORD e) {
        cerr << "Error " << e << hex << " " << e << endl;
    }

    // Clean up.
    if (hExchangeKey)   CryptDestroyKey(hExchangeKey);
    if (hKey)           CryptDestroyKey(hKey);
    if (hProv)          CryptReleaseContext(hProv, 0);
    if (pbKey)          delete [] pbKey;
}
