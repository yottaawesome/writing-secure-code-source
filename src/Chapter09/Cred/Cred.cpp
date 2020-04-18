#include "stdafx.h"

void main(void) {
	CREDUI_INFO cui;
    	cui.cbSize = sizeof CREDUI_INFO;
	cui.hwndParent = NULL;
	cui.pszMessageText = 
    	    TEXT("Please Enter your Northwind Traders Accounts password.");
	cui.pszCaptionText = TEXT("Northwind Traders Accounts");
	cui.hbmBanner = NULL;

	PCTSTR pszTargetName = TEXT("NorthwindAccountsServer"); 
	DWORD  dwErrReason = 0;
	char   pszName[CREDUI_MAX_USERNAME_LENGTH+1];
	char   pszPwd[CREDUI_MAX_PASSWORD_LENGTH+1];
	DWORD  dwName = CREDUI_MAX_USERNAME_LENGTH; 
	DWORD  dwPwd = CREDUI_MAX_PASSWORD_LENGTH; 
	BOOL   fSave = FALSE;
	DWORD  dwFlags = 
            CREDUI_FLAGS_GENERIC_CREDENTIALS | 
            CREDUI_FLAGS_ALWAYS_SHOW_UI;

	// Zero out username and password as they are [in,out] parameters.
	ZeroMemory(pszName, dwName);
	ZeroMemory(pszPwd, dwPwd);
   
	DWORD err = CredUIPromptForCredentials(
               &cui,
               pszTargetName,
               NULL,
               dwErrReason,
               pszName,dwName,
               pszPwd,dwPwd,
               &fSave,
               dwFlags);

	if (err) 
	    printf("CredUIPromptForCredentials() failed -> %d",
        	   GetLastError());
	else {
	    // Access the Northwind Traders Accounting package using
	    // pszName and pszPwd over a secure channel.
	}

}

