#include <winsock2.h>
#include <assert.h>
#include <stdio.h>
#include "SocketHelper.h"

int main(int argc, char* argv[])
{
	sockaddr_in addr;
	SOCKET sock;
    DWORD now;

	if(!InitWinsock())
	{
		printf("Cannot initialize Winsock\n");
		return -1;
	}

	if(!InitSockAddr(&addr, "192.168.0.1", 8765))
	{
		printf("Error setting sockaddr\n");
		return -1;
	}

	//now let's create the socket and bind it
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(sock == INVALID_SOCKET)
	{
			printf("Cannot create socket - err = %d\n", GetLastError());
			return -1;
	}

        now = GetTickCount();
	if(connect(sock, (sockaddr*)&addr, sizeof(sockaddr_in)) != 0)
        {
          printf("Connection failed - err = %d\n", GetLastError());
        }
        printf("Elapsed time = %d\n", GetTickCount() - now);

	closesocket(sock);
	
	return 0;
}
