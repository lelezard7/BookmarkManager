#ifndef UNICODE
#define UNICODE
#endif

#include "SettingsProgramWindow.h"
#include "..\..\HandleManager\HandleManager.h"
#include "..\..\Common\BkmDef.h"
#include "..\..\Common\CommonOperations.h"
#include "..\..\Common\PositionAndSizeControls.h"
#include "..\..\ApplicationSettings\ApplicationSettings.h"
#include <CommCtrl.h>

LRESULT CALLBACK SettingsProgramWindow::WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (msg)
	{
	/*case WM_COMMAND: {
		if (IsDlgButtonChecked(hWnd, 3222)) {
			CheckDlgButton(hWnd, 3222, BST_UNCHECKED);
			HWND* hDropDList = HandleManager::getHandleWnd(L"settingsProgramWindow_taskTypeDropDList");
			EnableWindow(*hDropDList, false);
		}
		else {
			CheckDlgButton(hWnd, 3222, BST_CHECKED);
			HWND* hDropDList = HandleManager::getHandleWnd(L"settingsProgramWindow_taskTypeDropDList");
			EnableWindow(*hDropDList, true);
		}
		return 0;
	}

	case WM_NOTIFY: {
		switch (((LPNMHDR)lParam)->code)
		{
		case TCN_SELCHANGE: {
			int curPage = TabCtrl_GetCurSel(((LPNMHDR)lParam)->hwndFrom);
			HWND* hDropDList = HandleManager::getHandleWnd(L"settingsProgramWindow_taskTypeDropDList");
			HWND* hCheckBox = HandleManager::getHandleWnd(L"settingsProgramWindow_enableTaskTypeCheckBox");
			
			if (curPage == 0)
			{
				ShowWindow(*hCheckBox, true);
				ShowWindow(*hDropDList, true);
			}
			else
			{
				ShowWindow(*hCheckBox, false);
				ShowWindow(*hDropDList, false);
			}
		}
		}
		return 0;
	}

	case WM_SIZE: {
		adjustmentOfControls();
		return 0;
	}

	case WM_GETMINMAXINFO: {
		CommonOperations::setMinimumWindowSize(600, 500, lParam);
		return 0;
	}

	case WM_CLOSE: {
		HWND* hParentWnd = HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd");
		EnableWindow(*hParentWnd, true);
		SetFocus(*hParentWnd);

		HandleManager::removeHandleWnd(L"settingsProgramWindow_enableTaskTypeCheckBox");
		HandleManager::removeHandleWnd(L"settingsProgramWindow_taskTypeDropDList");
		HandleManager::removeHandleWnd(L"settingsProgramWindow_navigationPanel");
		HandleManager::removeHandleWnd(L"settingsProgramWindow_wnd");
		DestroyWindow(hWnd);
		return 0;
	}*/

	default: {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
}

//void SettingsProgramWindow::create_settingsProgramWindow(HINSTANCE hInstance)
//{
//	HWND* hWnd = HandleManager::addHandleWnd(L"settingsProgramWindow_wnd");
//	HWND* hParentWnd = HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd");
//
//	*hWnd = CreateWindow(
//		SETTINGSPROGRAMWND_CLASSNAME,
//		SETTINGSPROGRAMWND_WNDNAME,
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, CW_USEDEFAULT,
//		600, 500,
//		NULL,
//		NULL,
//		hInstance,
//		NULL);
//
//	create_navigationPanel(*hWnd, hInstance);
//	HWND* hTabCtrl = HandleManager::getHandleWnd(L"settingsProgramWindow_navigationPanel");
//	create_enableTaskTypeCheckBox(*hTabCtrl, hInstance);
//	create_taskTypeDropDList(*hTabCtrl, hInstance);
//
//	CommonOperations::moveWindowToCenterScreen(*hWnd);
//
//	ShowWindow(*hWnd, true);
//	EnableWindow(*hParentWnd, false);
//}
//
//
//void SettingsProgramWindow::create_navigationPanel(HWND hWndParent, HINSTANCE hInstance)
//{
//	HWND* hTabCtrl = HandleManager::addHandleWnd(L"settingsProgramWindow_navigationPanel");
//
//	*hTabCtrl = CreateWindow(
//		WC_TABCONTROL,
//		NULL,
//		WS_VISIBLE | WS_CHILD,
//		SettingsProgramWnd_navigationPanel_X,
//		SettingsProgramWnd_navigationPanel_Y,
//		SettingsProgramWnd_navigationPanel_WIDTH,
//		SettingsProgramWnd_navigationPanel_HEIGHT,
//		hWndParent,
//		NULL,
//		hInstance,
//		NULL);
//
//	TCITEM tcitem;
//	tcitem.mask = TCIF_TEXT;
//	tcitem.pszText = (LPWSTR)L"General settings";
//	TabCtrl_InsertItem(*hTabCtrl, 1, &tcitem);
//
//	tcitem.mask = TCIF_TEXT;
//	tcitem.pszText = (LPWSTR)L"Internet";
//	TabCtrl_InsertItem(*hTabCtrl, 2, &tcitem);
//}
//
//void SettingsProgramWindow::create_taskTypeDropDList(HWND hWndParent, HINSTANCE hInstance)
//{
//	HWND* hDropDList = HandleManager::addHandleWnd(L"settingsProgramWindow_taskTypeDropDList");
//
//	*hDropDList = CreateWindow(
//		L"COMBOBOX",
//		NULL,
//		WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
//		SettingsProgramWnd_taskTypeDropDList_X,
//		SettingsProgramWnd_taskTypeDropDList_Y,
//		SettingsProgramWnd_taskTypeDropDList_WIDTH,
//		SettingsProgramWnd_taskTypeDropDList_HEIGHT,
//		hWndParent,
//		NULL,
//		hInstance,
//		NULL);
//
//	SendMessage(*hDropDList, CB_INSERTSTRING, -1, (LPARAM)L"URL");
//	SendMessage(*hDropDList, CB_INSERTSTRING, -1, (LPARAM)L"Program");
//	EnableWindow(*hDropDList, false);
//}
//
//void SettingsProgramWindow::create_enableTaskTypeCheckBox(HWND hWndParent, HINSTANCE hInstance)
//{
//	HWND* hCheckBox = HandleManager::addHandleWnd(L"settingsProgramWindow_enableTaskTypeCheckBox");
//
//	*hCheckBox = CreateWindow(
//		L"BUTTON",
//		L"Set the default task type",
//		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
//		SettingsProgramWnd_enableTaskTypeCheckBox_X,
//		SettingsProgramWnd_enableTaskTypeCheckBox_Y,
//		SettingsProgramWnd_enableTaskTypeCheckBox_WIDTH,
//		SettingsProgramWnd_enableTaskTypeCheckBox_HEIGHT,
//		GetParent(hWndParent),
//		(HMENU)3222,
//		hInstance,
//		NULL);
//}
//
//
//void SettingsProgramWindow::adjustmentOfControls()
//{
//	HandleName checklist[]{ L"settingsProgramWindow_navigationPanel", L"\0" };
//
//	if (HandleManager::checkExistence(checklist))
//	{
//		HWND* hTabCtrl = HandleManager::getHandleWnd(L"settingsProgramWindow_navigationPanel");
//
//		SetWindowPos(*hTabCtrl, HWND_TOP, SettingsProgramWnd_navigationPanel_X,
//			SettingsProgramWnd_navigationPanel_Y,
//			SettingsProgramWnd_navigationPanel_WIDTH,
//			SettingsProgramWnd_navigationPanel_HEIGHT, NULL);
//	}
//}
