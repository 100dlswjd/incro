#include<windows.h>
#include"resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK keyProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK mouseProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK timeProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;

HWND hWndMain;
HWND Wndkeyboard;
HWND Wndmouse;
HWND Wndtime;

LPCTSTR lpszClass = TEXT("Incro");
LPCTSTR keyboard_macro = TEXT("키보드 설정");
LPCTSTR mouse_macro = TEXT("마우스 설정");
LPCTSTR time_macro = TEXT("시간 설정");

int screenCx = GetSystemMetrics(SM_CXSCREEN);
int screenCy = GetSystemMetrics(SM_CYSCREEN);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = keyboard_macro;
	WndClass.lpfnWndProc = keyProc;
	RegisterClass(&WndClass);

	WndClass.lpszClassName = mouse_macro;
	WndClass.lpfnWndProc = mouseProc;
	RegisterClass(&WndClass);

	WndClass.lpszClassName = time_macro;
	WndClass.lpfnWndProc = timeProc;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_SYSMENU | WS_MINIMIZEBOX , CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK timeProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;
	case WM_CREATE:
		MoveWindow(hWnd, screenCx / 2 - 100, screenCy / 2 - 100, screenCx / 2 + 100, screenCy / 2 + 100, TRUE);
		return 0;
	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}


LRESULT CALLBACK mouseProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	switch (iMessage) {
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;
	case WM_CREATE:
		MoveWindow(hWnd, screenCx / 2 - 100, screenCy / 2 - 100, screenCx / 2 + 100, screenCy / 2 + 100, TRUE);
		return 0;
	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK keyProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage) {
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		return 0;
	case WM_CREATE:
		MoveWindow(hWnd, screenCx / 2 - 100, screenCy / 2 - 100, screenCx / 2 + 100, screenCy / 2 + 100, TRUE);
		return 0;
	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 300;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 300;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 300;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 300;
		return 0;
	case WM_CREATE:
		hWndMain = hWnd;
		MoveWindow(hWnd, screenCx/2 -150, screenCy/2 - 150, screenCx/2 + 150, screenCy/2 +150, TRUE);
		CreateWindow(TEXT("listBox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY, 10, 10, 180, 180, hWnd, (HMENU)100, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("키보드"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 10, 70, 35, hWnd, (HMENU)1, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("마우스"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 55, 70, 35, hWnd, (HMENU)2, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("시간"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 100, 70, 35, hWnd, (HMENU)3, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("지우기"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 145, 70, 35, hWnd, (HMENU)4, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("추가"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 20, 200, 60, 25, hWnd, (HMENU)5, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("삽입"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 100, 200, 60, 25, hWnd, (HMENU)6, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("반복"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 180, 200, 60, 25, hWnd, (HMENU)7, g_hInst, NULL);

		Wndkeyboard = CreateWindow(keyboard_macro, keyboard_macro, WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, g_hInst, NULL);

		Wndmouse = CreateWindow(mouse_macro, mouse_macro, WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, g_hInst, NULL);

		Wndtime = CreateWindow(time_macro, time_macro, WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL,g_hInst, NULL);

		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 1:
			ShowWindow(Wndkeyboard, SW_SHOW);
			break;
		case 2:
			ShowWindow(Wndmouse, SW_SHOW);
			break;
		case 3:
			ShowWindow(Wndtime, SW_SHOW);
			break;
		case 4:
			MessageBox(hWnd, TEXT("지우기 클릭했지 ?"), TEXT("incro"), MB_OK);
			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_CLOSE:
	{
		int temp;
		temp = MessageBox(hWnd, TEXT("저장이 안되어있습니다 \n종료하시겠습니까 ?"), TEXT("경고"), MB_OKCANCEL);
		if (temp == IDOK) {
			break;
		}
		else {
			return 0;
		}
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}