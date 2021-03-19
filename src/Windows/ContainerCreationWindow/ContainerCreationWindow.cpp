#define UNICODE

#include "..\..\ApplicationSettings\ApplicationSettings.h"
#include "..\..\Common\PositionAndSizeControls.h"
#include "..\..\Common\Debug.h"
#include "..\..\res\res.h"
#include "ContainerCreationWindow.h"
#include "ContainerCreationEvents.h"
#include <CommCtrl.h>


LRESULT CALLBACK ContainerCreatProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:			return contCreatWnd_initialization();
	case WM_SIZE:			return contCreatWnd_adjustmentControls();
	case WM_GETMINMAXINFO:	return !setMinimumWindowSize(350, 400, lParam);
	case WM_CTLCOLORSTATIC: return contCreatWnd_setColorStatic(wParam);
	case WM_CLOSE:			return contCreatWnd_closeWnd(hWnd, lParam);

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_CONTAINERCREATIONWND_APPLYBUTTON:		return contCreatWnd_fillContainer();
		case ID_CONTAINERCREATIONWND_APPLYTAGBUTTON:	return contCreatWnd_applyTag();

		case BKM_ID_ENTER:	return contCreatWnd_enter_pressed();
		case BKM_ID_TAB:	return contCreatWnd_tab_pressed();
		}
	}

	default:	return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}



static void create_taskTypeComboBox(HWND, HINSTANCE);
static void create_nameTextBox(HWND, HINSTANCE);
static void create_taskTextBox(HWND, HINSTANCE);
static void create_tagsTextBox(HWND, HINSTANCE);
static void create_applyButton(HWND, HINSTANCE);
static void create_tagsListView(HWND, HINSTANCE);
static void create_applyTagButton(HWND, HINSTANCE);
static void create_taskTypeHelpText(HWND, HINSTANCE);

void create_containerCreationWindow(HINSTANCE hInstance)
{
	HWND hWndParent = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_WND);

	HWND hWnd = CreateWindow(
		CLASSNAME_CONTAINERCREATIONWND,
		WNDNAME_CONTAINERCREATIONWND,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		600, 500,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_WND);

	create_taskTypeHelpText(hWnd, hInstance);
	create_taskTypeComboBox(hWnd, hInstance);
	create_nameTextBox(hWnd, hInstance);
	create_taskTextBox(hWnd, hInstance);
	create_tagsTextBox(hWnd, hInstance);
	create_applyTagButton(hWnd, hInstance);
	create_tagsListView(hWnd, hInstance);
	create_applyButton(hWnd, hInstance);

	moveWindowToCenterScreen(hWnd);

	ShowWindow(hWnd, true);
	EnableWindow(hWndParent, false);
}

void create_taskTypeComboBox(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"COMBOBOX",
		NULL,
		WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
		ContainerCreationWnd_taskTypeComboBox_X,
		ContainerCreationWnd_taskTypeComboBox_Y,
		ContainerCreationWnd_taskTypeComboBox_WIDTH,
		ContainerCreationWnd_taskTypeComboBox_HEIGHT,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_TaskTypeComboBox);

	fillComboBoxTaskTypes(hWnd);

	TaskTypes_Index_t DefaultTaskType = ApplicationSettings::getDefaultTaskType();
	if (DefaultTaskType != TASKTTYPE_NOTSPECIFIED)
		SendMessage(hWnd, CB_SETCURSEL, DefaultTaskType, NULL);
}

void create_nameTextBox(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
		ContainerCreationWnd_nameTextBox_X,
		ContainerCreationWnd_nameTextBox_Y,
		ContainerCreationWnd_nameTextBox_WIDTH,
		ContainerCreationWnd_nameTextBox_HEIGHT,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_NameTextBox);

	SendMessage(hWnd, EM_SETCUEBANNER, false, (LPARAM)L"Название");
}

void create_taskTextBox(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
		ContainerCreationWnd_taskTextBox_X,
		ContainerCreationWnd_taskTextBox_Y,
		ContainerCreationWnd_taskTextBox_WIDTH,
		ContainerCreationWnd_taskTextBox_HEIGHT,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_TaskTextBox);

	SendMessage(hWnd, EM_SETLIMITTEXT, 0, NULL);
	SendMessage(hWnd, EM_SETCUEBANNER, false, (LPARAM)L"Задача");
}

void create_tagsTextBox(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
		ContainerCreationWnd_tagsTextBox_X,
		ContainerCreationWnd_tagsTextBox_Y,
		ContainerCreationWnd_tagsTextBox_WIDTH,
		ContainerCreationWnd_tagsTextBox_HEIGHT,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_TagsTextBox);

	SendMessage(hWnd, EM_SETCUEBANNER, false, (LPARAM)L"Тег");
}

void create_applyButton(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"BUTTON",
		L"Принять",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		ContainerCreationWnd_applyButton_X,
		ContainerCreationWnd_applyButton_Y,
		ContainerCreationWnd_applyButton_WIDTH,
		ContainerCreationWnd_applyButton_HEIGHT,
		hWndParent,
		(HMENU)ID_CONTAINERCREATIONWND_APPLYBUTTON,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_ApplyButton);
}

void create_tagsListView(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		WC_LISTVIEW,
		NULL,
		WS_CHILD | WS_VISIBLE | LVS_REPORT,
		ContainerCreationWnd_tagsListView_X,
		ContainerCreationWnd_tagsListView_Y,
		ContainerCreationWnd_tagsListView_WIDTH,
		ContainerCreationWnd_tagsListView_HEIGHT,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	ListView_SetExtendedListViewStyleEx(hWnd, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_TagsListView);

	LVCOLUMN lvcolumn;
	lvcolumn.mask = LVCF_WIDTH | LVCF_TEXT;
	lvcolumn.cx = 250;
	lvcolumn.pszText = (LPWSTR)L"Тег";

	ListView_InsertColumn(hWnd, 1, &lvcolumn);
}

void create_applyTagButton(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"BUTTON",
		L">>",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		ContainerCreationWnd_applyTagButton_X,
		ContainerCreationWnd_applyTagButton_Y,
		ContainerCreationWnd_applyTagButton_WIDTH,
		ContainerCreationWnd_applyTagButton_HEIGHT,
		hWndParent,
		(HMENU)ID_CONTAINERCREATIONWND_APPLYTAGBUTTON,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_ApplyTagButton);
}

void create_taskTypeHelpText(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"STATIC",
		L"Тип задачи:",
		WS_VISIBLE | WS_CHILD,
		ContainerCreationWnd_taskTypeHelpText_X,
		ContainerCreationWnd_taskTypeHelpText_Y,
		ContainerCreationWnd_taskTypeHelpText_WIDTH,
		ContainerCreationWnd_taskTypeHelpText_HEIGHT,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_TaskTypeHelpText);
}
