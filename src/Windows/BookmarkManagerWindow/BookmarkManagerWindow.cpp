//TODO: изменить GetModuleHandle() на GetModuleHandleEx()

#define UNICODE

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
#include "..\..\res\res.h"
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

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case BKM_ID_DELETE: {
			HWND hMainLV = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MainListView);
			size_t lvIndex = ListView_GetNextItem(hMainLV, -1, LVNI_SELECTED);

			if (lvIndex == -1)
				return 0;

			Archive_Id id = mainLV_getSelectedId();

			if (Archive::deleteContainer(id))
				ListView_DeleteItem(hMainLV, lvIndex);
			//else
			//	MessageBox() //TODO: Выдать ошибку
			return 0;
		}

		case BKM_ID_ENTER: {
			openButton_pressed();
			return 0;
		}

		case ID_BOOKMARKMANAGERWND_CLEARBUTTON: {
			HWND hMainListView = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MainListView);

			if (ListView_GetItemCount(hMainListView) != 0)
			{
				if (MessageBox(hWnd, L"Do you really want to clear the list? This will remove all items!",
					L"Remove All", MB_OKCANCEL | MB_ICONWARNING) == IDOK)
				{
					ListView_DeleteAllItems(hMainListView);
					Archive::clear();
				}
			}
			return 0;
		}

		case ID_BOOKMARKMANAGERWND_ADDBUTTON: {
			addButton_pressed();
			return 0;
		}

		case ID_BOOKMARKMANAGERWND_OPENBUTTON: {
			openButton_pressed();
			return 0;
		}

		case ID_FILE_CLOSE: {
			PostMessage(hWnd, WM_CLOSE, NULL, NULL);
			return 0;
		}

		case ID_HELP_ABOUTBOOKMARKMANAGER: {
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(BKM_ABOUTWND), hWnd, AboutProc);
			return 0;
		}

		case ID_FILE_SETTINGS: {
			create_settingsProgramWindow(GetModuleHandle(NULL), hWnd);
			return 0;
		}

		case ID_HELP_HOWTOUSE: {
			HWND hHelpWnd = HtmlHelp(hWnd, L"BookmarkManager.chm", HH_DISPLAY_TOPIC, NULL);
			if (!hHelpWnd)
				debugMessage(L"Couldn't open .chm file");
			moveWindowToCenterScreen(hHelpWnd);
			return 0;
		}

		}
		return 0;
	}

	case UM_SHOWCREATEDCONTAINER: {
		showCreatedContainer(wParam);
		return 0;
	}

	case WM_GETMINMAXINFO: {
		setMinimumWindowSize(350, 400, lParam);
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
		CLASSNAME_BOOKMARKMANAGERWND,
		WNDNAME_BOOKMARKMANAGERNWND,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 650,
		NULL,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_BOOKMARKMANAGERWND_WND);

	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(BKM_MENU));
	SetMenu(hWnd, hMenu);

	create_mainListView(hWnd, hInstance);
	create_addButton(hWnd, hInstance);
	create_openButton(hWnd, hInstance);
	create_clearButton(hWnd, hInstance);

	moveWindowToCenterScreen(hWnd);

	return hWnd;
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

	ListView_SetExtendedListViewStyleEx(hWnd, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	HandleManager::addHandleWnd(hWnd, HNAME_BOOKMARKMANAGERWND_MainListView);

	LVCOLUMN lvcolumn;
	lvcolumn.mask = LVCF_WIDTH | LVCF_TEXT;

	lvcolumn.cx = 40;
	lvcolumn.pszText = (LPWSTR)L"ID";
	ListView_InsertColumn(hWnd, 1, &lvcolumn);

	lvcolumn.cx = 215;
	lvcolumn.pszText = (LPWSTR)L"Name";
	ListView_InsertColumn(hWnd, 2, &lvcolumn);

	lvcolumn.pszText = (LPWSTR)L"Task";
	ListView_InsertColumn(hWnd, 3, &lvcolumn);
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
		(HMENU)ID_BOOKMARKMANAGERWND_ADDBUTTON,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_BOOKMARKMANAGERWND_AddButton);
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
		(HMENU)ID_BOOKMARKMANAGERWND_OPENBUTTON,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_BOOKMARKMANAGERWND_OpenButton);
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
		(HMENU)ID_BOOKMARKMANAGERWND_CLEARBUTTON,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_BOOKMARKMANAGERWND_ClearButton);
}


void BookmarkManagerWindow::addButton_pressed()
{
	if (ApplicationSettings::getStartupMethodContainerCreationWindow() == StartupMethod::SHOW_CLOSED_WINDOW
		|| ApplicationSettings::getStartupMethodContainerCreationWindow() == StartupMethod::CONTINUE_UNFINISHED_CREATION)
	{
		if (HandleManager::checkExistence(HNAME_CONTAINERCREATIONWND_WND))
		{
			HWND hWnd;

			hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND);
			ShowWindow(hWnd, true);
			hWnd = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_WND);
			EnableWindow(hWnd, false);
			return;
		}
	}

	create_containerCreationWindow(GetModuleHandle(NULL));
}

void BookmarkManagerWindow::openButton_pressed()
{
	HWND hWnd = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MainListView);
	size_t lvIndex = ListView_GetNextItem(hWnd, -1, LVNI_SELECTED);

	if (lvIndex == -1)
		return;

	Archive_Id id = mainLV_getSelectedId();

	for (size_t i = 0; i < Archive::size(); i++)
	{
		Container* container = Archive::getContainer(id);
		if (container) {
			container->start();
			break;
		}
	}
}


void BookmarkManagerWindow::adjustmentOfControls(HWND hWnd)
{
	CheckList checkList;
	checkList.push_back(HNAME_BOOKMARKMANAGERWND_MainListView);
	checkList.push_back(HNAME_BOOKMARKMANAGERWND_AddButton);
	checkList.push_back(HNAME_BOOKMARKMANAGERWND_OpenButton);
	checkList.push_back(HNAME_BOOKMARKMANAGERWND_ClearButton);

	if (HandleManager::checkExistence(checkList))
	{
		HWND hMainListView = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MainListView);
		HWND hAddButton = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_AddButton);
		HWND hOpenButton = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_OpenButton);
		HWND hCleanButton = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_ClearButton);

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

void BookmarkManagerWindow::showCreatedContainer(WPARAM wParam)
{
	HWND hWnd = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MainListView);

	LVITEM lvitem = { NULL };
	lvitem.mask = LVIF_TEXT;

	std::wstring buffer = std::to_wstring(wParam);
	lvitem.pszText = (LPWSTR)buffer.c_str();
	ListView_InsertItem(hWnd, &lvitem);
	buffer.clear();

	Container* container = Archive::getContainer(wParam);
	lvitem.iSubItem = 1;
	lvitem.pszText = container->getName();
	ListView_SetItem(hWnd, &lvitem);

	lvitem.iSubItem = 2;
	lvitem.pszText = container->getTask();
	ListView_SetItem(hWnd, &lvitem);
}
