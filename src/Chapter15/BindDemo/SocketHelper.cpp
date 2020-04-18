#include <winsock2.h>
#include <stdio.h>
#include <assert.h>

//this pragma keep you from having to alter the default project
// especially useful when dealing with libraries and classes
#pragma comment(lib, "ws2_32.lib")
/*
This function initializes Winsock.

*/
bool InitWinsock(void)
{
	WORD VersionRequested;
	WSADATA WsaData;
	int ret;

	//We're asking for version 2.2.
	//Should run on Windows NT 4.0, Windows 2000 and later.
	VersionRequested = MAKEWORD( 2, 2 );
 
	ret = WSAStartup(VersionRequested, &WsaData);

	if(ret == ERROR_SUCCESS)
	{
		//Not enough; just to check for success.
		//Did we get the version we asked for?
		if(LOBYTE(WsaData.wVersion) == 2 &&
			HIBYTE(WsaData.wVersion) == 2)
		{
			return true;
		}
		else
		{
			//Note - high byte is minor version;
			//low byte is major version.
			printf("Winsock 2.2 not available\n");
			printf("Winsock %d.%d is highest available\n", 
				    LOBYTE(WsaData.wHighVersion),
					HIBYTE(WsaData.wHighVersion));

			return false;
		}
	}
	else
	{
		printf("Cannot initialize Winsock - err = %d\n", ret);
		return false;
	}
}

/*
Initializes a sockaddr_in struct for use with bind, connect, and friends
Usage - 
If you don't need to specify a port - for example, binding a UDP client
or binding a socket that isn't UDP or TCP, use port = 0

If a specific IP address isn't required - for example, binding a server
to all available IP addresses specify IpStr = "0.0.0.0" 
This will cause inet_ntoa to return INADDR_ANY

*/

bool InitSockAddr(sockaddr_in* pSa, const char* IpStr, unsigned short port)
{
	unsigned long addr;

	// ALWAYS check your inputs
	// assume the world outside your function is bent on your destruction!
	// this is a cool construct - you're protected for both release and debug code

	// Note - inet_addr doesn't return an error if fed a NULL pointer
	// it will return 0, which is otherwise known as INADDR_ANY
	// this little-known fact caused large amounts of mayhem one day
	// and resulted in finding a new denial of service attack
	if(pSa == NULL || IpStr == NULL)
	{
		assert(false);
		return false;
	}

	addr = inet_addr(IpStr);

	if(addr == ~0)
	{
		printf("Bad IP string %s\n", IpStr);
		return false;
	}

	pSa->sin_family = AF_INET;
	pSa->sin_addr.S_un.S_addr = addr;
	pSa->sin_port = htons(port);
	return true;
}
