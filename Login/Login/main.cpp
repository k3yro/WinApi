#include <windows.h>
#include <iostream>
#include <commctrl.h>

#define BUTTONOK 111
#define EDITUSER 222
#define EDITPWRD 333

LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

using namespace std;

int main()
{
	HINSTANCE hI = GetModuleHandle(0);
	LPCWSTR szName = L"LoginWindow";
	HBRUSH MyBrush = CreateSolidBrush(RGB(230, 230, 230));
	MSG msg;
	WNDCLASS wc;

	wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MessageHandler;
	wc.hInstance = hI;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hbrBackground = MyBrush;
	wc.lpszClassName = szName;

	RegisterClass(&wc);

	HWND hwnd = CreateWindow(szName, L"App - Login", WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
		500/*Todo: Berechnen*/, 400, 380, 400, NULL, NULL, hI, NULL);

	//-----------------------------------------------------------------------------------

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//-----------------------------------------------------------------------------------
}

LRESULT CALLBACK MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND hButtonOk, hEditUser, hEditPwrd, hMonthCal, hwndDP;
	char usernameBuffer[23];
	char passwordBuffer[23];

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
		hButtonOk = CreateWindow(L"button", L"Ok",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			100, 330, 80, 25, hwnd, (HMENU)BUTTONOK,
			(HINSTANCE)GetWindowLong(hwnd, -6), NULL);

		hEditUser = CreateWindow(L"combobox", L"",
			WS_CHILD | WS_VISIBLE,
			100, 30, 200, 20, hwnd, (HMENU)EDITUSER,
			(HINSTANCE)GetWindowLong(hwnd, -6), NULL);

		hEditPwrd = CreateWindow(L"combobox", L"",
			WS_CHILD | WS_VISIBLE,
			100, 60, 200, 20, hwnd, (HMENU)EDITPWRD,
			(HINSTANCE)GetWindowLong(hwnd, -6), NULL);
		
		hMonthCal = CreateWindow(MONTHCAL_CLASSW, L"",
			WS_BORDER | WS_CHILD | WS_VISIBLE | MCS_NOTODAYCIRCLE,
			100, 130, 200, 200, hwnd, (HMENU)2, NULL, NULL);

		hwndDP = CreateWindowEx(0, DATETIMEPICK_CLASS, TEXT("DateTime"),
			WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHOWNONE,
			100, 100, 200, 25, hwnd, (HMENU)3, NULL, NULL);

		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case BUTTONOK:
			//DTM_GETMONTHCAL
			GetWindowTextA(hEditUser, usernameBuffer, 23);
			GetWindowTextA(hEditPwrd, passwordBuffer, 23);
			cout << "Username: " << usernameBuffer << endl;
			cout << "Password: " << passwordBuffer << endl;
			//MessageBoxA(NULL, "Wrong Login!\nPlease try again!", "Account Details", MB_ICONERROR);
			break;
		case EDITUSER:
			SendMessage(hEditUser, EM_SETREADONLY, FALSE, 0);
			break;
		case EDITPWRD:
			SendMessage(hEditUser, EM_SETREADONLY, FALSE, 0);
			break;
		}

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}