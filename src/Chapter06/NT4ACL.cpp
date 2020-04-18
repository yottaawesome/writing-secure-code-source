/*
NT4ACL 
*/

#include <windows.h>
#include <stdio.h>
#include <aclapi.h>

void main(){

    PSID pEveryoneSID = NULL, pAdminSID = NULL, pNetworkSID  = NULL;
    PACL pACL = NULL;
    PSECURITY_DESCRIPTOR pSD = NULL;

    //ACL will contain three ACEs:
    //   Network (Deny Access)
    //   Everyone (Read)
    //   Admin (Full Control)
    try { 
        const int NUM_ACES = 3;
        EXPLICIT_ACCESS ea[NUM_ACES];
        ZeroMemory(&ea, NUM_ACES * sizeof(EXPLICIT_ACCESS)) ;

        //Create a well- known SID for the Network logon group.
        SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AU THORITY;
        if (!AllocateAndInitializeSid(&SIDAuthNT, 1,
            SECURITY_NETWORK_RID,
            0, 0, 0, 0, 0, 0, 0,
            &pNetworkSID) ) 
            throw GetLastError();

        ea[0].grfAccessPermissions = GENERIC_ALL;
        ea[0].grfAccessMode = DENY_ACCESS;
        ea[0].grfInheritance= NO_INHERITANCE;
        ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
        ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_G ROUP;
        ea[0].Trustee.ptstrName  = (LPTSTR) pNetworkSID;

        //Create a well-known SID for the Everyone group.
        SID_IDENTIFIER_AUTHORITY SIDAuthWorld =
            SECURITY_WORLD_SID_AUTHORITY;
        if (!AllocateAndInitializeSid(&SIDAuthWorld, 1,
            SECURITY_WORLD_RID,
            0, 0, 0, 0, 0, 0, 0,
            &pEveryoneSID) ) 
            throw GetLastError();

        ea[1].grfAccessPermissions = GENERIC_READ;
        ea[1].grfAccessMode = SET_ACCESS;
        ea[1].grfInheritance= NO_INHERITANCE;
        ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
        ea[1].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_G ROUP;
        ea[1].Trustee.ptstrName  = (LPTSTR) pEveryoneSID;

        //Create a SID for the BUILTIN\Administrators group.
        if (!AllocateAndInitializeSid(&SIDAuthNT, 2,
            SECURITY_BUILTIN_DOMA IN_RID,
            DOMAIN_ALIAS_RID_ADMI NS,
            0, 0, 0, 0, 0, 0,
            &pAdminSID) ) 
            throw GetLastError(); 

        ea[2].grfAccessPermissions = GENERIC_ALL;
        ea[2].grfAccessMode = SET_ACCESS;
        ea[2].grfInheritance= NO_INHERITANCE;
        ea[2].Trustee.TrusteeForm = TRUSTEE_IS_SID;
        ea[2].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
        ea[2].Trustee.ptstrName  = (LPTSTR) pAdminSID;

        //Create a new ACL with the three ACEs.
        if (ERROR_SUCCESS != SetEntriesInAcl(NUM_ACES, 
            ea, 
            NULL, 
            &pACL)) 
            throw GetLastError();

        //Initialize a security descriptor.  
        pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, 
            SECURITY_DESCRIPTOR_MIN_ LENGTH); 
        if (pSD == NULL) 
            throw GetLastError();

        if (!InitializeSecurityDescriptor(pSD, 
            SECURITY_DESCRIPTOR_REVISION))   
            throw GetLastError(); 

        //Add the ACL to the security descriptor. 
        if (!SetSecurityDescriptorDacl(pSD, 
            TRUE,     //fDaclPresent flag   
            pACL, 
            FALSE)) {  
                throw GetLastError(); 
            } else {
                SECURITY_ATTRIBUTES sa;
                sa.nLength = sizeof(SECURITY_ATTRIBUTES);
                sa.bInheritHandle = FALSE;
                sa.lpSecurityDescriptor = pSD;

                if (!CreateDirectory("C:\\Program Files\\MyStuf f", &sa)) 
                    throw GetLastError();
            } //End try
    } catch(...) {
        //Error condition
    }

    if (pSD) 
        LocalFree(pSD);

    if (pACL)
        LocalFree(pACL);

    //Call FreeSID for each SID allocated by AllocateAndInit ializeSID.
    if (pEveryoneSID) 
        FreeSid(pEveryoneSID);

    if (pNetworkSID)
        FreeSid(pNetworkSID);

    if (pAdminSID) 
        FreeSid(pAdminSID);
}
