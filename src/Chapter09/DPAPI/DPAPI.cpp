// DPAPI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

void main() {

	// Data to protect
   	DATA_BLOB blobIn;
   	blobIn.pbData = reinterpret_cast<BYTE *>("This is my secret data.");    
   	blobIn.cbData = lstrlen(reinterpret_cast<char *>(blobIn.pbData))+1;
   
  	// Optional entropy via an external function call
   	DATA_BLOB blobEntropy;

	blobEntropy.pbData = reinterpret_cast<BYTE *>("*71hdm2%b\x12w9B");
	blobEntropy.cbData = lstrlen(
       reinterpret_cast<char *>(blobEntropy.pbData));

   	// Encrypt the data.
   	DATA_BLOB blobOut;
   	if(CryptProtectData(
       		&blobIn,
       		L"Writing Secure Code Example", 
       		&blobEntropy,                         
       		NULL,                         
       		NULL,                    
       		0,
       		&blobOut))   {
       	printf("Protection worked.\n");
   	} else {
       		printf("Error calling CryptProtectData() -> %x", GetLastError());
       		exit(-1);
   	}

   	// Decrypt the data.
   	DATA_BLOB blobVerify;
   	if (CryptUnprotectData(
      		&blobOut,
       		NULL,
       		&blobEntropy,
       		NULL,                
       		NULL,       
       		0,
       		&blobVerify)) {
       		printf("The decrypted data is: %s\n", blobVerify.pbData);
   	} else {
       		printf("Error calling CryptUnprotectData() -> %x", 
              	GetLastError());
       		exit(-1);
   	}

   	LocalFree(blobOut.pbData);
   	LocalFree(blobVerify.pbData);

} 