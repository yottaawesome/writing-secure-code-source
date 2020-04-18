// NTFSStream.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <windows.h>

void main(void) {

	char b[20];
	lstrcpy(b, "Hello!");
	HANDLE h = CreateFile("c:\\somefile.txt",
                      GENERIC_WRITE,
                      0, NULL,
                      CREATE_ALWAYS,
                      FILE_ATTRIBUTE_NORMAL,
                      NULL);
	if (h != INVALID_HANDLE_VALUE) {
    		DWORD dwNum = 0;
    		WriteFile(h, b, lstrlen(b), &dwNum, NULL);
    		CloseHandle(h);
	}

	h = CreateFile("c:\\somefile.txt.",
               GENERIC_READ,
               0, NULL,
               OPEN_EXISTING,
               FILE_ATTRIBUTE_NORMAL,
               NULL);
	if (h != INVALID_HANDLE_VALUE) {
    		char b[20];
    		DWORD dwNum =0;
    		ReadFile(h, b, sizeof b, & dwNum, NULL);
    		CloseHandle(h);
	}

}

