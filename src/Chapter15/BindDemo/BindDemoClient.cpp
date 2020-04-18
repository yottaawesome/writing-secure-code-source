#include <winsock2.h>
#include <stdio.h>
#include <assert.h>
#include "SocketHelper.h"


/*
This application demonstrates a generic UDP-based server
*/

int main(int argc, char* argv[])
{
	SOCKET sock;
	sockaddr_in sin;

	if(argc != 2)
	{
		printf("Usage is %s [address of server]\n", argv[0]);
		return -1;
	}

	if(!InitWinsock())
		return -1;

	//create your socket
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if(sock == INVALID_SOCKET)
	{
		printf("Cannot create socket - err = %d\n", GetLastError());
		return -1;
	}

	//now let's bind the socket
	//first initialize the sockaddr_in
	//We're going to bind to INADDR_ANY, and let the OS choose our port
	if(!InitSockAddr(&sin, "0.0.0.0", 0))
	{
		printf("Can't initialize the sockaddr_in - doh!\n");
		closesocket(sock);
		return -1;
	}

	if(bind(sock, (sockaddr*)&sin, sizeof(sockaddr_in)) == 0)
	{
		printf("Socket bound to %s\n", argv[1]);
	}
	else
	{
		printf("Cannot bind socket - err = %d\n", GetLastError());
		closesocket(sock);
		return -1;
	}

	//Now let's send a message to our server.
	char* Msg = "Hey you!";

	if(!InitSockAddr(&sin, argv[1], 8391))
	{
		printf("Cannot initialize sockaddr from %s\n", argv[1]);
		closesocket(sock);
		return -1;
	}

	if(sendto(sock, Msg, strlen(Msg) + 1, 0, (sockaddr*)&sin, sizeof(sockaddr_in))
		== -1)
	{
		printf("Cannot send message - err = %d\n", GetLastError());
	}
	else
	{
		printf("Sent message to %s\n", argv[1]);
	}
	closesocket(sock);
	return 0;
}