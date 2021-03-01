//TODO: Ñìåíèòü GetModuleHandle() íà GetModuleHandleEx()
//TODO: Èçáàâèòüñÿ îò óòå÷åê ïàìÿòè

#ifndef UNICODE
#define UNICODE
#endif

#include "BookmarkManagerWindow.h"
#include "..\ContainerCreationWindow\ContainerCreationWindow.h"
#include "..\AboutProgramWindow\AboutProgramWindow.h"
#include "..\SettingsProgramWindow\SettingsProgramWindow.h"
#include "..\..\HandleManager\HandleManager.h"
#include "..\..\Common\BkmDef.h"
#include "..\..\ApplicationSettings\ApplicationSettings.h"
#include "..\..\Common\CommonOperations.h"
#include "..\..\Archive\Archive.h"
#include "..\..\Common\PositionAndSizeControls.h"
#include "..\..\res\Resource.h"
#include <CommCtrl.h>
#include <HtmlHelp.h>


LRESULT CALLBACK BookmarkManagerWindow::WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE: {
		adjustmentOfControls(hWnd);
		return 0;
	}

	//case WM_COMMAND: {
	//	if (HIWORD(wParam) == 0)
	//	{
	//		switch (LOWORD(wParam))
	//		{
	//		case ID_BOOKMARKMANAGERNWND_ADDBUTTON: {
	//			addButton_pressed();
	//			return 0;
	//		}

	//		case ID_BOOKMARKMANAGERNWND_OPENBUTTON: {
	//			openButton_pressed();
	//			return 0;
	//		}

	//		case ID_MENU_CLOSEPROGRAM: {
	//			PostMessage(hWnd, WM_CLOSE, NULL, NULL);
	//			return 0;
	//		}

	//		case ID_MENU_ABOUTPROGRAM: {
	//			AboutProgramWindow::create_aboutProgramWindow(GetModuleHandle(NULL));
	//			return 0;
	//		}

	//		case ID_MENU_SETTINGSPROGRAM: {
	//			SettingsProgramWindow::create_settingsProgramWindow(GetModuleHandle(NULL));
	//			return 0;
	//		}

	//		case ID_MENU_HOWTOUSE: {
	//			HWND hHelpWnd = HtmlHelp(hWnd, L"BookmarkManager.chm", HH_DISPLAY_TOPIC, NULL);
	//			if (!hHelpWnd)
	//				debugMessage(L"Couldn't open .chm file");
	//			CommonOperations::moveWindowToCenterScreen(hHelpWnd);
	//			return 0;
	//		}
	//		}
	//	}
	//	return 0;
	//}

	//case UM_SHOWCREATEDCONTAINER: {
	//	showCreatedContainer(lParam);
	//	return 0;
	//}

	case WM_GETMINMAXINFO: {
		CommonOperations::setMinimumWindowSize(350, 400, lParam);
		return 0;
	}

	case WM_CLOSE: {
		DestroyWindow(hWnd);
		return 0;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}

	default: {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
}

HWND BookmarkManagerWindow::create_bookmarkManagerWindow(HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		BOOKMARKMANAGERWND_CLASSNAME,
		BOOKMARKMANAGERNWND_WNDNAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 650,
		NULL,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, NAME_BOOKMARKMANAGERNWND_WND);

	HMENU hMenu = create_menu();
	SetMenu(hWnd, hMenu);

	create_mainListView(hWnd, hInstance);
	create_addButton(hWnd, hInstance);
	create_openButton(hWnd, hInstance);
	create_clearButton(hWnd, hInstance);

	CommonOperations::moveWindowToCenterScreen(hWnd);

	return hWnd;
}


