/*This application takes a security template .inf file,
  substitutes a user-supplied directory for %newapp_install%
  and writes it to a custom .inf file that you can apply
  to the directory your user chose.
  */

#define UNICODE
#include <windows.h>
#include <stdio.h>

/* I really hate tracking all my code paths to make sure I
   don't leak handles, so I write lots of classes like this.
*/
class SmartHandle
{
public:
    SmartHandle()
    {
        Handle = INVALID_HANDLE_VALUE;
    }

    ~SmartHandle()
    {
        if(IsValid())
        {
            CloseHandle(Handle);
        }
    }

    bool IsValid(void)
    {
        if(Handle != INVALID_HANDLE_VALUE &&
            Handle != NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    HANDLE Handle;
};

/*
  Tired of having to convert arguments to UNICODE?
  Use wmain instead of main, and they'll be passed in as UNICODE.
*/

int wmain(int argc, WCHAR* argv[])
{
    SmartHandle hInput;
    SmartHandle hOutput;
    SmartHandle hMap;
    WCHAR* pFile;
    WCHAR* pTmp;
    WCHAR* pLast;
    DWORD filesize;
    DWORD dirlen;

    if(argc != 4)
    {
        wprintf(L"Usage is %s [input file]", argv[0]);
		wprintf(L"[output file][install directory]\n");
        return -1;
    }

    dirlen = wcslen(argv[3]);

    hInput.Handle = CreateFile(argv[1], 
                GENERIC_READ, 
                0,             //Don't share it.
                NULL,          //Don't change the security.
                OPEN_EXISTING, //Fail if it isn't present.
                FILE_ATTRIBUTE_NORMAL, //Just a normal file
                NULL);         //No template

    if(!hInput.IsValid())
    {
        wprintf(L"Cannot open %s\n", argv[1]);
        return -1;
    }

    DWORD highsize = 0;
    filesize = GetFileSize(hInput.Handle, &highsize);

    if(highsize != 0 || filesize == ~0)
    {
        //The file is bigger than 4GB - what kind of .inf file is this???
        wprintf(L"%s is too large to map or size not found\n", argv[1]);
        return -1;
    }

    /*same as before, except that you always create the file*/
    hOutput.Handle = CreateFile(argv[2],
                 GENERIC_WRITE,
                 0,
                 NULL,
                 CREATE_ALWAYS,
                 FILE_ATTRIBUTE_NORMAL,
                 NULL);

    if(!hOutput.IsValid())
    {
        wprintf(L"Cannot open %s\n", argv[2]);
        return -1;
    }

//Now we have the input and output files open, map a view of the 
//input file
    //memory mapped files are cool and make many tasks easier

    hMap.Handle = CreateFileMapping(hInput.Handle, //File we have open
                  NULL,          //No special security
                  PAGE_READONLY, //Read-only
                  0,             //Don't specify max size
                  0,             //or min - will be size of file.
                  NULL);         //We don't need a name.


    if(!hMap.IsValid())
    {
        wprintf(L"Cannot map %s\n", argv[1]);
        return -1;
    }

    //Start at the beginning of the file, and map the whole thing.
    pFile = (WCHAR*)MapViewOfFile(hMap.Handle, FILE_MAP_READ, 0, 0, 0);

    if(pFile == NULL)
    {
        wprintf(L"Cannot map view of %s\n", argv[1]);
        return -1;
    }

    //Now we've got a pointer to the whole file - 
    //let's look for the string we want.

    pTmp = pLast = pFile;
    DWORD subst_len = wcslen(L"%newapp_install%");

    while(1)
    {
        DWORD written, bytes_out;

        pTmp = wcsstr(pLast, L"%newapp_install%");

        if(pTmp != NULL)
        {
            //Found the string.
            //How many bytes to write?

            bytes_out = (pTmp - pLast) * sizeof(WCHAR);

            if(!WriteFile(hOutput.Handle, pLast, bytes_out, 
                &written, NULL) || bytes_out != written)
            {
                wprintf(L"Cannot write to %s\n", argv[2]);
                return -1;
            }

            //Now instead of %newapp_install%, print the actual dir
            if(!WriteFile(hOutput.Handle, argv[3], 
                dirlen * sizeof(WCHAR), &written, NULL) ||
                dirlen * sizeof(WCHAR) != written)
            {
                wprintf(L"Cannot write to %s\n", argv[2]);
                UnmapViewOfFile(pFile);
                return -1;
            }

            pTmp += subst_len;
            pLast = pTmp;
            }
        else
        {
            //Didn't find the string - write the rest of the file.
            bytes_out = (BYTE*)pFile + filesize - (BYTE*)pLast;

            if(!WriteFile(hOutput.Handle, pLast, bytes_out, 
                &written, NULL) || bytes_out != written)
            {
                wprintf(L"Cannot write to %s\n", argv[2]);
                UnmapViewOfFile(pFile);
                return -1;
            }
            else
            {
                //We're done.
                UnmapViewOfFile(pFile);
                break;
            }
        }
    }

    //All the rest of our handles close automatically.
    return 0;
}
