#define UNICODE

#include "..\..\Common\Debug.h"
#include "..\..\res\res.h"
#include "SettingsProgramWindow.h"
#include "SettingsProgramEvents.h"
#include <prsht.h>


static INT_PTR CALLBACK ProgramProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:	return settingsProgWnd_initialization(hDlg);

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case BKM_ADDCONTAINERWNDBEHAVIOR_2:
		case BKM_ADDCONTAINERWNDBEHAVIOR_3:
		case BKM_DEFAULTTASKTYPE_COMBOBOX:		return settingsProgWnd_applyButton_turnOn(hDlg);

		case BKM_DEFAULTTASKTYPE_CHECKBOX:		return settingsProgWnd_taskTypeComobBox_changeEnable(hDlg);
		case BKM_ADDCONTAINERWNDBEHAVIOR_1:		return behavior_1_radioButtons_changeEnable(hDlg);
		}
	}

	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
		case PSN_KILLACTIVE:	return applySettings(hDlg);
		}
	}

	default:	return FALSE;
	}
}

LRESULT create_settingsProgramWindow(HINSTANCE hInstance, HWND hWndParent)
{
	PROPSHEETPAGE propsheetpage;
	propsheetpage.dwFlags = PSP_USETITLE;
	propsheetpage.dwSize = sizeof(PROPSHEETPAGE);
	propsheetpage.pszTemplate = MAKEINTRESOURCE(BKM_SETTINGSPROGRAMWND_PROPPAGE_1);
	propsheetpage.hInstance = hInstance;
	propsheetpage.pfnDlgProc = ProgramProc;
	propsheetpage.pszTitle = L"Программа";

	PROPSHEETHEADER propsheethead;
	propsheethead.dwFlags = PSH_PROPSHEETPAGE | PSH_NOCONTEXTHELP;
	propsheethead.dwSize = sizeof(PROPSHEETHEADER);
	propsheethead.hInstance = hInstance;
	propsheethead.hwndParent = hWndParent;
	propsheethead.pszCaption = L"Bookmark Manager: Настройки";
	propsheethead.nPages = 1;
	propsheethead.pStartPage = 0;
	propsheethead.ppsp = (LPCPROPSHEETPAGE)&propsheetpage;

	PropertySheet(&propsheethead);

	return 0;
}
