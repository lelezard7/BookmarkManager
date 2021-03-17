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
			int lvIndex = ListView_GetNextItem(hMainLV, -1, LVNI_SELECTED);
			if (lvIndex != -1)
			{
				if (Archive::delContainerByIndex(lvIndex))
					ListView_DeleteItem(hMainLV, lvIndex);
				else
					debugMessage(L"Failed to delete container");
			}

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
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(BKM_ABOUTWND), hWnd, AboutProgramWindow::DlgProc);
			return 0;
		}

		case ID_FILE_SETTINGS: {
			SettingsProgramWindow::create_settingsProgramWindow(GetModuleHandle(NULL), hWnd);
			return 0;
		}

		case ID_HELP_HOWTOUSE: {
			HWND hHelpWnd = HtmlHelp(hWnd, L"BookmarkManager.chm", HH_DISPLAY_TOPIC, NULL);
			if (!hHelpWnd)
				debugMessage(L"Couldn't open .chm file");
			CommonOperations::moveWindowToCenterScreen(hHelpWnd);
			return 0;
		}

		}
		return 0;
	}

	case UM_SHOWCREATEDCONTAINER: {
		showCreatedContainer(lParam);
		return 0;
	}

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

	CommonOperations::moveWindowToCenterScreen(hWnd);

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

	HandleManager::addHandleWnd(hWnd, HNAME_BOOKMARKMANAGERWND_MainListView);

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

	ContainerCreationWindow::create_containerCreationWindow(GetModuleHandle(NULL));
}

void BookmarkManagerWindow::openButton_pressed()
{
	//PWSTR lvText = new WCHAR[30000];
	//LVITEM lvitem;

	//HWND hWnd = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MainListView);
	//int lvIndex = ListView_GetNextItem(hWnd, -1, LVNI_SELECTED);
	//ListView_GetItemText(hWnd, lvIndex, NULL, lvText, 30000);

	//for (size_t i = 0; i < Archive::size(); i++)
	//{
	//	auto container = Archive::getContainerByIndex(i); //TODO: Если есть два контейнера с одинаковыми именами
	//	//то будет выбран первый попавшийся элемент.
	//	std::wstring taskName(container->getContent(ContainerDataTypes::NAME));
	//	std::wstring selectedName(lvText);

	//	if (taskName == selectedName)
	//	{
	//		container->start();
	//	}
	//}

	//delete[] lvText;
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

void BookmarkManagerWindow::showCreatedContainer(LPARAM lParam)
{
	//LVITEM lvitem = { NULL };
	//lvitem.mask = LVIF_TEXT;

	//Container* container = Archive::getContainerByID(lParam);
	//lvitem.pszText = container->getContent(ContainerDataTypes::NAME);

	//HWND hWnd = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MainListView);
	//ListView_InsertItem(hWnd, &lvitem);
}
