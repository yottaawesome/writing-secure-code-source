
DCOM_Securityps.dll: dlldata.obj DCOM_Security_p.obj DCOM_Security_i.obj
	link /dll /out:DCOM_Securityps.dll /def:DCOM_Securityps.def /entry:DllMain dlldata.obj DCOM_Security_p.obj DCOM_Security_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del DCOM_Securityps.dll
	@del DCOM_Securityps.lib
	@del DCOM_Securityps.exp
	@del dlldata.obj
	@del DCOM_Security_p.obj
	@del DCOM_Security_i.obj
