#include "main.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX	mw_wndClass;
	MSG			mw_msg;

	mw_wndClass.lpszClassName = MW_CLASSNAME;
	mw_wndClass.lpfnWndProc = WndProc;
	mw_wndClass.hInstance = hInstance;
	mw_wndClass.cbSize = sizeof(WNDCLASSEX);
	mw_wndClass.style = CS_HREDRAW | CS_VREDRAW;
	mw_wndClass.lpszMenuName = MW_WNDNAME;
	mw_wndClass.cbWndExtra = NULL;
	mw_wndClass.cbClsExtra = NULL;
	mw_wndClass.hbrBackground = CreateSolidBrush(RGB(70, 68, 81));
	mw_wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	mw_wndClass.hIcon = NULL;
	mw_wndClass.hIconSm = NULL;

	if (!RegisterClassEx(&mw_wndClass))
	{
		MessageBox(NULL, L"Не удалось зарегистрировать класс окна", L"Error", MB_OK);
		return 0;
	}

	HWND mw_wnd = CreateWindow(
		MW_CLASSNAME,
		MW_WNDNAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		300, 300,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!mw_wnd)
	{
		MessageBox(NULL, L"Не удалось создать окно", L"Error", MB_OK);
		return 0;
	}

	moveWindowToCenterScreen(mw_wnd);
	ShowWindow(mw_wnd, nCmdShow);
	UpdateWindow(mw_wnd);

	while (GetMessage(&mw_msg, NULL, NULL, NULL))
	{
		//TranslateMessage(&mw_msg); //TODO: DELETE
		DispatchMessage(&mw_msg);
	}

	return (int)mw_msg.wParam;
}

LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	HDC wp_hDc;
	PAINTSTRUCT wp_paintstruct;

	switch (msg)
	{
	case WM_PAINT: {
		wp_hDc = BeginPaint(hWnd, &wp_paintstruct);
		EndPaint(hWnd, &wp_paintstruct);
		return 0;
	}

	case WM_CLOSE: {
		PostQuitMessage(0);
		return 0;
	}

	default: {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
}

void moveWindowToCenterScreen(HWND hWnd, HWND hWndInsertAfter)
{
	RECT rect;

	GetWindowRect(hWnd, &rect);
	SetWindowPos(hWnd, hWndInsertAfter, SCREENX - ((rect.right - rect.left) / 2), SCREENY - ((rect.bottom - rect.top) / 2), NULL, NULL, SWP_NOSIZE);
}
