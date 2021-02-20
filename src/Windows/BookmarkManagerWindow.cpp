//TODO: ������� GetModuleHandle() �� GetModuleHandleEx()
//TODO: ���������� �� ������ ������

#ifndef UNICODE
#define UNICODE
#endif

#include "BookmarkManagerWindow.h"
#include "ContainerCreationWindow.h"
#include "AboutProgramWindow.h"
#include "..\Total\HandleManager.h"
#include "..\Total\BmDef.h"
#include "..\ApplicationSettings\ApplicationSettings.h"
#include "..\Total\GeneralOperations.h"
#include "..\Archive\Archive.h"
#include <CommCtrl.h>


LRESULT CALLBACK BookmarkManagerWindow::WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	HDC			hDC;
	PAINTSTRUCT	paintstruct;

	switch (msg)
	{
	case WM_PAINT: {
		hDC = BeginPaint(hWnd, &paintstruct);

		EndPaint(hWnd, &paintstruct);
		return 0;
	}

	case WM_SIZE: {
		/*		Resizes and positions controls.		*/
		adjustmentOfControls(hWnd);
		return 0;
	}

	case WM_COMMAND: {
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
			case ID_BOOKMARKMANAGERNWND_ADDBUTTON: {
				addButton_pressed();
				return 0;
			}

			case ID_BOOKMARKMANAGERNWND_OPENBUTTON: {
				openButton_pressed();
				return 0;
			}

			case ID_MENU_CLOSEPROGRAM: {
				PostMessage(hWnd, WM_CLOSE, NULL, NULL);
				return 0;
			}

			case ID_MENU_ABOUTPROGRAM: {
				AboutProgramWindow::create_aboutProgramWindow(GetModuleHandle(NULL));
				return 0;
			}
			}
		}
		return 0;
	}

	case UM_SHOWCREATEDCONTAINER: {
		showCreatedContainer(lParam);
		return 0;
	}

	case WM_GETMINMAXINFO: {
		GeneralOperations::setMinimumWindowSize(350, 400, lParam);
		return 0;
	}

	case WM_CLOSE: {
		DestroyWindow(hWnd); //TODO: ���������� � ���������� �����
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
	HMENU hMenu = create_menu();
	HWND* hWnd = HandleManager::addHandleWnd(L"bookmarkManagerWindow_wnd");

	*hWnd = CreateWindow(
		BOOKMARKMANAGERWND_CLASSNAME,
		BOOKMARKMANAGERNWND_WNDNAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 650,
		NULL,
		NULL,
		hInstance,
		NULL);

	SetMenu(*hWnd, hMenu);
	create_mainListView(*hWnd, hInstance);
	create_addButton(*hWnd, hInstance);
	create_openButton(*hWnd, hInstance);
	create_cleanButton(*hWnd, hInstance);

	GeneralOperations::moveWindowToCenterScreen(*hWnd);

	return *hWnd;
}


HMENU BookmarkManagerWindow::create_menu()
{
	HMENU	hMenuBar = CreateMenu();
	HMENU	hFilePopupMenu = CreatePopupMenu();
	HMENU	hHelpPopupMenu = CreatePopupMenu();

	AppendMenu(hMenuBar, MF_STRING | MF_POPUP, (UINT)hFilePopupMenu, L"����");
	{
		AppendMenu(hFilePopupMenu, MF_STRING, ID_MENU_SETTINGSPROGRAM, L"���������");
		AppendMenu(hFilePopupMenu, MF_STRING, ID_MENU_CLOSEPROGRAM, L"�������");
	}

	AppendMenu(hMenuBar, MF_STRING | MF_POPUP, (UINT)hHelpPopupMenu, L"�������");
	{
		AppendMenu(hHelpPopupMenu, MF_STRING, ID_MENU_HOWTOUSE, L"��� ������������");
		AppendMenu(hHelpPopupMenu, MF_STRING, ID_MENU_ABOUTPROGRAM, L"� ���������");
	}

	return hMenuBar;
}

