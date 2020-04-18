// CanonUser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void main() {

	for (int i = NameUnknown ; 
	 	i <= NameServicePrincipal; 
	 	i++) {

		TCHAR szName[256];
		DWORD dwLen = sizeof szName / sizeof TCHAR;

		TCHAR *enf;
		switch(i) {
			case 0 : enf = "NameUnknown"; break;
			case 1 : enf = "NameFullyQualifiedDN"; break;
			case 2 : enf = "NameSamCompatible"; break;
			case 3 : enf = "NameDisplay"; break;
			case 4 : enf = "NameUniqueId"; break;
			case 5 : enf = "NameCanonical"; break;
			case 6 : enf = "NameUserPrincipal"; break;
			case 7 : enf = "NameUserPrincipal"; break;
			case 8 : enf = "NameServicePrincipal "; break;
                        default: enf = "Unknown"; break;
		}

		BOOL fRet =
			GetUserNameEx((EXTENDED_NAME_FORMAT)i,
					  szName,
					  &dwLen);

		if (fRet) {
			printf("%s in '%s' format.\n",szName,enf);
		} else {
			printf("%s failed %d\n", enf, GetLastError());
		}
	}
}

