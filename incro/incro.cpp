#include<windows.h>
#include"resource.h"

#define ID_EDIT 100

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK keyProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK mouseProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK timeProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;

HWND hEdit;
HWND hWndMain;
HWND Wndkeyboard;
HWND Wndmouse;
HWND Wndtime;

LPCTSTR lpszClass = TEXT("Incro");
LPCTSTR keyboard_macro = TEXT("키보드 설정");
LPCTSTR mouse_macro = TEXT("마우스 설정");
LPCTSTR time_macro = TEXT("시간 설정");

POINT ptMouse;

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
	WndClass.style = CS_HREDRAW | CS_VREDRAW ;
	RegisterClass(&WndClass);

	//WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
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
	//TCHAR str[128] = TEXT("aaaaaaaaaaaaa");
	HDC hdc;
	PAINTSTRUCT ps;
	HFONT hFont, OldFont;
	LPCWSTR temp_text_1 = TEXT("시간(초)를 입력해주세요.");
	LPCWSTR temp_text_2 = TEXT("범위 : 0.001 ~300초");
	switch (iMessage) {
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 180;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 180;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);		
		hFont = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		TextOut(hdc, 20, 20, temp_text_1, lstrlen(temp_text_1));
		TextOut(hdc, 20, 40, temp_text_2, lstrlen(temp_text_2));
		SelectObject(hdc, OldFont);
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_CREATE:
		CreateWindow(TEXT("EDIT"), NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, 52, 70, 81, 20, hWnd, (HMENU)ID_EDIT, g_hInst, 0);
		CreateWindow(TEXT("button"), TEXT("확인"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 52, 100, 81, 20, hWnd, (HMENU)0, g_hInst, MB_OK);
		MoveWindow(hWnd, screenCx / 2 - 100, screenCy / 2 - 100, screenCx / 2 + 100, screenCy / 2 + 100, TRUE);
		//GetWindowText(hEdit, str, 128);
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
	HDC hdc;
	PAINTSTRUCT ps;	
	LPCWSTR temp_X = TEXT("X : ");
	LPCWSTR temp_Y = TEXT("Y : ");
	TCHAR xyPos[128];
	HFONT hFont, OldFont;
	
	switch (iMessage) {
	case WM_MOUSEMOVE:
		GetCursorPos(&ptMouse);
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 250;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 250;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 250;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 250;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hFont = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		//TextOut(hdc, 20, 20, temp_X, lstrlen(temp_X));
		//TextOut(hdc, 80, 20, temp_Y, lstrlen(temp_Y));
		wsprintf(xyPos, TEXT("X : %04d   Y : %04d"), ptMouse.x, ptMouse.y);
		TextOut(hdc, 20, 20, xyPos, lstrlen(xyPos));
		TextOut(hdc, 140, 40, temp_X, lstrlen(temp_X));
		TextOut(hdc, 140, 70, temp_Y, lstrlen(temp_Y));
		SelectObject(hdc, OldFont);
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;	
	case WM_CREATE:
		CreateWindow(TEXT("EDIT"), NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, 180, 40, 40, 20, hWnd, (HMENU)ID_EDIT, g_hInst, 0);
		CreateWindow(TEXT("EDIT"), NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, 180, 70, 40, 20, hWnd, (HMENU)ID_EDIT, g_hInst, 0);
		CreateWindow(TEXT("button"), TEXT("확인"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 52, 170, 81, 20, hWnd, (HMENU)0, g_hInst, MB_OK);
		CreateWindow(TEXT("button"), TEXT("이동"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 40, 50, 20, hWnd, (HMENU)1, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("왼쪽클릭"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 60, 80, 20, hWnd, (HMENU)2, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("왼쪽 누른상태"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 80, 130, 20, hWnd, (HMENU)3, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("땐 상태"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 100, 70, 20, hWnd, (HMENU)4, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("오른쪽 클릭"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 120,110, 20, hWnd, (HMENU)5, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("오른쪽 누른상태"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 140, 150, 20, hWnd, (HMENU)6, g_hInst, NULL);

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
	LPCWSTR temp_text = TEXT("추가할 키를 입력하세요");
	HFONT hFont, OldFont;
	static HWND InEdit;
	static int x = 20;
	static int y = 20;
	TCHAR Key_push[128];	

	switch (iMessage) {
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;
	case WM_KEYDOWN:
		hdc = BeginPaint(hWnd, &ps);
		Key_push = wParam;
		SetWindowText(InEdit, LOWORD(wParam));
		switch (wParam) {
			
		case VK_LEFT:
			SetWindowText(InEdit, LOWORD(wParam));
			//wsprintf(Key_push, TEXT("LEFT"));
			//TextOut(hdc, 40, 40, temp_text, lstrlen(temp_text));
			//MessageBox(hWnd, TEXT("LEFT"), TEXT("LEFT 누름"), MB_OK);			
			break;
		case VK_RIGHT:
			SetWindowText(InEdit, TEXT("RIGHT"));
			//wsprintf(Key_push, TEXT("RIGHT"));
			//TextOut(hdc, 20, 50, Key_push, lstrlen(Key_push));
			//MessageBox(hWnd, TEXT("RIGHT"), TEXT("RIGHT 누름"), MB_OK);			
			break;
		case VK_UP:
			//wsprintf(Key_push, TEXT("UP"));
			//TextOut(hdc, 20, 50, Key_push, lstrlen(Key_push));
			//MessageBox(hWnd, TEXT("UP"), TEXT("UP 누름"), MB_OK);			
			break;
		case VK_DOWN:
			//wsprintf(Key_push, TEXT("DOWN"));
			//TextOut(hdc, 20, 50, Key_push, lstrlen(Key_push));
			//MessageBox(hWnd, TEXT("DOWN"), TEXT("DOWN 누름"), MB_OK);			
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hFont = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		//TextOut(hdc, x, y, temp_text, lstrlen(temp_text));
		TextOut(hdc, 20, 20, temp_text, lstrlen(temp_text));
		//TextOut(hdc, 20, 50, Key_push, lstrlen(Key_push));
		SelectObject(hdc, OldFont);
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_CREATE:
		//CreateWindow(TEXT("EDIT"), NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, 52, 100, 81, 20, hWnd, (HMENU)ID_EDIT, g_hInst, 0);
		CreateWindow(TEXT("button"), TEXT("확인"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 52, 130, 81, 20, hWnd, (HMENU)0, g_hInst, MB_OK);
		CreateWindow(TEXT("button"), TEXT("한번누름"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 20, 40, 90, 30, hWnd, (HMENU)1, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("누르고있기"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON , 20, 65, 110, 30, hWnd, (HMENU)1, g_hInst, NULL);
		InEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED , 20, 100, 80, 20, hWnd, (HMENU)2, g_hInst, NULL);
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