HMENU BookmarkManagerWindow::create_menu()
{
	HMENU	hMenuBar = CreateMenu();
	HMENU	hFilePopupMenu = CreatePopupMenu();
	HMENU	hHelpPopupMenu = CreatePopupMenu();

	AppendMenu(hMenuBar, MF_STRING | MF_POPUP, (UINT)hFilePopupMenu, L"File");
	{
		AppendMenu(hFilePopupMenu, MF_STRING, ID_MENU_NEWFILE, L"New");
		AppendMenu(hFilePopupMenu, MF_STRING, ID_MENU_OPENFILE, L"Open...");
		AppendMenu(hFilePopupMenu, MF_STRING, ID_MENU_SAVEFILE, L"Save");
		AppendMenu(hFilePopupMenu, MF_STRING, ID_MENU_SETTINGSPROGRAM, L"Settings");
		AppendMenu(hFilePopupMenu, MF_STRING, ID_MENU_CLOSEPROGRAM, L"Close");
	}

	AppendMenu(hMenuBar, MF_STRING | MF_POPUP, (UINT)hHelpPopupMenu, L"Help");
	{
		AppendMenu(hHelpPopupMenu, MF_STRING, ID_MENU_HOWTOUSE, L"How to use");
		AppendMenu(hHelpPopupMenu, MF_STRING, ID_MENU_ABOUTPROGRAM, L"About BookmarkManager");
	}

	return hMenuBar;
}

void BookmarkManagerWindow::create_mainListView(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		WC_LISTVIEW,
		NULL,
		WS_CHILD | WS_VISIBLE | LVS_REPORT,
		BookmarkManagerWnd_mainListView_X,
		BookmarkManagerWnd_mainListView_Y,
		BookmarkManagerWnd_mainListView_WIDTH,
		BookmarkManagerWnd_mainListView_HEIGHT,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, NAME_BOOKMARKMANAGERNWND_MainListView);

	LVCOLUMN lvcolumn;
	lvcolumn.mask = LVCF_WIDTH | LVCF_TEXT;
	lvcolumn.cx = 250;
	lvcolumn.pszText = (LPWSTR)L"Name";

	ListView_InsertColumn(hWnd, 1, &lvcolumn);
}

void BookmarkManagerWindow::create_addButton(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"BUTTON",
		L"Add",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		BookmarkManagerWnd_addButton_X,
		BookmarkManagerWnd_addButton_Y,
		BookmarkManagerWnd_addButton_WIDTH,
		BookmarkManagerWnd_addButton_HEIGHT,
		hWndParent,
		(HMENU)ID_BOOKMARKMANAGERNWND_ADDBUTTON,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, NAME_BOOKMARKMANAGERNWND_AddButton);
}

void BookmarkManagerWindow::create_openButton(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"BUTTON",
		L"Open",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		BookmarkManagerWnd_openButton_X,
		BookmarkManagerWnd_openButton_Y,
		BookmarkManagerWnd_openButton_WIDTH,
		BookmarkManagerWnd_openButton_HEIGHT,
		hWndParent,
		(HMENU)ID_BOOKMARKMANAGERNWND_OPENBUTTON,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, NAME_BOOKMARKMANAGERNWND_OpenButton);
}

void BookmarkManagerWindow::create_clearButton(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"BUTTON",
		L"Clear",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		BookmarkManagerWnd_cleanButton_X,
		BookmarkManagerWnd_cleanButton_Y,
		BookmarkManagerWnd_cleanButton_WIDTH,
		BookmarkManagerWnd_cleanButton_HEIGHT,
		hWndParent,
		(HMENU)ID_BOOKMARKMANAGERNWND_CLEANBUTTON,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, NAME_BOOKMARKMANAGERNWND_ClearButton);
}


