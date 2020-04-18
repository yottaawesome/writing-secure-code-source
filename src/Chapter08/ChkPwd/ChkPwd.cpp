///////////////////////////////////////////////////////////////
// CHKPWD
//
// *NOTE* 
// This code will ONLY compile and 
// run on a Windows .NET Server 2003 computer
// that has a version of Platform SDK 
// dated later than Aug02
///////////////////////////////////////////////////////////////

#include "stdafx.h"

LPTSTR GetPasswordStatus(NET_API_STATUS valstat) {
	TCHAR *szStat = NULL;
	switch(valstat) {
		case NERR_PasswordTooShort : 
			szStat = _T("Too short"); break;
		case NERR_PasswordTooLong  :
			szStat = _T("Too long"); break;
		case NERR_PasswordNotComplexEnough :
			szStat = _T("Not complex enough"); break;
		case NERR_PasswordFilterError :
			szStat = _T("Filter Error"); break;
		case NERR_Success :
			szStat = _T("OK!"); break;
		case NERR_BadPassword :
			szStat = _T("Bad password data"); break;
		default :
			szStat = _T("Dunno!"); break;
	}

	return szStat;
}

NET_API_STATUS CheckPassword(LPWSTR szPwd) {

	if (szPwd == NULL) return false;

	NET_VALIDATE_PASSWORD_RESET_INPUT_ARG  CheckPwIn;
	NET_VALIDATE_OUTPUT_ARG  *pCheckPwOut  = NULL;
	ZeroMemory(&CheckPwIn,sizeof(CheckPwIn));
	CheckPwIn.ClearPassword = szPwd;

	NET_API_STATUS stat = NetValidatePasswordPolicy(
										NULL,NULL,
										NetValidatePasswordReset,
										&CheckPwIn,
										(LPVOID*)&pCheckPwOut);

	NET_API_STATUS pwdOK = pCheckPwOut->ValidationStatus;
	NetValidatePasswordPolicyFree((LPVOID*)&pCheckPwOut);

	return pwdOK;
}

int _tmain(int argc, _TCHAR* argv[])
{
	WCHAR *pwd[] = {L"fred", L"jahsd72hk!jdx:", L"Smitthy!"};
	for (int i=0 ; i < sizeof(pwd)/sizeof(pwd[0]); i++) {
		NET_API_STATUS s = CheckPassword(pwd[i]);
		LPTSTR szStat = GetPasswordStatus(s);
		printf("'%S' is %s\n",pwd[i],szStat);
	}

	return 0;
}
