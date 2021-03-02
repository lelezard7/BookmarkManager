#define UNICODE

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
	case WM_COMMAND: {
		if (IsDlgButtonChecked(hWnd, 3222)) {
			CheckDlgButton(hWnd, 3222, BST_UNCHECKED);
			HWND hDropDList = HandleManager::getHandleWnd(HNAME_SETTINGSPROGRAMWND_TaskTypeDropDList);
			EnableWindow(hDropDList, false);
		}
		else {
			CheckDlgButton(hWnd, 3222, BST_CHECKED);
			HWND hDropDList = HandleManager::getHandleWnd(HNAME_SETTINGSPROGRAMWND_TaskTypeDropDList);
			EnableWindow(hDropDList, true);
		}
		return 0;
	}

	case WM_NOTIFY: {
		switch (((LPNMHDR)lParam)->code)
		{
		case TCN_SELCHANGE: {
			int curPage = TabCtrl_GetCurSel(((LPNMHDR)lParam)->hwndFrom);
			HWND hDropDList = HandleManager::getHandleWnd(HNAME_SETTINGSPROGRAMWND_TaskTypeDropDList);
			HWND hCheckBox = HandleManager::getHandleWnd(HNAME_SETTINGSPROGRAMWND_EnableTaskTypeCheckBox);
			
			if (curPage == 0)
			{
				ShowWindow(hCheckBox, true);
				ShowWindow(hDropDList, true);
			}
			else
			{
				ShowWindow(hCheckBox, false);
				ShowWindow(hDropDList, false);
			}
		}
		}
		return 0;
	}

	case WM_SIZE: {
		adjustmentOfControls();
		return 0;
	}

	case WM_CLOSE: {
		return close_window(hWnd);
	}

	default: {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
}

void SettingsProgramWindow::create_settingsProgramWindow(HINSTANCE hInstance)
{
	HWND hWndParent = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERNWND_WND);

	HWND hWnd = CreateWindow(
		CLASSNAME_SETTINGSPROGRAMWND,
		WNDNAME_SETTINGSPROGRAMWND,
		WS_SYSMENU | WS_CAPTION,
		CW_USEDEFAULT, CW_USEDEFAULT,
		600, 500,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_SETTINGSPROGRAMWND_WND);

	HWND hNavPanel = create_navigationPanel(hWnd, hInstance);
	{
		create_enableTaskTypeCheckBox(hNavPanel, hInstance);
		create_taskTypeDropDList(hNavPanel, hInstance);
	}

	CommonOperations::moveWindowToCenterScreen(hWnd);

	ShowWindow(hWnd, true);
	EnableWindow(hWndParent, false);
}


HWND SettingsProgramWindow::create_navigationPanel(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		WC_TABCONTROL,
		NULL,
		WS_VISIBLE | WS_CHILD,
		SettingsProgramWnd_navigationPanel_X,
		SettingsProgramWnd_navigationPanel_Y,
		SettingsProgramWnd_navigationPanel_WIDTH,
		SettingsProgramWnd_navigationPanel_HEIGHT,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_SETTINGSPROGRAMWND_NavigationPanel);

	TCITEM tcitem;
	tcitem.mask = TCIF_TEXT;

	tcitem.pszText = (LPWSTR)L"General settings";
	TabCtrl_InsertItem(hWnd, 1, &tcitem);

	tcitem.pszText = (LPWSTR)L"Internet";
	TabCtrl_InsertItem(hWnd, 2, &tcitem);

	return hWnd;
}

void SettingsProgramWindow::create_taskTypeDropDList(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"COMBOBOX",
		NULL,
		WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
		SettingsProgramWnd_taskTypeDropDList_X,
		SettingsProgramWnd_taskTypeDropDList_Y,
		SettingsProgramWnd_taskTypeDropDList_WIDTH,
		SettingsProgramWnd_taskTypeDropDList_HEIGHT,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_SETTINGSPROGRAMWND_TaskTypeDropDList);

	SendMessage(hWnd, CB_INSERTSTRING, -1, (LPARAM)L"URL");
	SendMessage(hWnd, CB_INSERTSTRING, -1, (LPARAM)L"Program");
	EnableWindow(hWnd, false);
}

void SettingsProgramWindow::create_enableTaskTypeCheckBox(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"BUTTON",
		L"Set the default task type",
		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		SettingsProgramWnd_enableTaskTypeCheckBox_X,
		SettingsProgramWnd_enableTaskTypeCheckBox_Y,
		SettingsProgramWnd_enableTaskTypeCheckBox_WIDTH,
		SettingsProgramWnd_enableTaskTypeCheckBox_HEIGHT,
		GetParent(hWndParent), //TODO: Сделать красиво
		(HMENU)3222, //TODO: Сделать красиво
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_SETTINGSPROGRAMWND_EnableTaskTypeCheckBox);
}


void SettingsProgramWindow::adjustmentOfControls()
{
	CheckList checkList;
	checkList.push_back(HNAME_SETTINGSPROGRAMWND_NavigationPanel);

	if (HandleManager::checkExistence(checkList))
	{
		HWND hNavPanel = HandleManager::getHandleWnd(HNAME_SETTINGSPROGRAMWND_NavigationPanel);

		SetWindowPos(hNavPanel, HWND_TOP, SettingsProgramWnd_navigationPanel_X,
			SettingsProgramWnd_navigationPanel_Y,
			SettingsProgramWnd_navigationPanel_WIDTH,
			SettingsProgramWnd_navigationPanel_HEIGHT, NULL);
	}
}

LRESULT SettingsProgramWindow::close_window(HWND hWnd)
{
	HWND hWndParent = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERNWND_WND);
	EnableWindow(hWndParent, true);
	SetFocus(hWndParent);

	HandleManager::removeHandleWnd(HNAME_SETTINGSPROGRAMWND_EnableTaskTypeCheckBox);
	HandleManager::removeHandleWnd(HNAME_SETTINGSPROGRAMWND_TaskTypeDropDList);
	HandleManager::removeHandleWnd(HNAME_SETTINGSPROGRAMWND_NavigationPanel);
	HandleManager::removeHandleWnd(HNAME_SETTINGSPROGRAMWND_WND);
	DestroyWindow(hWnd);
	return 0;
}
