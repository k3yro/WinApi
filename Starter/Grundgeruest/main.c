#include <windows.h>

LRESULT CALLBACK WindowProzedur(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hI, HINSTANCE useless, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR    szAnwendungsName[] = TEXT("Grundgerüst");
    HWND            windowHandle;
    MSG             nachricht;
    WNDCLASS        fensterKlasse;

    fensterKlasse.style         = CS_HREDRAW | CS_VREDRAW;
    fensterKlasse.lpfnWndProc   = WindowProzedur;
    fensterKlasse.cbClsExtra    = 0;
    fensterKlasse.cbWndExtra    = 0;
    fensterKlasse.hInstance     = hI;
    fensterKlasse.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    fensterKlasse.hCursor       = LoadCursor(NULL, IDC_ARROW);
    fensterKlasse.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    fensterKlasse.lpszMenuName  = NULL;
    fensterKlasse.lpszClassName = szAnwendungsName;

    if (!RegisterClass(&fensterKlasse))
    {
        MessageBox(NULL, TEXT("Anwendungsfehler! (Unicode?)"), szAnwendungsName, MB_ICONERROR);
        return 0;
    }

    windowHandle = CreateWindow(szAnwendungsName,       // Name der Fensterklasse
                                TEXT("Grundgerüst"),    // Fenstertitel
                                WS_OVERLAPPEDWINDOW,    // Fensterstil
                                CW_USEDEFAULT,          // X-Position des Fensters
                                CW_USEDEFAULT,          // YPosition des Fensters
                                CW_USEDEFAULT,          // Fensterbreite
                                CW_USEDEFAULT,          // Fensterhöhe
                                NULL,                   // übergeordnetes Fenster
                                NULL,                   // Menü
                                hI,                     // Programm-Kopiezähler (Programm-ID
                                NULL);                  // zusätzliche Parameter

    ShowWindow(windowHandle, iCmdShow);
    UpdateWindow(windowHandle);

    while (GetMessage(&nachricht, NULL, 0, 0))
    {
        TranslateMessage(&nachricht);
        DispatchMessage(&nachricht);
    }
    return nachricht.wParam;
}

LRESULT CALLBACK WindowProzedur(HWND windowsHandle, UINT nachricht, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    switch (nachricht) {
    case WM_CREATE:
       // PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(windowsHandle, &ps);

        GetClientRect(windowsHandle, &rect);

        DrawText(hdc, TEXT("WinApi Grundgerüst"), -1, &rect,
                 DT_SINGLELINE| DT_CENTER | DT_VCENTER);

        EndPaint(windowsHandle, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(windowsHandle, nachricht, wParam, lParam);
}
