#include "stdafx.h"
#include "atlrx.h"

enum errCanon {
    ERR_CANON_NO_ERROR = 0,
    ERR_CANON_INVALID_FILENAME,
    ERR_CANON_NOT_A_FILE,
    ERR_CANON_NO_SUCH_FILE,
    ERR_CANON_TOO_BIG,
    ERR_CANON_NO_MEM};

errCanon GetCanonicalFileName(_TCHAR *szFilename, 
                              _TCHAR *szDir,
                              _TCHAR **pszNewFilename) {

    *pszNewFilename = NULL;
    _TCHAR *pTempFullDir = NULL;
    HANDLE hFile = NULL;

    errCanon err = ERR_CANON_NO_ERROR;

    try {
        // STEP 2 
        // Check that filename is valid (alphanum '.' 0-4 alphanums)
        // Case insensitive
        CAtlRegExp<> reFilename;
        reFilename.Parse("^\\a+\\.\\a?\\a?\\a?\\a?$", FALSE);
        CAtlREMatchContext<> mc;
        if (!reFilename.Match(szFilename, &mc))
            throw ERR_CANON_INVALID_FILENAME;

        DWORD cbFilename = lstrlen(szFilename);
        DWORD cbDir = lstrlen(szDir);

        // Temp new buffer size, allow for added '\'.
        DWORD cbNewFilename = cbFilename + cbDir + 1;

        // STEP 3
        // Make sure filesize is small enough.
        if (cbNewFilename > MAX_PATH)
            throw ERR_CANON_TOO_BIG;

        // Allocate memory for the new filename.
        // Accomodate for trailing '\0'.
        _TCHAR *pTempFullDir = new _TCHAR[cbNewFilename + 1];
        if (pTempFullDir == NULL)
            throw ERR_CANON_NO_MEM;
      
        // STEP 4 
        // Join the dir and the filename together. 
        _sntprintf(pTempFullDir,
                   cbNewFilename,
                   _T("%s\\%s"),
                   szDir,
                   szFilename);
        pTempFullDir[cbNewFilename] = '\0';

        // STEP 5 
        // Get the full path, 
        // Accommodates for .. and trailing '.' and spaces
        LPTSTR pFilename;
        _TCHAR pFullPathName[MAX_PATH + 1];

        DWORD dwFullPathLen = 
            GetFullPathName(pTempFullDir,
                            MAX_PATH,
                            pFullPathName,
                            &pFilename);
        if (dwFullPathLen > MAX_PATH)
            throw ERR_CANON_NO_MEM;

        // STEP 6 
        // Get the long filename.
        GetLongPathName(pFullPathName, pFullPathName, MAX_PATH);
      
        // STEP 7
        // Is this a file or a device?
        HANDLE hFile = CreateFile(pFullPathName,
                                  0, 0, NULL,
                                  OPEN_EXISTING,
                                  0, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
            throw ERR_CANON_NO_SUCH_FILE;
           
        if (GetFileType(hFile) != FILE_TYPE_DISK)
            throw ERR_CANON_NOT_A_FILE;
      
        // Looks good!
        // Caller must call delete [] pszNewFilename.
        *pszNewFilename = new _TCHAR[lstrlen(pFullPathName) + 1];
        if (*pszNewFilename != NULL)
            lstrcpy(*pszNewFilename, pFullPathName);
        else
            err = ERR_CANON_NO_MEM;

    } catch(errCanon e) {
        err = e;
    } 

    if (pTempFullDir)   delete [] pTempFullDir;
    CloseHandle(hFile);

    return err;
}


int _tmain(int argc, _TCHAR* argv[]) {
	errCanon err = ERR_CANON_NO_ERROR;

	if (argc > 1) {
		_TCHAR *pNewFilename = NULL;
		err = GetCanonicalFileName(argv[1],"c:\\temp",&pNewFilename);
		
		if (err == ERR_CANON_NO_ERROR) {
			printf("%s is valid\n",pNewFilename);
			delete [] pNewFilename;
		} else {
			printf("%s is invalid (%d)\n",argv[1],err);
		}
	}

	return err;
}

