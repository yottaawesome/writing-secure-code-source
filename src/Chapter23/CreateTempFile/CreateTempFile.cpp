#include <windows.h> 

HANDLE CreateTempFile(LPCTSTR szPrefix) {

   // Get temp dir.
   TCHAR szDir[MAX_PATH];
   if (GetTempPath(sizeof(szDir)/sizeof(TCHAR), szDir) == 0)
       return NULL;

   // Create unique temp file in temp dir.
   TCHAR szFileName[MAX_PATH];
   if (!GetTempFileName(szDir, szPrefix, 0, szFileName))
       return NULL;

   // Open temp file.
   HANDLE hTemp = CreateFile(szFileName,
                        GENERIC_READ | GENERIC_WRITE,
                        0,      // Don't share.
                        NULL,   // Default security descriptor
                        CREATE_ALWAYS,   
                        FILE_ATTRIBUTE_NOT_CONTENT_INDEXED | 
                        FILE_ATTRIBUTE_TEMPORARY | 
                        FILE_FLAG_DELETE_ON_CLOSE,
                        NULL);

   return hTemp == INVALID_HANDLE_VALUE 
                   ? NULL 
                   : hTemp;
}

int main() {
    BOOL fRet = FALSE;
    HANDLE h = CreateTempFile(TEXT("tmp"));
    if (h) {
      
        //
        // Do stuff with temp file.
        //

        CloseHandle(h);
    }
    return 0;
}
