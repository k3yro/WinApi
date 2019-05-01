#include <windows.h>
#include <iostream>
#include <fstream>

#define BUTTONOK 111
#define EDITUSER 222
#define EDITPWRD 333

#define ID_NEW   101
#define ID_LOAD  102
#define ID_SAVE  103
#define ID_CLOSE 104

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
		500/*Todo: Berechnen*/, 400, 380, 200, NULL, NULL, hI, NULL);

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
	HMENU hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	static HWND hButtonOk, hEditUser, hEditPwrd;
	char usernameBuffer[23];
	char passwordBuffer[23];
	char filename[256];
	filename[0] = 0;
	OPENFILENAMEA saveDialog = {};

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

		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
		AppendMenu(hFileMenu, MF_STRING, ID_NEW, L"New");
		AppendMenu(hFileMenu, MF_STRING, ID_LOAD, L"Load");
		AppendMenu(hFileMenu, MF_STRING, ID_SAVE, L"Save");
		AppendMenu(hFileMenu, MF_STRING, ID_CLOSE, L"Close");

		SetMenu(hwnd, hMenu);

		hButtonOk = CreateWindow(L"button", L"Ok",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			100, 100, 80, 25, hwnd, (HMENU)BUTTONOK,
			(HINSTANCE)GetWindowLong(hwnd, -6), NULL);

		hEditUser = CreateWindow(L"combobox", L"",
			WS_CHILD | WS_VISIBLE,
			100, 30, 200, 20, hwnd, (HMENU)EDITUSER,
			(HINSTANCE)GetWindowLong(hwnd, -6), NULL);

		hEditPwrd = CreateWindow(L"combobox", L"",
			WS_CHILD | WS_VISIBLE,
			100, 60, 200, 20, hwnd, (HMENU)EDITPWRD,
			(HINSTANCE)GetWindowLong(hwnd, -6), NULL);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case BUTTONOK:		
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
		case ID_SAVE:
			saveDialog.lStructSize = sizeof(OPENFILENAMEA);
			saveDialog.lpstrFilter = "Text-Dateien\0*.txt;*.text\0AlleDateien\0*.*";
			saveDialog.nFilterIndex = 1;
			saveDialog.lpstrFile = filename;
			saveDialog.nMaxFile = 256;
			saveDialog.lpstrTitle = "Select file to save";
			saveDialog.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
			saveDialog.nFileExtension = 1;
			saveDialog.lpstrDefExt = ".txt";
			if (GetSaveFileNameA(&saveDialog) != 0) {
				GetWindowTextA(hEditUser, usernameBuffer, 23);
				GetWindowTextA(hEditPwrd, passwordBuffer, 23);

				std::ofstream outfile;
				outfile.open(filename);
				outfile << usernameBuffer << ":" << passwordBuffer << endl;
				outfile.close();
			}
			break;
		case ID_CLOSE:
			PostQuitMessage(0);
			break;
		}

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}