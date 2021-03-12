#define UNICODE

#include "..\..\ApplicationSettings\ApplicationSettings.h"
#include "..\..\Common\PositionAndSizeControls.h"
#include "..\..\res\res.h"
#include "..\..\Archive\Archive.h"
#include "SettingsProgramWindow.h"
#include <CommCtrl.h>
#include <prsht.h>

INT_PTR CALLBACK ProgramProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK NetworkProc(HWND, UINT, WPARAM, LPARAM);


void SettingsProgramWindow::create_settingsProgramWindow(HINSTANCE hInstance, HWND hWndParent)
{
	PROPSHEETPAGE propsheetpage[2];
	PROPSHEETHEADER propsheethead;

	propsheetpage[0].dwFlags = PSP_USETITLE;
	propsheetpage[0].dwSize = sizeof(PROPSHEETPAGE);
	propsheetpage[0].pszTemplate = MAKEINTRESOURCE(BKM_SETTINGSPROGRAMWND_PROPPAGE_1);
	propsheetpage[0].hInstance = hInstance;
	propsheetpage[0].pfnDlgProc = ProgramProc;
	propsheetpage[0].pszTitle = L"Program";

	//propsheetpage[1].dwFlags = PSP_USETITLE;
	//propsheetpage[1].dwSize = sizeof(PROPSHEETPAGE);
	//propsheetpage[1].pszTemplate = MAKEINTRESOURCE(BKM_SETTINGSPROGRAMWND_PROPPAGE_2);
	//propsheetpage[1].hInstance = hInstance;
	//propsheetpage[1].pfnDlgProc = NetworkProc;
	//propsheetpage[1].pszTitle = L"Network";


	propsheethead.dwFlags = PSH_PROPSHEETPAGE | PSH_NOCONTEXTHELP;
	propsheethead.dwSize = sizeof(PROPSHEETHEADER);
	propsheethead.hInstance = hInstance;
	propsheethead.hwndParent = hWndParent;
	propsheethead.pszCaption = L"Bookmark Manager: Settings";
	propsheethead.nPages = 1;
	propsheethead.pStartPage = 0;
	propsheethead.ppsp = (LPCPROPSHEETPAGE)&propsheetpage;
	
	PropertySheet(&propsheethead);
}


//INT_PTR CALLBACK NetworkProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//	default: {
//		return FALSE;
//	}
//	}
//}


//------------------------------


void addcontainerwndbehavior_1(HWND);
INT_PTR initialization(HWND);
INT_PTR applySettings(HWND);

INT_PTR CALLBACK ProgramProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG: {
		return initialization(hDlg);
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case BKM_DEFAULTTASKTYPE_CKB: {
			HWND hTaskType = GetDlgItem(hDlg, BKM_DEFAULTTASKTYPE);
			if (hTaskType)
			{
				bool check = IsDlgButtonChecked(hDlg, BKM_DEFAULTTASKTYPE_CKB) == BST_CHECKED;
				EnableWindow(hTaskType, check);
				PropSheet_Changed(GetParent(hDlg), hDlg);
			}
			return TRUE;
		}

		case BKM_ADDCONTAINERWNDBEHAVIOR_1: {
			addcontainerwndbehavior_1(hDlg);
			PropSheet_Changed(GetParent(hDlg), hDlg);
			return TRUE;
		}

		case BKM_ADDCONTAINERWNDBEHAVIOR_2:
		case BKM_ADDCONTAINERWNDBEHAVIOR_3:
		case BKM_DEFAULTTASKTYPE: {
			PropSheet_Changed(GetParent(hDlg), hDlg);
			return TRUE;
		}

		default: {
			return TRUE;
		}
		}
	}

	case WM_NOTIFY: {
		switch (((LPNMHDR)lParam)->code)
		{
		case PSN_KILLACTIVE: {
			return applySettings(hDlg);
		}

		default: {
			return TRUE;
		}
		}
	}

	default: {
		return FALSE;
	}
	}
}

void addcontainerwndbehavior_1(HWND hDlg)
{
	HWND hRadioB1 = GetDlgItem(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_2);
	HWND hRadioB2 = GetDlgItem(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_3);
	if (hRadioB1 != NULL && hRadioB2 != NULL)
	{
		bool check = IsDlgButtonChecked(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_1) == BST_UNCHECKED;
		EnableWindow(hRadioB1, check);
		EnableWindow(hRadioB2, check);
	}
}

INT_PTR initialization(HWND hDlg)
{
	HWND hTaskType = GetDlgItem(hDlg, BKM_DEFAULTTASKTYPE);
	if (hTaskType) {
		createTaskTypesCB(hTaskType);
	}
	else {
		return TRUE;
	}

	if (ApplicationSettings::getDefaultTaskType() != TASKT_NOTSPECIFIED)
	{
		CheckDlgButton(hDlg, BKM_DEFAULTTASKTYPE_CKB, true);
		EnableWindow(hTaskType, true);
		SendMessage(hTaskType, CB_SETCURSEL, ApplicationSettings::getDefaultTaskType(), NULL);
	}


	if (ApplicationSettings::getStartupMethodContainerCreationWindow() == StartupMethod::SHOW_CLOSED_WINDOW)
	{
		CheckDlgButton(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_1, BST_CHECKED);
	}
	else
	{
		addcontainerwndbehavior_1(hDlg);

		if (ApplicationSettings::getStartupMethodContainerCreationWindow() == StartupMethod::CREATE_NEW_WINDOW) {
			CheckDlgButton(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_2, BST_CHECKED);
		}
		else if (ApplicationSettings::getStartupMethodContainerCreationWindow() == StartupMethod::CONTINUE_UNFINISHED_CREATION) {
			CheckDlgButton(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_3, BST_CHECKED);
		}
	}

	return TRUE;
}


void changeDefaultTaskType(HWND);
void changeStartupMethod(HWND);

INT_PTR applySettings(HWND hDlg)
{
	changeDefaultTaskType(hDlg);
	changeStartupMethod(hDlg);
	
	return TRUE;
}

void changeDefaultTaskType(HWND hDlg)
{
	HWND hTaskType = GetDlgItem(hDlg, BKM_DEFAULTTASKTYPE);
	if (hTaskType)
	{
		if (IsDlgButtonChecked(hDlg, BKM_DEFAULTTASKTYPE_CKB) == BST_CHECKED)
		{
			int index = SendMessage(hTaskType, CB_GETCURSEL, NULL, NULL);
			ApplicationSettings::setDefaultTaskType(index);
		}
		else
		{
			ApplicationSettings::setDefaultTaskType(TASKT_NOTSPECIFIED);
		}
	}
}

void changeStartupMethod(HWND hDlg)
{
	if (IsDlgButtonChecked(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_1) == BST_CHECKED)
	{
		ApplicationSettings::setStartupMethodContainerCreationWindow(StartupMethod::SHOW_CLOSED_WINDOW);
		return;
	}

	if (IsDlgButtonChecked(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_2) == BST_CHECKED)
	{
		ApplicationSettings::setStartupMethodContainerCreationWindow(StartupMethod::CREATE_NEW_WINDOW);

		if (HandleManager::checkExistence(HNAME_CONTAINERCREATIONWND_WND))
		{
			HWND hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND);
			SendMessage(hWnd, WM_CLOSE, NULL, NULL);
		}
	}
	else if (IsDlgButtonChecked(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_3) == BST_CHECKED)
	{
		ApplicationSettings::setStartupMethodContainerCreationWindow(StartupMethod::CONTINUE_UNFINISHED_CREATION);
	}
}
