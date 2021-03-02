#define UNICODE

#include "AboutProgramWindow.h"
#include "..\..\HandleManager\HandleManager.h"
#include "..\..\Common\CommonOperations.h"
#include "..\..\Common\BkmDef.h"

LRESULT CALLBACK AboutProgramWindow::WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE: {
		return close_window(hWnd);
	}

	default: {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
}

void AboutProgramWindow::create_aboutProgramWindow(HINSTANCE hInstance)
{
	HWND hWndParent = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERNWND_WND);

	HWND hWnd = CreateWindow(
		CLASSNAME_ABOUTPROGRAMNWND,
		WNDNAME_ABOUTPROGRAMNWND,
		WS_SYSMENU | WS_CAPTION,
		CW_USEDEFAULT, CW_USEDEFAULT,
		450, 200,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_ABOUTPROGRAMWND_WND);
	CommonOperations::moveWindowToCenterScreen(hWnd);

	ShowWindow(hWnd, true);
	EnableWindow(hWndParent, false);
}


LRESULT AboutProgramWindow::close_window(HWND hWnd)
{
	HWND hWndParent = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERNWND_WND);
	EnableWindow(hWndParent, true);
	SetFocus(hWndParent);

	HandleManager::removeHandleWnd(HNAME_ABOUTPROGRAMWND_WND);
	DestroyWindow(hWnd);
	return 0;
}
