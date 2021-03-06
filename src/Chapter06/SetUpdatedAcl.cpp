/*
SetUpdatedACL.cpp
*/

#define _WIN32_WINNT 0x0501
#include "windows.h"
#include "aclapi.h"
#include <sddl.h>

int main(int argc, char* argv[]) {
    char *szName = "c:\\junk\\data.txt";
    PACL pDacl = NULL;
    PACL pNewDacl = NULL;
    PSECURITY_DESCRIPTOR sd = NULL;
    PSID sidAuthUsers = NULL;
    DWORD dwErr = 0;

    try {
        dwErr = 
            GetNamedSecurityInfo(szName,
            SE_FILE_OBJECT,
            DACL_SECURITY_INFORMATION,
            NULL,
            NULL,
            &pDacl,
            NULL,
            &sd);
        if (dwErr != ERROR_SUCCESS) 
            throw dwErr;

        EXPLICIT_ACCESS ea;
        ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));

        DWORD cbSid = SECURITY_MAX_SID_SIZE;
        sidAuthUsers = LocalAlloc(LMEM_FIXED,cbSid);
        if (sidAuthUsers == NULL) 
            throw ERROR_NOT_ENOUGH_MEMORY;

        if (!CreateWellKnownSid(WinAuthenticatedUserSid,
            NULL,
            sidAuthUsers,
            &cbSid))
            throw GetLastError();

        BuildTrusteeWithSid(&ea.Trustee, sidAuthUsers);
        ea.grfAccessPermissions = GENERIC_READ;
        ea.grfAccessMode        = SET_ACCESS;
        ea.grfInheritance       = NO_INHERITANCE;
        ea.Trustee.TrusteeForm  = TRUSTEE_IS_SID;
        ea.Trustee.TrusteeType  = TRUSTEE_IS_GROUP;

        dwErr = SetEntriesInAcl(1,&ea,pDacl,&pNewDacl);
        if (dwErr != ERROR_SUCCESS)
            throw dwErr;

        dwErr = 
            SetNamedSecurityInfo(szName,
            SE_FILE_OBJECT,
            DACL_SECURITY_INFORMATION,
            NULL,
            NULL,
            pNewDacl,
            NULL);
    } catch(DWORD e) {
        // error
    }

    if (sidAuthUsers) 
        LocalFree(sidAuthUsers);

    if (sd) 
        LocalFree(sd);

    if (pNewDacl) 
        LocalFree(pNewDacl);

    return dwErr;
}
