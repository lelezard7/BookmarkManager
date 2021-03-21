#define UNICODE

#include "..\..\ApplicationSettings\ApplicationSettings.h"
#include "..\..\Common\PositionAndSizeControls.h"
#include "..\..\HandleManager\HandleManager.h"
#include "..\..\Archive\Archive.h"
#include "..\..\Common\BkmDef.h"
#include "..\..\Common\Debug.h"
#include "..\..\res\res.h"
#include "..\ContainerCreationWindow\ContainerCreationWindow.h"
#include "..\AboutProgramWindow\AboutProgramWindow.h"
#include "BookmarkManagerEvents.h"
#include <CommCtrl.h>
#include <HtmlHelp.h>


static size_t mainListView_getSelectedId()
{
	HWND hWnd = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);
	size_t index = ListView_GetNextItem(hWnd, -1, LVNI_SELECTED);

	PWSTR buffer_id = new WCHAR[0xF4240];  //TODO: ������� ���������� ����������� �������� �� ���� ���������.
	ListView_GetItemText(hWnd, index, 0, buffer_id, 0xF4240);

	size_t id = std::stoull(buffer_id);
	delete[] buffer_id;

	return id;
}

LRESULT bkmManagerWnd_adjustmentControls(HWND hWnd)
{
	HWND hMainListView = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);
	HWND hAddButton = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_ADDBUTTON);
	HWND hOpenButton = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_OPENBUTTON);
	HWND hClearButton = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_CLEARBUTTON);

	SetWindowPos(hMainListView, HWND_TOP, BookmarkManagerWnd_MainListView_X,
		BookmarkManagerWnd_MainListView_Y,
		BookmarkManagerWnd_MainListView_Width,
		BookmarkManagerWnd_MainListView_Height, NULL);
	SetWindowPos(hAddButton, HWND_TOP, BookmarkManagerWnd_AddButton_X,
		BookmarkManagerWnd_AddButton_Y,
		BookmarkManagerWnd_AddButton_Width,
		BookmarkManagerWnd_AddButton_Height, NULL);
	SetWindowPos(hOpenButton, HWND_TOP, BookmarkManagerWnd_OpenButton_X,
		BookmarkManagerWnd_OpenButton_Y,
		BookmarkManagerWnd_OpenButton_Width,
		BookmarkManagerWnd_OpenButton_Height, NULL);
	SetWindowPos(hClearButton, HWND_TOP, BookmarkManagerWnd_ClearButton_X,
		BookmarkManagerWnd_ClearButton_Y,
		BookmarkManagerWnd_ClearButton_Width,
		BookmarkManagerWnd_ClearButton_Height, NULL);

	return 0;
}

LRESULT showCreatedContainer(WPARAM wParam)
{
	HWND hWnd = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);

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

	return 0;
}



LRESULT bkmManagerWnd_ClearMainListView(HWND hWnd)
{
	HWND hMainLv = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);

	if (ListView_GetItemCount(hMainLv) == 0)
		return 0;

	if (MessageBox(hWnd, L"�� ������������� ������ �������� ���� ������?",
		L"Bookmark Manager", MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		ListView_DeleteAllItems(hMainLv);
		Archive::clear();
	}

	return 0;
}

LRESULT bkmManagerWnd_start�ontainer(HWND hWnd)
{
	HWND hMainLv = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);
	size_t index = ListView_GetNextItem(hMainLv, -1, LVNI_SELECTED);

	if (index == -1)
		return 0;

	Archive_Id id = mainListView_getSelectedId();
	Container* container = Archive::getContainer(id);

	if (!container) {
		std::wstring errMessage = L"�� ������� ��������� ���������. ��������� � ID: " +
			std::to_wstring(id) + L" �� ������!";
		MessageBox(hWnd, errMessage.c_str(), L"Bookmark Manager", MB_OK | MB_ICONWARNING);

		return 0;
	}

	container->start();

	return 0;
}

LRESULT bkmManagerWnd_delete_pressed(HWND hWnd)
{
	HWND hMainLv = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MAINLISTVIEW);
	size_t index = ListView_GetNextItem(hMainLv, -1, LVNI_SELECTED);

	if (index == -1)
		return 0;

	Archive_Id id = mainListView_getSelectedId();

	if (Archive::deleteContainer(id)) {
		ListView_DeleteItem(hMainLv, index);
	}
	else {
		std::wstring errMessage = L"�� ������� ������� ���������. ��������� � ID: " +
			std::to_wstring(id) + L" �� ������!";
		MessageBox(hWnd, errMessage.c_str(), L"Bookmark Manager", MB_OK | MB_ICONWARNING);
	}

	return 0;
}

LRESULT bkmManagerWnd_addButton_pressed(HWND hWnd)
{
	LaunchMethod launchMethod = ApplicationSettings::getLaunchMethodContainerCreationWindow();

	if (launchMethod == LaunchMethod::SHOW_CLOSED_WINDOW ||
		launchMethod == LaunchMethod::CONTINUE_UNFINISHED_CREATION)
	{
		if (HandleManager::checkExistence(HNAME_CONTAINERCREATIONWND_WND))
		{
			HWND hContCreatWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND);
			ShowWindow(hContCreatWnd, true);

			EnableWindow(hWnd, false);

			return 0;
		}
	}

	create_containerCreationWindow(GetModuleHandle(NULL));

	return 0;
}



LRESULT bkmManagerWnd_menu_help_howToUse(HWND hWnd)
{
	HWND hHelpWnd = HtmlHelp(hWnd, L"BookmarkManager.chm", HH_DISPLAY_TOPIC, NULL);

	if (hHelpWnd) {
		moveWindowToCenterScreen(hHelpWnd);
		return 0;
	}

	size_t length = GetCurrentDirectory(NULL, NULL);
	PWSTR buffer = new WCHAR[length];

	GetCurrentDirectory(length, buffer);
	std::wstring errMessage = L"�� ������� ����� ���� �������: \"" + std::wstring(buffer) +
		L"\\BookmarkManager.chm\"";
	delete[] buffer;

	MessageBox(hWnd, errMessage.c_str(), L"Bookmark Manager", MB_OK | MB_ICONWARNING);

	return 0;
}

LRESULT bkmManagerWnd_menu_help_aboutProg(HWND hWnd)
{
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(BKM_ABOUTWND), hWnd, AboutProc);

	return 0;
}

LRESULT bkmManagerWnd_menu_file_close(HWND hWnd)
{
	PostMessage(hWnd, WM_CLOSE, NULL, NULL);

	return 0;
}



LRESULT bkmManagerWnd_closeProgram(HWND hWnd)
{
	DestroyWindow(hWnd);

	return 0;
}

LRESULT bkmManagerWnd_destroyWindow()
{
	PostQuitMessage(0);

	return 0;
}
