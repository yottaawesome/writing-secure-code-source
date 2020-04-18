/*
   JettisonPrivs.cpp
*/

#ifndef SE_PRIVILEGE_REMOVED
#	define SE_PRIVILEGE_REMOVED (0x00000004)
#endif

#define SAME_LUID(luid1,luid2) \
	(luid1.LowPart == luid2.LowPart && \
	luid1.HighPart == luid2.HighPart)

DWORD JettisonPrivs() {
	DWORD  dwError = 0;
	VOID*  TokenInfo = NULL;

	try {
		HANDLE hToken = NULL;
		if (!OpenProcessToken(
			GetCurrentProcess(),
			TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,
			&hToken)) 
			throw GetLastError();

		DWORD dwSize=0;
		if (!GetTokenInformation(
			hToken,
			TokenPrivileges,
			NULL, 0,
			&dwSize)) {

				dwError = GetLastError();
				if (dwError != ERROR_INSUFFICIENT_BUFFER)
					throw dwError;
			}

			TokenInfo = new char[dwSize];

			if (NULL == TokenInfo)
				throw ERROR_NOT_ENOUGH_MEMORY;

			if (!GetTokenInformation(
				hToken,
				TokenPrivileges,
				TokenInfo, dwSize,
				&dwSize))
				throw GetLastError();

			TOKEN_PRIVILEGES* pTokenPrivs = (TOKEN_PRIVILEGES*) TokenInfo;

			// don't remove this priv
			LUID luidChangeNotify;
			LookupPrivilegeValue(NULL,SE_CHANGE_NOTIFY_NAME,&luidChangeNotify);

			for (DWORD dwIndex = 0; dwIndex < pTokenPrivs->PrivilegeCount; dwIndex++)
				if (!SAME_LUID(pTokenPrivs->Privileges[dwIndex].Luid, luidChangeNotify)) 
					pTokenPrivs->Privileges[dwIndex].Attributes = SE_PRIVILEGE_REMOVED;

			if (!AdjustTokenPrivileges(
				hToken,
				FALSE,
				pTokenPrivs, dwSize,
				NULL, NULL))
				throw GetLastError();
	} catch (DWORD err) {
		dwError = err;
	}

	if (TokenInfo) 
		delete [] TokenInfo;

	return dwError;
}
