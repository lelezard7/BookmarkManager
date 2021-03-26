//TODO: изменить GetModuleHandle() на GetModuleHandleEx()

#define UNICODE

#include "..\..\Common\PositionAndSizeControls.h"
#include "..\..\HandleManager\HandleManager.h"
#include "..\..\Common\Debug.h"
#include "..\..\res\res.h"
#include "..\SettingsProgramWindow\SettingsProgramWindow.h"
#include "BookmarkManagerWindow.h"
#include "BookmarkManagerEvents.h"
#include <CommCtrl.h>


LRESULT CALLBACK BkmManagerProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:					return bkmManagerWnd_adjustmentControls(hWnd);
	case WM_GETMINMAXINFO:			return !setMinimumWindowSize(350, 400, lParam);

	case UM_SHOWCREATEDCONTAINER:	return showCreatedContainer(wParam);

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_BOOKMARKMANAGERWND_CLEARBUTTON: return bkmManagerWnd_ClearMainListView(hWnd);
		case ID_BOOKMARKMANAGERWND_ADDBUTTON:	return bkmManagerWnd_addButton_pressed(hWnd);
		case ID_BOOKMARKMANAGERWND_OPENBUTTON:	return bkmManagerWnd_startСontainer(hWnd);

		case ID_FILE_CLOSE:					return bkmManagerWnd_menu_file_close(hWnd);
		case ID_HELP_ABOUTBOOKMARKMANAGER:	return bkmManagerWnd_menu_help_aboutProg(hWnd);
		case ID_FILE_SETTINGS:				return create_settingsProgramWindow(GetModuleHandle(NULL), hWnd);
		case ID_HELP_HOWTOUSE:				return bkmManagerWnd_menu_help_howToUse(hWnd);
		case ID_FILE_SAVE:					return bkmManagerWnd_menu_file_save();
		case ID_FILE_OPEN:					return bkmManagerWnd_menu_file_open();

		case BKM_ID_DELETE:	return bkmManagerWnd_delete_pressed(hWnd);
		case BKM_ID_ENTER:	return bkmManagerWnd_startСontainer(hWnd);
		}
	}

	case WM_CLOSE:		return bkmManagerWnd_closeProgram(hWnd);
	case WM_DESTROY:	return bkmManagerWnd_destroyWindow();

	default:	return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}



static void create_mainListView(HWND hWndParent, HINSTANCE);
static void create_addButton(HWND hWndParent, HINSTANCE);
static void create_openButton(HWND hWndParent, HINSTANCE);
static void create_clearButton(HWND hWndParent, HINSTANCE);

HWND create_bookmarkManagerWindow(HINSTANCE hInstance)
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

	create_mainListView(hWnd, hInstance);
	create_addButton(hWnd, hInstance);
	create_openButton(hWnd, hInstance);
	create_clearButton(hWnd, hInstance);

	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(BKM_MENU));
	SetMenu(hWnd, hMenu);

	moveWindowToCenterScreen(hWnd);

	return hWnd;
}

static void create_mainListView(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		WC_LISTVIEW,
		NULL,
		WS_CHILD | WS_VISIBLE | LVS_REPORT,
		BookmarkManagerWnd_MainListView_X,
		BookmarkManagerWnd_MainListView_Y,
		BookmarkManagerWnd_MainListView_Width,
		BookmarkManagerWnd_MainListView_Height,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	ListView_SetExtendedListViewStyleEx(hWnd,
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	HandleManager::addHandleWnd(hWnd, HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);

	LVCOLUMN lvcolumn;
	lvcolumn.mask = LVCF_WIDTH | LVCF_TEXT;

	lvcolumn.cx = 40;
	lvcolumn.pszText = (LPWSTR)L"ID";
	ListView_InsertColumn(hWnd, 1, &lvcolumn);

	lvcolumn.cx = BookmarkManagerWnd_MainListView_Width / 2;
	lvcolumn.pszText = (LPWSTR)L"Название";
	ListView_InsertColumn(hWnd, 2, &lvcolumn);

	lvcolumn.pszText = (LPWSTR)L"Задача";
	ListView_InsertColumn(hWnd, 3, &lvcolumn);
}

static void create_addButton(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"BUTTON",
		L"Добавить",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		BookmarkManagerWnd_AddButton_X,
		BookmarkManagerWnd_AddButton_Y,
		BookmarkManagerWnd_AddButton_Width,
		BookmarkManagerWnd_AddButton_Height,
		hWndParent,
		(HMENU)ID_BOOKMARKMANAGERWND_ADDBUTTON,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_BOOKMARKMANAGERWND_ADDBUTTON);
}

static void create_openButton(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"BUTTON",
		L"Открыть",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		BookmarkManagerWnd_OpenButton_X,
		BookmarkManagerWnd_OpenButton_Y,
		BookmarkManagerWnd_OpenButton_Width,
		BookmarkManagerWnd_OpenButton_Height,
		hWndParent,
		(HMENU)ID_BOOKMARKMANAGERWND_OPENBUTTON,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_BOOKMARKMANAGERWND_OPENBUTTON);
}

static void create_clearButton(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"BUTTON",
		L"Очистить",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		BookmarkManagerWnd_ClearButton_X,
		BookmarkManagerWnd_ClearButton_Y,
		BookmarkManagerWnd_ClearButton_Width,
		BookmarkManagerWnd_ClearButton_Height,
		hWndParent,
		(HMENU)ID_BOOKMARKMANAGERWND_CLEARBUTTON,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_BOOKMARKMANAGERWND_CLEARBUTTON);
}
