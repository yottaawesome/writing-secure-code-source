// SaltedHash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void main() {
	HCRYPTPROV hProv;
	HCRYPTHASH hHash;

	char *bSecret="Hello!";
	DWORD cbSecret = lstrlen(bSecret);

	char *bSalt="87823";
	DWORD cbSalt = lstrlen(bSalt);
	
	try {
		if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) 
			throw;

		if (!CryptCreateHash(hProv, CALG_SHA1, 0, 0, &hHash))
                        throw;

                if (!CryptHashData(hHash, (LPBYTE)bSecret, cbSecret, 0))
                        throw;  
 
                if (!CryptHashData(hHash, (LPBYTE)bSalt, cbSalt, 0))
                        throw;

                // Get the size of the resulting salted hash.
                DWORD cbSaltedHash = 0;
		DWORD cbSaltedHashLen = sizeof (DWORD);

                
                if (!CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)&cbSaltedHash, &cbSaltedHashLen, 0))
                        throw;
   
                // Get the salted hash.
                BYTE *pbSaltedHash = new BYTE[cbSaltedHash];

                if (NULL == *pbSaltedHash) throw;

                if (!CryptGetHashParam(hHash, HP_HASHVAL, pbSaltedHash, &cbSaltedHash, 0))
                        throw;

	        } catch(...) {
		printf("Oops! %d", GetLastError());
	}
}