void BookmarkManagerWindow::create_mainListView(HWND hWndParent, HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(hWndParent, &rect);

	HWND* hListView = HandleManager::addHandleWnd(L"bookmarkManagerWindow_mainListView");

	*hListView = CreateWindow(
		WC_LISTVIEW,
		NULL,
		WS_CHILD | WS_VISIBLE | LVS_REPORT,
		5, 5,
		rect.right - 10, rect.bottom - 50,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	LVCOLUMN lvcolumn;
	lvcolumn.mask = LVCF_WIDTH | LVCF_TEXT;
	lvcolumn.cx = 250;
	lvcolumn.pszText = (LPWSTR)L"Name";

	ListView_InsertColumn(*hListView, 1, &lvcolumn);
}

void BookmarkManagerWindow::create_addButton(HWND hWndParent, HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(hWndParent, &rect);

	HWND* hButton = HandleManager::addHandleWnd(L"bookmarkManagerWindow_addButton");

	*hButton = CreateWindow(
		L"BUTTON",
		L"��������",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		rect.right - 107, rect.bottom - 40,
		100, 25,
		hWndParent,
		(HMENU)ID_BOOKMARKMANAGERNWND_ADDBUTTON,
		hInstance,
		NULL);
}

void BookmarkManagerWindow::create_openButton(HWND hWndParent, HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(hWndParent, &rect);

	HWND* hButton = HandleManager::addHandleWnd(L"bookmarkManagerWindow_openButton");

	*hButton = CreateWindow(
		L"BUTTON",
		L"�������",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		rect.left + 7, rect.bottom - 40,
		100, 25,
		hWndParent,
		(HMENU)ID_BOOKMARKMANAGERNWND_OPENBUTTON,
		hInstance,
		NULL);
}

void BookmarkManagerWindow::create_cleanButton(HWND hWndParent, HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(hWndParent, &rect);

	HWND* hButton = HandleManager::addHandleWnd(L"bookmarkManagerWindow_cleanButton");

	*hButton = CreateWindow(
		L"BUTTON",
		L"��������",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		rect.left + 112, rect.bottom - 40,
		100, 25,
		hWndParent,
		(HMENU)ID_BOOKMARKMANAGERNWND_CLEANBUTTON,
		hInstance,
		NULL);
}


void BookmarkManagerWindow::addButton_pressed()
{
	if (ApplicationSettings::getStartupMethodContainerCreationWindow() == StartupMethod::SHOW_CLOSED_WINDOW)
	{
		if (HandleManager::checkExistence(L"containerCreationWindow_wnd"))
		{
			HWND* hWnd;

			hWnd = HandleManager::getHandleWnd(L"containerCreationWindow_wnd");
			ShowWindow(*hWnd, true);
			hWnd = HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd");
			EnableWindow(*hWnd, false);
		}
		else
		{
			ContainerCreationWindow::create_containerCreationWindow(GetModuleHandle(NULL));
		}
	}
	else
	{
		ContainerCreationWindow::create_containerCreationWindow(GetModuleHandle(NULL));
	}
}

void BookmarkManagerWindow::openButton_pressed()
{
	PWSTR lvText = new WCHAR[30000];
	LVITEM lvitem;
	HWND* hWnd;

	hWnd = HandleManager::getHandleWnd(L"bookmarkManagerWindow_mainListView");
	int lvIndex = ListView_GetNextItem(*hWnd, -1, LVNI_SELECTED);
	ListView_GetItemText(*hWnd, lvIndex, NULL, lvText, 30000);

	for (size_t i = 0; i < Archive::size(); i++)
	{
		auto container = Archive::getContainerByIndex(i);
		std::wstring taskName(container->getContent(ContainerDataTypes::NAME));
		std::wstring selectedName(lvText);

		if (taskName == selectedName)
		{
			STARTUPINFO startupinfo;
			ZeroMemory(&startupinfo, sizeof(STARTUPINFO));
			PROCESS_INFORMATION pi;
			if (CreateProcess(L"Z:\\OperaGX\\launcher.exe", NULL, NULL, NULL, false, NULL, NULL, NULL, &startupinfo, &pi))
			{
				Sleep(1000);
				TerminateProcess(pi.hProcess, NO_ERROR);
			}
		}
	}

	delete[] lvText;
}

void BookmarkManagerWindow::adjustmentOfControls(HWND hWnd)
{
	HandleName �hecklist[]{ L"bookmarkManagerWindow_mainListView", L"bookmarkManagerWindow_addButton",
								L"bookmarkManagerWindow_openButton", L"bookmarkManagerWindow_cleanButton",
								L"\0" };

	if (HandleManager::checkExistence(�hecklist))
	{
		RECT	rect;
		GetClientRect(hWnd, &rect);

		HWND* hMainListView = HandleManager::getHandleWnd(L"bookmarkManagerWindow_mainListView");
		HWND* hAddButton = HandleManager::getHandleWnd(L"bookmarkManagerWindow_addButton");
		HWND* hOpenButton = HandleManager::getHandleWnd(L"bookmarkManagerWindow_openButton");
		HWND* hCleanButton = HandleManager::getHandleWnd(L"bookmarkManagerWindow_cleanButton");

		SetWindowPos(*hMainListView, HWND_TOP, NULL, NULL, rect.right - 10, rect.bottom - 50, SWP_NOMOVE);
		SetWindowPos(*hAddButton, HWND_TOP, rect.right - 107, rect.bottom - 40, NULL, NULL, SWP_NOSIZE);
		SetWindowPos(*hOpenButton, HWND_TOP, rect.left + 7, rect.bottom - 40, NULL, NULL, SWP_NOSIZE);
		SetWindowPos(*hCleanButton, HWND_TOP, rect.left + 112, rect.bottom - 40, NULL, NULL, SWP_NOSIZE);
	}
}

void BookmarkManagerWindow::showCreatedContainer(LPARAM lParam)
{
	LVITEM lvitem = { NULL };
	lvitem.mask = LVIF_TEXT;

	Container* container = Archive::getContainerByID(lParam);
	lvitem.pszText = container->getContent(ContainerDataTypes::NAME);

	HWND* hWnd = HandleManager::getHandleWnd(L"bookmarkManagerWindow_mainListView");
	ListView_InsertItem(*hWnd, &lvitem);
}
