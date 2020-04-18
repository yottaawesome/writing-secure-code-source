/*
ATLACL.cpp 
*/

#include <atlsecurity.h>
#include <iostream>

using namespace std;

void main(){

	try {
		//The user accounts
		CSid sidBlake("Northwindtraders\\blake");
		CSid sidAdmin = Sids::Admins();
		CSid sidGuests = Sids::Guests();

		//Create the ACL, and populate with ACEs.
		//Note the deny ACE is placed before the allow ACEs.
		CDacl dacl;
		dacl.AddDeniedAce(sidGuests, GENERIC_ALL);
		dacl.AddAllowedAce(sidBlake, GENERIC_READ);
		dacl.AddAllowedAce(sidAdmin, GENERIC_ALL);

		//Create the security descriptor and attributes.
		CSecurityDesc sd;
		sd.SetDacl(dacl);
		CSecurityAttributes sa(sd);

		//Create the directory with the security attributes.
		if (CreateDirectory("c:\\MyTestDir", &sa))
			cout << "Directory created!" << endl;

	} catch(CAtlException e) {
		cerr << "Error, application failed with error " 
			<< hex << (HRESULT)e << endl;
	}
}
