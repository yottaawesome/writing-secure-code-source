// InternetCrackURL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

BOOL IsValidDomain(char *szURL, char *szValidDomain, 
                   BOOL fRequireHTTPS) {
	URL_COMPONENTS urlComp;
	ZeroMemory(&urlComp, sizeof(urlComp));
	urlComp.dwStructSize = sizeof(urlComp);

	// Only interested in the hostname
	char szHostName[128];
	urlComp.lpszHostName = szHostName;
	urlComp.dwHostNameLength = sizeof(szHostName);

	BOOL fRet = InternetCrackUrl(szURL, 0, 0, &urlComp);

	if (fRet==FALSE) {
		printf("InternetCrackURL failed -> %d", GetLastError());
		return FALSE;
	}

        // Check for HTTPS if HTTPS is required.
	if (fRequireHTTPS && urlComp.nScheme != INTERNET_SCHEME_HTTPS)
		return FALSE;


	// Quick 'n' dirty right-side case sensitive search
	int cbHostName = lstrlen(urlComp.lpszHostName);
	int cbValid = lstrlen(szValidDomain);
	int cbSize = (cbHostName > cbValid) ? cbValid : cbHostName;
	for (int i=1; i <= cbSize; i++) 
		if (urlComp.lpszHostName[cbHostName - i] != szValidDomain[cbValid - i])
			return FALSE;

	return TRUE;					
}

void main() {
	char *szURL="https://www.northwindtraders.com/foo/default.html";
	char *szValidDomain = "northwindtraders.com";
	BOOL fRequireHTTPS = TRUE;

	if (IsValidDomain(szURL, szValidDomain, TRUE)) {
		printf("Cool, %s is in a valid domain.", szURL);
	}
}
