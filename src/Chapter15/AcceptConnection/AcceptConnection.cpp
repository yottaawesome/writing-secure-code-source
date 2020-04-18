/*
AcceptConnection.cpp
Demonstrates connection options
*/

#include <winsock2.h>
#include <assert.h>
#include <stdio.h>
#include "SocketHelper.h"

const char* MyIpAddr = "192.168.0.1";

void OldStyleListen(SOCKET sock)
{
	//Now we're bound. Let's listen on the port.
        //Use this as a connection counter.

	int conns = 0;

	while(1)
	{
		//Use maximum backlog allowed.
		if(listen(sock, SOMAXCONN) == 0)
		{
			SOCKET sock2;
			sockaddr_in from;
			int size;

			//Someone tried to connect - call accept to find out who.
			conns++;

			size = sizeof(sockaddr_in);
			sock2 = accept(sock, (sockaddr*)&from, &size);

			if(sock2 == INVALID_SOCKET)
			{
				printf("Error accepting connection - %d\n", 
                                       GetLastError());
			}
			else
			{
				//NOTE - in the real world, we'd probably want to hand this 
				//socket off to a worker thread.

				printf("Accepted connection from %s\n",
                                        inet_ntoa(from.sin_addr));
				//Now decide what to do with the connection;
                                //really lame decision criteria - we'll just take
                                //every other one.

				if(conns % 2 == 0)
				{
					printf("We like this client.\n");
					//Pretend to do some processing here.
				}
				else
				{
					printf("Go away!\n");
				}
				closesocket(sock2);
			}
		}
		else
		{
			//error
			printf("Listen failed - err = %d\n", GetLastError());
			break;
		}

		//Insert your own code here to decide when to shut down the server.
		if(conns > 10)
		{
			break;
		}
	}
}

int CALLBACK AcceptCondition(
  IN LPWSABUF lpCallerId,
  IN LPWSABUF lpCallerData,
  IN OUT LPQOS lpSQOS,
  IN OUT LPQOS lpGQOS,
  IN LPWSABUF lpCalleeId,
  OUT LPWSABUF lpCalleeData,
  OUT GROUP FAR *g,
  IN DWORD dwCallbackData
)
{
	sockaddr_in* pCaller;
	sockaddr_in* pCallee;

	pCaller = (sockaddr_in*)lpCallerId->buf;
	pCallee = (sockaddr_in*)lpCalleeId->buf;

	printf("Attempted connection from %s\n", inet_ntoa(pCaller->sin_addr));

	//If you need this to work under Windows 98, see Q193919.
	if(lpSQOS != NULL)
	{
		//You could negotiate QOS here.
	}

	//Now decide what to return. 
	//Let's not take connections from ourselves.
	if(pCaller->sin_addr.S_un.S_addr == inet_addr(MyIpAddr))
	{
		return CF_REJECT;
	}
	else
	{
		return CF_ACCEPT;
	}

	//Note that we could also return CF_DEFER. 
	//This function needs to run in the same thread as the caller.
	//A possible use for this would be to do a DNS lookup on the caller
	//then try again once we know who they are.

}

void NewStyleListen(SOCKET sock)
{
	//Now we're bound. Let's listen on the port;
	//use this as a connection counter.
	int conns = 0;

	//First, set an option.
	BOOL val = TRUE;
	
	if(setsockopt(sock, 
				  SOL_SOCKET, 
				  SO_CONDITIONAL_ACCEPT, 
				  (const char*)&val, sizeof(val)) != 0)
	{
		printf("Cannot set SO_CONDITIONAL_ACCEPT - err = %d\n", GetLastError());
		return;
	}

	while(1)
	{
		//Use maximum backlog allowed.
		if(listen(sock, SOMAXCONN) == 0)
		{
			SOCKET sock2;
			sockaddr_in from;
			int size;

			//Someone tried to connect - call accept to find out who.
			conns++;

			size = sizeof(sockaddr_in);

			//This is where things get different.
			sock2 = WSAAccept(sock,
				              (sockaddr*)&from,
							  &size,
							  AcceptCondition,
							  conns); //Use conns as extra callback data.

			if(sock2 == INVALID_SOCKET)
			{
				printf("Error accepting connection - %d\n", GetLastError());
			}
			else
			{
				//NOTE - in the real world, we'd probably want to hand this 
				//socket off to a worker thread.

				printf("Accepted connection from %s\n", inet_ntoa(from.sin_addr));
				//Pretend to do some processing here.
				closesocket(sock2);
			}
		}
		else
		{
			//Error
			printf("Listen failed - err = %d\n", GetLastError());
			break;
		}

		//Insert your own code here to decide when to shut down the server.
		if(conns > 10)
		{
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	sockaddr_in addr;
	SOCKET sock;

	if(!InitWinsock())
	{
		printf("Cannot initialize Winsock\n");
		return -1;
	}

	//Use some semi-random port that shouldn't be in use.
	if(!InitSockAddr(&addr, "0.0.0.0", 8765))
	{
		printf("Error setting sockaddr\n");
		return -1;
	}

	//Now let's create the socket and bind it.
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(sock == INVALID_SOCKET)
	{
			printf("Cannot create socket - err = %d\n", GetLastError());
			return -1;
	}

	if(bind(sock, (sockaddr*)&addr, sizeof(sockaddr_in)) == 0)
	{
			printf("Socket bound\n", argv[1]);
	}
	else
	{
			printf("Cannot bind socket - err = %d\n", GetLastError());
			closesocket(sock);
			return -1;
	}

	//Comment out one or the other of these
	//OldStyleListen(sock);
	NewStyleListen(sock);

	closesocket(sock);
	
	return 0;
}