#include <windows.h>
#include <tchar.h>
#include <stdio.h>

const TCHAR* szFensterTitel = TEXT("Titel");
int CDECL paramAlert(TCHAR*, ...);
int CDECL alert(TCHAR*);

int WINAPI WinMain(HINSTANCE hI, HINSTANCE old, PSTR szCmdLine, int iCmdShow)
{
    int screenXMax = 0, screenYMax = 0;

    screenXMax = GetSystemMetrics(SM_CXSCREEN);
    screenYMax = GetSystemMetrics(SM_CYSCREEN);

    paramAlert(TEXT("nachricht %i x %i"), screenXMax, screenYMax);
    alert(TEXT("Hello alert"));
    return 0;
}

int CDECL paramAlert(TCHAR *szNachricht, ...)
{
    TCHAR szBuffer[512];
    va_list param;

    //va_start(param, szNachricht); // oder ohne Makro:
    param = (char*) &szNachricht + sizeof (szNachricht);

    //_vsntprintf(szBuffer, sizeof (szBuffer) / sizeof (TCHAR), szNachricht, param);
    wvsprintf(szBuffer, szNachricht, param);

    //va_end(param); // oder ohne Makro:
    param = NULL;

    return MessageBox(NULL, szBuffer, szFensterTitel, 0);
}

//TODO: Parametertyp egal
int CDECL alert(TCHAR* szNachricht)
{
    TCHAR szBuffer[512];
    wsprintf(szBuffer, szNachricht);
    return MessageBox(NULL, szBuffer, szFensterTitel, 0);
}
