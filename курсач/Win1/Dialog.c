#include<Windows.h>
#include"Header.h"

HWND hwnd1, bt_no, st;

LRESULT  WINAPI WindProc1(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
	}
	else
		return DefWindowProcA(hwnd, message, wparam, lparam);
}

void mistake(char fraza[])
{
	FreeConsole();
	WNDCLASSA wnd;
	HBRUSH hb = (HBRUSH)CreateSolidBrush(RGB(10, 255, 90));
	memset(&wnd, 0, sizeof(WNDCLASSA));
	wnd.lpszClassName = "My Window";
	wnd.hbrBackground = hb;
	wnd.lpfnWndProc = WindProc1;
	RegisterClassA(&wnd);

	hwnd1 = CreateWindow("My Window", "Main Window", WS_TILEDWINDOW, 10, 10, 180, 150, NULL, NULL, NULL, NULL);
	ShowWindow(hwnd1, SW_SHOW);
	st = CreateWindow("static", fraza, WS_VISIBLE | WS_CHILD, 10, 20, 150, 40, hwnd1, (HMENU)1111, NULL, NULL);
	bt_no = CreateWindow("button", "OK", WS_VISIBLE | WS_CHILD, 50, 70, 70, 40, hwnd1, 911, NULL, NULL);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}