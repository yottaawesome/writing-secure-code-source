// CanonServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void main() {

	for (int i = ComputerNameNetBIOS; 
	 	i <= ComputerNamePhysicalDnsFullyQualified; 
	 	i++) {

		TCHAR szName[256];
		DWORD dwLen = sizeof szName / sizeof TCHAR;

		TCHAR *cnf;
		switch(i) {
			case 0 : cnf = "ComputerNameNetBIOS"; break;
			case 1 : cnf = "ComputerNameDnsHostname"; break;
			case 2 : cnf = "ComputerNameDnsDomain"; break;
			case 3 : cnf = "ComputerNameDnsFullyQualified"; break;
			case 4 : cnf = "ComputerNamePhysicalNetBIOS"; break;
			case 5 : cnf = "ComputerNamePhysicalDnsHostname"; break;
			case 6 : cnf = "ComputerNamePhysicalDnsDomain"; break;
			case 7 : cnf = "ComputerNamePhysicalDnsFullyQualified"; break;
                        default: cnf = "Unknown"; break;
		}

		BOOL fRet =
			GetComputerNameEx((COMPUTER_NAME_FORMAT)i,
					  szName,
					  &dwLen);

		if (fRet) {
			printf("%s in '%s' format.\n", szName, cnf);
		} else {
			printf("Failed %d", GetLastError());
		}
	}
}

