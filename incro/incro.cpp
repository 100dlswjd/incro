#include<windows.h>
#include"resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Incro");
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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_SYSMENU | WS_MINIMIZEBOX , CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
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
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 1:
			MessageBox(hWnd, TEXT("키보드 클릭했지 ?"),TEXT("incro"),MB_OK);
			CreateWindow(TEXT("button"), TEXT("이동"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 10, 30, 30, hWnd, (HMENU)1, g_hInst, NULL);			
			break;
		case 2:
			MessageBox(hWnd, TEXT("마우스 클릭했지 ?"), TEXT("incro"), MB_OK);
			break;
		case 3:
			MessageBox(hWnd, TEXT("시간 클릭했지 ?"), TEXT("incro"), MB_OK);
			break;
		case 4:
			MessageBox(hWnd, TEXT("지우기 클릭했지 ?"), TEXT("incro"), MB_OK);
			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

