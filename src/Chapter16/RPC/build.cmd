@rem Build the sample RPC app 

@echo off
cls
set ccflags=-DWINVER=0x0500 -W3 -D_WINNT -D_WIN32_WINNT=0x0500 -Od -DDEBUG -D_DEBUG
midl -robust phone.idl

cl -c %ccflags% phonec.cpp 
cl -c %ccflags% phone_c.c
cl -c %ccflags% phones.cpp
cl -c %ccflags% phone_s.c
	
link -out:phonec.exe phonec.obj phone_c.obj rpcrt4.lib Ntdsapi.lib
link -out:phones.exe phones.obj phone_s.obj rpcrt4.lib advapi32.lib