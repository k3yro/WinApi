#include <windows.h>

#define BUTTONOK 1
#define EDITUSR 2
#define EDITPW 3

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int DisplayResourceNAMessageBox();

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hPrI, PSTR szCmdLine, int iCmdShow)
{
	LPCWSTR szName = L"Fensterklasse";
	HBRUSH MyBrush = CreateSolidBrush(RGB(230, 230, 230));
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hI;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = 0;
	wc.hbrBackground = MyBrush;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szName;

	RegisterClass(&wc);

	HWND hwnd = CreateWindow(szName, L"App - Login", WS_SYSMENU | WS_MINIMIZEBOX,
		500/*Todo: Berechnen*/, 400, 380, 200, NULL, NULL, hI, NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//-----------------------------------------------------------------------------------

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
//-----------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND hwndButtonOk, hwndEditUsr, hwndEditPw;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkColor(hdc, RGB(230, 230, 230));
		TextOut(hdc, 20, 33, L"Username:", 9);
		TextOut(hdc, 20, 63, L"Password:", 9);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_CREATE:
		hwndButtonOk = CreateWindow(L"button", L"Ok",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			100, 100, 80, 25, hwnd, (HMENU)BUTTONOK,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

		hwndEditUsr = CreateWindow(L"combobox", L"",
			WS_CHILD | WS_VISIBLE,
			100, 30, 200, 20, hwnd, (HMENU)EDITUSR,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

		hwndEditPw = CreateWindow(L"combobox", L"sdfsdf",
			WS_CHILD | WS_VISIBLE,
			100, 60, 200, 20, hwnd, (HMENU)EDITPW,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case BUTTONOK:
			MessageBox(
				NULL,
				(LPCWSTR)L"Wrong Login!\nPlease try again!",
				(LPCWSTR)L"Account Details",
				MB_ICONERROR
			);

			//SetWindowText(hwndEditUsr, L"");
			//SendMessage(hwndEditUsr, EM_SETREADONLY, TRUE, 0);
			break;
		case EDITUSR:
			SendMessage(hwndEditUsr, EM_SETREADONLY, FALSE, 0);
			break;
		case EDITPW:
			SendMessage(hwndEditUsr, EM_SETREADONLY, FALSE, 0);
			break;
		}

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}