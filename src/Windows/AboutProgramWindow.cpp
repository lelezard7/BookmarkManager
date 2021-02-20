#ifndef UNICODE
#define UNICODE
#endif

#include "AboutProgramWindow.h"
#include "..\Total\HandleManager.h"
#include "..\Total\GeneralOperations.h"
#include "..\Total\BmDef.h"

LRESULT CALLBACK AboutProgramWindow::WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE: {
		HWND* hWndParent;

		hWndParent = HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd");
		EnableWindow(*hWndParent, true);
		SetFocus(*hWndParent);

		HandleManager::removeHandleWnd(L"aboutProgramWindow_wnd");
		DestroyWindow(hWnd);
		return 0;
	}

	default: {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
}

void AboutProgramWindow::create_aboutProgramWindow(HINSTANCE hInstance)
{
	HWND* hWndParent = HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd");
	HWND* hWnd = HandleManager::addHandleWnd(L"aboutProgramWindow_wnd");

	*hWnd = CreateWindow(
		ABOUTPROGRAMNWND_CLASSNAME,
		ABOUTPROGRAMNWND_WNDNAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		600, 500,
		*hWndParent,
		NULL,
		hInstance,
		NULL);

	GeneralOperations::moveWindowToCenterScreen(*hWnd);

	ShowWindow(*hWnd, true);
	EnableWindow(*hWndParent, false);
}
