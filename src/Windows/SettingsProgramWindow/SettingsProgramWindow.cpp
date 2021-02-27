#ifndef UNICODE
#define UNICODE
#endif

#include "SettingsProgramWindow.h"
#include "..\..\HandleManager\HandleManager.h"
#include "..\..\Common\BkmDef.h"
#include "..\..\Common\CommonOperations.h"

LRESULT CALLBACK SettingsProgramWindow::WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE: {
		HWND* hParentWnd = HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd");
		EnableWindow(*hParentWnd, true);
		SetFocus(*hParentWnd);

		HandleManager::removeHandleWnd(L"settingsProgramWindow_wnd");
		DestroyWindow(hWnd);
		return 0;
	}

	default: {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
}

void SettingsProgramWindow::create_settingsProgramWindow(HINSTANCE hInstance)
{
	HWND* hWnd = HandleManager::addHandleWnd(L"settingsProgramWindow_wnd");
	HWND* hParentWnd = HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd");

	*hWnd = CreateWindow(
		SETTINGSPROGRAMWND_CLASSNAME,
		SETTINGSPROGRAMWND_WNDNAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		600, 500,
		NULL,
		NULL,
		hInstance,
		NULL);

	CommonOperations::moveWindowToCenterScreen(*hWnd);

	ShowWindow(*hWnd, true);
	EnableWindow(*hParentWnd, false);
}
