// UTF8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MAX_CHAR 255

void ToUTF8(LPWSTR wszChar) {
	BYTE bUTF8[MAX_CHAR+1];
	DWORD cbUTF8 = MAX_CHAR;

	ZeroMemory(bUTF8,MAX_CHAR);

	int iRes = WideCharToMultiByte(CP_UTF8,
						0,
						wszChar,
						-1,
						(LPSTR)bUTF8,
						cbUTF8,
						NULL,
						NULL);

	if (iRes == 0) {
		DWORD dwErr = GetLastError();
		printf("WideCharToMultiByte() failed -> %d",dwErr);
	} else {
		printf("WideCharToMultiByte() succeeded! ");
		for (int i=0; i < iRes-1; i++)
			printf("%02x ",bUTF8[i]);

		printf("\n");
	}
}

void FromUTF8(LPBYTE pUTF8, DWORD cbUTF8) {
	WCHAR wszResult[MAX_CHAR+1];
	DWORD dwResult = MAX_CHAR;

	int iRes = MultiByteToWideChar(CP_UTF8,
						0,
						(LPCSTR)pUTF8,
						cbUTF8,
						wszResult,
						dwResult);

	if (iRes == 0) {
		DWORD dwErr = GetLastError();
		printf("MultiByteToWideChar() failed -> %d\n",dwErr);
	} else {
		printf("MultiByteToWideChar() returned "
			   "%s (%d) wide characters\n",
			   wszResult,
			   iRes);
	}
}

void main() {
	
	ToUTF8(L"\\");

	// Get Unicode for 0x5c; should be '\'.
	BYTE pUTF8_1[] = {0x5C};
	DWORD cbUTF8_1 = sizeof pUTF8_1;
	FromUTF8(pUTF8_1,cbUTF8_1);

	// Get Unicode for 0xC0 0xAF. 
    // Should fail because this is 
    // an overlong '/'.


	BYTE pUTF8_2[] = {0xC0, 0xAF};
	DWORD cbUTF8_2 = sizeof pUTF8_2;
	FromUTF8(pUTF8_2, cbUTF8_2);

	// Get Unicode for 0xC2 0xA9; should be 
    // a '©' symbol.
 
	BYTE pUTF8_3[] = {0xC2, 0xA9};
	DWORD cbUTF8_3 = sizeof pUTF8_3;
	FromUTF8(pUTF8_3, cbUTF8_3);
}