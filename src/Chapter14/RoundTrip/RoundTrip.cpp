// RoundTrip.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

////////////////////////////////////////////////////////////////////////////
//  CheckRoundTrip
//  Returns TRUE if the given string round trips between Unicode and the
//  given code page.  Otherwise, it returns FALSE.
////////////////////////////////////////////////////////////////////////////

BOOL CheckRoundTrip(
                    DWORD uiCodePage,
                    LPWSTR wszString) 
{

    BOOL fStatus = TRUE;
    BYTE *pbTemp = NULL;
    WCHAR *pwcTemp = NULL;

    try {
        // Determine if string length is < MAX_STRING_LEN
        // Handles null strings gracefully
        const size_t MAX_STRING_LEN = 200;
        size_t cchCount = 0;
        if (!SUCCEEDED(StringCchLength(wszString, MAX_STRING_LEN, &cchCount))) 
            throw FALSE;

        pbTemp = new BYTE[MAX_STRING_LEN];
        pwcTemp = new WCHAR[MAX_STRING_LEN];
        if (!pbTemp || !pwcTemp) {
            printf("ERROR: No Memory!\n");
            throw FALSE;
        }

        ZeroMemory(pbTemp,MAX_STRING_LEN * sizeof(BYTE));
        ZeroMemory(pwcTemp,MAX_STRING_LEN * sizeof(WCHAR));

        //  Convert from Unicode to the given code page.
        int rc =  WideCharToMultiByte( uiCodePage,
            0,
            wszString,
            -1,
            (LPSTR)pbTemp,
            MAX_STRING_LEN,
            NULL,
            NULL );
        if (!rc) {
            printf("ERROR: WC2MB Error = %d, CodePage = %d, String = %ws\n",
                GetLastError(), uiCodePage, wszString);
            throw FALSE;
        }

        //  Convert from the given code page back to Unicode.
        rc = MultiByteToWideChar( uiCodePage,
            0,
            (LPSTR)pbTemp,
            -1,
            pwcTemp,
            MAX_STRING_LEN / sizeof(WCHAR) );
        if (!rc) {
            printf("ERROR: MB2WC Error = %d, CodePage = %d, String = %ws\n",
                GetLastError(), uiCodePage, wszString);
            throw FALSE;
        }

        //  Get length of original Unicode string, check it's equal to the conversion length.
        size_t Length = 0;
        StringCchLength(wszString, MAX_STRING_LEN,&Length);
        if (Length+1 != rc) {
            printf("Length %d != rc %d\n", Length, rc);
            throw FALSE;
        }

        //  Compare the original Unicode string to the converted string and
        //  make sure they are identical.
        for (size_t ctr = 0; ctr < Length; ctr++) {
            if (pwcTemp[ctr] != wszString[ctr])
                throw FALSE;
        }
    } catch (BOOL iErr) {
        fStatus = iErr;
    }

    if (pbTemp)  delete [] pbTemp;
    if (pwcTemp) delete [] pwcTemp;

    return (fStatus);
}

int _cdecl main(
                int argc,
                char* argv[])
{
    LPWSTR s1 = L"\x00a9MicrosoftCorp";          // Copyright
    LPWSTR s2 = L"To\x221e&Beyond";              // Infinity

    printf("1252 Copyright = %d\n", CheckRoundTrip(1252, s1));
    printf("437  Copyright = %d\n", CheckRoundTrip(437, s1));
    printf("1252 Infinity  = %d\n", CheckRoundTrip(1252, s2));
    printf("437  Infinity  = %d\n", CheckRoundTrip(437, s2));

    return (1);
}
