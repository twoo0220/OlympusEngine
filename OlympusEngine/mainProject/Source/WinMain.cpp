#include "pch.h"
 

/* Global Variables */
#pragma region GlobalVariables
	WCHAR	WindowClass[MAX_NAME_STRING];
	WCHAR	WindowTitle[MAX_NAME_STRING];

	INT		WindowWidth;
	INT		WindowHeight;

	HICON	hIcon;
#pragma endregion

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	// hWnd 창 핸들의 복사본, 실행 중인 창의 인스턴스
	// message 메시지 유형, 닫기 등등
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);	// 창의 종료 버튼을 누르면 프로그램 종료
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, message, wparam, lparam);
}

#pragma region Pre-Declarations

VOID InitializeVariables();
VOID CreateWindowClass();

#pragma endregion


int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT )
{
	InitializeVariables();
	CreateWindowClass();

	/* Create and Display out Window */

	HWND hWnd = CreateWindow(
		WindowClass,
		WindowTitle,
		WS_OVERLAPPEDWINDOW,	// window 창 스타일 설정
		CW_USEDEFAULT,			// 새 창의 기본 창 위치를 기본값으로 설정
		0,
		WindowWidth,
		WindowHeight,
		nullptr,
		nullptr,
		HInstance(),
		nullptr
	);

	if (!hWnd)
	{
		MessageBox(0, L"Failed to Create Window!", 0, 0);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);

	
	/* Lsten for Message events */

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}

VOID InitializeVariables()
{
	LoadString(HInstance(), IDS_PERGAMENAME, WindowTitle, MAX_NAME_STRING);
	LoadString(HInstance(), IDS_WINDOWCLASS, WindowClass, MAX_NAME_STRING);

	WindowWidth = 1366;
	WindowHeight = 768;
	hIcon = LoadIcon(HInstance(), MAKEINTRESOURCE(IDI_MAINICON));	// resource에서 직접 로드
}

VOID CreateWindowClass()
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);		// 클래스의 크기
	wcex.style = CS_HREDRAW | CS_VREDRAW;	//
	wcex.cbClsExtra = 0;					// 추가 메모리를 위한 작업
	wcex.cbWndExtra = 0;					// 현재로는 추가 작업을 할 필요가 없으니 0
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.hIcon = hIcon;
	wcex.hIconSm = hIcon;
	wcex.lpszClassName = WindowClass;
	wcex.lpszMenuName = nullptr;
	wcex.hInstance = HInstance();
	wcex.lpfnWndProc = WindowProcess;
	RegisterClassEx(&wcex);
}