//void BookmarkManagerWindow::addButton_pressed()
//{
//	if (ApplicationSettings::getStartupMethodContainerCreationWindow() == StartupMethod::SHOW_CLOSED_WINDOW)
//	{
//		if (HandleManager::checkExistence(L"containerCreationWindow_wnd"))
//		{
//			HWND* hWnd;
//
//			hWnd = HandleManager::getHandleWnd(L"containerCreationWindow_wnd");
//			ShowWindow(*hWnd, true);
//			hWnd = HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd");
//			EnableWindow(*hWnd, false);
//		}
//		else
//		{
//			ContainerCreationWindow::create_containerCreationWindow(GetModuleHandle(NULL));
//		}
//	}
//	else
//	{
//		ContainerCreationWindow::create_containerCreationWindow(GetModuleHandle(NULL));
//	}
//}
//
//void BookmarkManagerWindow::openButton_pressed()
//{
//	PWSTR lvText = new WCHAR[30000];
//	LVITEM lvitem;
//	HWND* hWnd;
//
//	hWnd = HandleManager::getHandleWnd(L"bookmarkManagerWindow_mainListView");
//	int lvIndex = ListView_GetNextItem(*hWnd, -1, LVNI_SELECTED);
//	ListView_GetItemText(*hWnd, lvIndex, NULL, lvText, 30000);
//
//	for (size_t i = 0; i < Archive::size(); i++)
//	{
//		auto container = Archive::getContainerByIndex(i);
//		std::wstring taskName(container->getContent(ContainerDataTypes::NAME));
//		std::wstring selectedName(lvText);
//
//		if (taskName == selectedName)
//		{
//			container->start();
//		}
//	}
//
//	delete[] lvText;
//}


void BookmarkManagerWindow::adjustmentOfControls(HWND hWnd)
{
	CheckList ñheckList;
	ñheckList.push_back(NAME_BOOKMARKMANAGERNWND_MainListView);
	ñheckList.push_back(NAME_BOOKMARKMANAGERNWND_AddButton);
	ñheckList.push_back(NAME_BOOKMARKMANAGERNWND_OpenButton);
	ñheckList.push_back(NAME_BOOKMARKMANAGERNWND_ClearButton);

	if (HandleManager::checkExistence(ñheckList))
	{
		HWND hMainListView = HandleManager::getHandleWnd(NAME_BOOKMARKMANAGERNWND_MainListView);
		HWND hAddButton = HandleManager::getHandleWnd(NAME_BOOKMARKMANAGERNWND_AddButton);
		HWND hOpenButton = HandleManager::getHandleWnd(NAME_BOOKMARKMANAGERNWND_OpenButton);
		HWND hCleanButton = HandleManager::getHandleWnd(NAME_BOOKMARKMANAGERNWND_ClearButton);

		SetWindowPos(hMainListView, HWND_TOP, BookmarkManagerWnd_mainListView_X,
			BookmarkManagerWnd_mainListView_Y,
			BookmarkManagerWnd_mainListView_WIDTH,
			BookmarkManagerWnd_mainListView_HEIGHT, NULL);
		SetWindowPos(hAddButton, HWND_TOP, BookmarkManagerWnd_addButton_X,
			BookmarkManagerWnd_addButton_Y,
			BookmarkManagerWnd_addButton_WIDTH,
			BookmarkManagerWnd_addButton_HEIGHT, NULL);
		SetWindowPos(hOpenButton, HWND_TOP, BookmarkManagerWnd_openButton_X,
			BookmarkManagerWnd_openButton_Y,
			BookmarkManagerWnd_openButton_WIDTH,
			BookmarkManagerWnd_openButton_HEIGHT, NULL);
		SetWindowPos(hCleanButton, HWND_TOP, BookmarkManagerWnd_cleanButton_X,
			BookmarkManagerWnd_cleanButton_Y,
			BookmarkManagerWnd_cleanButton_WIDTH,
			BookmarkManagerWnd_cleanButton_HEIGHT, NULL);
	}
}

//void BookmarkManagerWindow::showCreatedContainer(LPARAM lParam)
//{
//	LVITEM lvitem = { NULL };
//	lvitem.mask = LVIF_TEXT;
//
//	Container* container = Archive::getContainerByID(lParam);
//	lvitem.pszText = container->getContent(ContainerDataTypes::NAME);
//
//	HWND* hWnd = HandleManager::getHandleWnd(L"bookmarkManagerWindow_mainListView");
//	ListView_InsertItem(*hWnd, &lvitem);
//}
