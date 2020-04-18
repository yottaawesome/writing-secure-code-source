/*
  RC4Test.cpp
*/
#define MAX_BLOB 50
BYTE bPlainText1[MAX_BLOB];
BYTE bPlainText2[MAX_BLOB];
BYTE bCipherText1[MAX_BLOB];
BYTE bCipherText2[MAX_BLOB];
BYTE bKeyStream[MAX_BLOB];
BYTE bKey[MAX_BLOB];

//////////////////////////////////////////////////////////////////
// Setup -  set the two plaintexts and the encryption key.
void Setup() {
    ZeroMemory(bPlainText1, MAX_BLOB);
    ZeroMemory(bPlainText2, MAX_BLOB);
    ZeroMemory(bCipherText1, MAX_BLOB);
    ZeroMemory(bCipherText2, MAX_BLOB);
    ZeroMemory(bKeyStream, MAX_BLOB);
    ZeroMemory(bKey, MAX_BLOB);

    strncpy(reinterpret_cast<char*>(bPlainText1),
        "Hey Frodo, meet me at Weathertop, 6pm.", MAX_BLOB-1);

    strncpy(reinterpret_cast<char*>(bPlainText2),
        "Saruman has me prisoner in Orthanc.", MAX_BLOB-1);

    strncpy(reinterpret_cast<char*>(bKey),
        GetKeyFromUser(), MAX_BLOB-1);	//  External function
}

//////////////////////////////////////////////////////////////////
// Encrypt - encrypts a blob of data using RC4.
void Encrypt(LPBYTE bKey, 
             LPBYTE bPlaintext,
             LPBYTE bCipherText, 
             DWORD dwHowMuch) {
                 HCRYPTPROV hProv;
                 HCRYPTKEY  hKey;
                 HCRYPTHASH hHash;

    /*
      The way this works is as follows:
      Acquire a handle to a crypto provider.
      Create an empty hash object.
      Hash the key provided into the hash object.
      Use the hash created in step 3 to derive a crypto key. This key 
      also stores the algorithm to perform the encryption.
      Use the crypto key from step 4 to encrypt the plaintext.
    */

    DWORD dwBuff = dwHowMuch;
    CopyMemory(bCipherText, bPlaintext, dwHowMuch);
    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 
                             CRYPT_VERIFYCONTEXT))
        throw;
    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
        throw;
    if (!CryptHashData(hHash, bKey, MAX_BLOB, 0))
        throw;
    if (!CryptDeriveKey(hProv, CALG_RC4, hHash, 
                        CRYPT_EXPORTABLE, 
                        &hKey))
        throw;
    if (!CryptEncrypt(hKey, 0, TRUE, 0, 
                      bCipherText, 
                      &dwBuff, 
                      dwHowMuch))
        throw;

    if (hKey)  CryptDestroyKey(hKey);
    if (hHash) CryptDestroyHash(hHash);
    if (hProv) CryptReleaseContext(hProv, 0);
}

void main() {
    Setup();

    // Encrypt the two plaintexts using the key, bKey.
    try {
        Encrypt(bKey, bPlainText1, bCipherText1, MAX_BLOB);
        Encrypt(bKey, bPlainText2, bCipherText2, MAX_BLOB);
    } catch (...) {
        printf("Error - %d", GetLastError());
        return;
    }

    // Now do the “magic.”
    //  Get each byte from the known ciphertext or plaintext.
    for (int i = 0; i < MAX_BLOB; i++) {
        BYTE c1 = bCipherText1[i];        //  Ciphertext #1 bytes
        BYTE p1 = bPlainText1[i];         //  Plaintext #1 bytes
        BYTE k1 = c1 ^ p1;                //  Get keystream bytes.
        BYTE p2 = k1 ^ bCipherText2[i];   //  Plaintext #2 bytes

        // Print each byte in the second message.
        printf("%c", p2);
    }
}
