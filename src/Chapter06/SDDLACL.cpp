/*
SDDLACL
*/

#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <sddl.h>

void main() {
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = FALSE;
	char *szSD = "D:P"                      // DACL
		"(D;OICI;GA;;;BG)"         // Deny Guests
		"(A;OICI;GA;;;SY)"         // Allow SYSTEM Full Control
		"(A;OICI;GA;;;BA)"         // Allow Admins Full Control
		"(A;OICI;GRGWGX;;;IU)";    // Allow Interactive Users RWX

	if (ConvertStringSecurityDescriptorToSecurityDescriptor(
		szSD,
		SDDL_REVISION_1, 
		&(sa.lpSecurityDescriptor), 
		NULL)) {

			if (!CreateDirectory("C:\\MyDir", &sa )) {
				DWORD err = GetLastError();
			}

			LocalFree(sa.lpSecurityDescriptor);
		} 
}
