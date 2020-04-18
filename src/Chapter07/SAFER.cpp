/*
  SAFER.cpp
*/
#include <windows.h>
#include <WinSafer.h>
#include <winnt.h>
#include <stdio.h>
#include <strsafe.h>

void main() {
    SAFER_LEVEL_HANDLE hAuthzLevel;

    // Valid programmatic SAFER levels:
    //  SAFER_LEVELID_FULLYTRUSTED
    //  SAFER_LEVELID_NORMALUSER
    //  SAFER_LEVELID_CONSTRAINED
    //  SAFER_LEVELID_UNTRUSTED
    //  SAFER_LEVELID_DISALLOWED

    // Create a normal user level.
    if (SaferCreateLevel(SAFER_SCOPEID_USER,
                         SAFER_LEVELID_NORMALUSER,
                         0, &hAuthzLevel, NULL)) {

        //  Generate the restricted token that we will use.
        HANDLE hToken = NULL;
        if (SaferComputeTokenFromLevel(
            hAuthzLevel,    // Safer Level handle
            NULL,           //  NULL is current thread token.
            &hToken,        // Target token
            0,              // No flags
            NULL)) {        // Reserved

            // Build the path to Cmd.exe to make sure
            // we're not running a Trojaned Cmd.exe.
            char szPath[MAX_PATH+1], szSysDir[MAX_PATH+1];
            if (GetSystemDirectory(szSysDir, sizeof szSysDir)) {
                _StringCbPrintf(szPath,
                          sizeof szPath,
                          "%s\\cmd.exe",
                          szSysDir);
            
                STARTUPINFO si;
                ZeroMemory(&si, sizeof(STARTUPINFO));
                si.cb = sizeof(STARTUPINFO);
                si.lpDesktop = NULL;
            
                PROCESS_INFORMATION pi;
                if (!CreateProcessAsUser( 
                    hToken,
                    szPath, NULL,
                    NULL, NULL,
                    FALSE, CREATE_NEW_CONSOLE,
                    NULL, NULL,  
                    &si, &pi))
                    printf("CreateProcessAsUser failed (%lu)\n",
                           GetLastError() );
            }

        }
        SaferCloseLevel(hAuthzLevel);
    }
}
