//include guard
#ifndef SOCKETHELPER_H
#define SOCKETHELPER_H

//if winsock2.h isn't included, complain
#ifndef _WINSOCK2API_
#error Winsock2.h must be included
#endif

/*
Why don't we just include it here, you ask?
Never, ever, ever put winsock2.h, winsock,h OR windows.h in a header
unless you're very sure nothing anywhere will include a different one

The reason for this is that if you first include winsock.h, it pulls in windows.h
and vice-versa. Winsock.h is guarded against someone first pulling in winsock2.h, so - 

#include <winsock2.h>
#include <windows.h> OR #include <winsock.h>

is redundant, but works just fine.

However, if you do it like so,
#include <windows.h>
#include <winsock2.h>

You get hundreds of compiler errors and no one is very happy. 
If the header that pulls in one of these is nested within other headers,
and you have a large project, then the problems can go on for days.
*/

/*
This function initializes Winsock to v2.2

*/
bool InitWinsock(void);

/*
Initializes a sockaddr_in struct for use with bind, connect, and friends
Usage - 
If you don't need to specify a port - for example, binding a UDP client
or binding a socket that isn't UDP or TCP, use port = 0

If a specific IP address isn't required - for example, binding a server
to all available IP addresses specify IpStr = "0.0.0.0" 
This will cause inet_ntoa to return INADDR_ANY

*/

bool InitSockAddr(sockaddr_in* pSa, const char* IpStr, unsigned short port);


#endif