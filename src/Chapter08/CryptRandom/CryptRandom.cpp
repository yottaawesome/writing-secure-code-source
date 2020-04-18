/*
CryptRandom.cpp
*/

#include <windows.h>
#include <wincrypt.h>
#include <iostream.h>

class CCryptRandom {
public:
    CCryptRandom();
    virtual ~CCryptRandom();
    BOOL get(void *lpGoop, DWORD cbGoop);

private:
    HCRYPTPROV m_hProv;
};

CCryptRandom::CCryptRandom() {
    m_hProv = NULL;
    CryptAcquireContext(&m_hProv,
                        NULL, NULL,
                        PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
    if (m_hProv == NULL) 
        throw GetLastError();
}

CCryptRandom::~CCryptRandom() {
    if (m_hProv) CryptReleaseContext(m_hProv, 0);
}

BOOL CCryptRandom::get(void *lpGoop, DWORD cbGoop) {
    if (!m_hProv) return FALSE;
    return CryptGenRandom(m_hProv, cbGoop,
                          reinterpret_cast<LPBYTE>(lpGoop));
}

void main() {
    try {
        CCryptRandom r;
    
        // Generate 10 random numbers between 0 and 99.
        for (int i=0; i<10; i++) {
            DWORD d;
            if (r.get(&d, sizeof d))
                cout << d % 100 << endl;
        }
    } catch (DWORD dwErr) {
        // exception handling
    }
}
