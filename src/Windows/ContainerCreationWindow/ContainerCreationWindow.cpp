#define UNICODE

#include "..\..\ApplicationSettings\ApplicationSettings.h"
#include "..\..\Common\PositionAndSizeControls.h"
#include "..\..\Archive\TaskTypesCollection.h"
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
		case BKM_ID_DELETE:	return contCreatWnd_delete_pressed();
		case BKM_ID_TAB:	return contCreatWnd_tab_pressed();
		}
	}

	default:	return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}



static void create_taskTypeComboBox(HWND hWndParent, HINSTANCE);
static void create_nameTextBox(HWND hWndParent, HINSTANCE);
static void create_taskTextBox(HWND hWndParent, HINSTANCE);
static void create_tagsTextBox(HWND hWndParent, HINSTANCE);
static void create_applyButton(HWND hWndParent, HINSTANCE);
static void create_tagsListView(HWND hWndParent, HINSTANCE);
static void create_applyTagButton(HWND hWndParent, HINSTANCE);
static void create_taskTypeHelpText(HWND hWndParent, HINSTANCE);

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

static void create_taskTypeComboBox(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"COMBOBOX",
		NULL,
		WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
		ContainerCreationWnd_TaskTypeComboBox_X,
		ContainerCreationWnd_TaskTypeComboBox_Y,
		ContainerCreationWnd_TaskTypeComboBox_Width,
		ContainerCreationWnd_TaskTypeComboBox_Height,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_TASKTYPECOMBOBOX);

	fillComboBoxTaskTypes(hWnd);

	TaskType DefaultTaskType = ApplicationSettings::getDefaultTaskType();
	if (DefaultTaskType != TASKTYPE_NOTSPECIFIED)
		SendMessage(hWnd, CB_SETCURSEL, DefaultTaskType, NULL);
}

static void create_nameTextBox(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
		ContainerCreationWnd_NameTextBox_X,
		ContainerCreationWnd_NameTextBox_Y,
		ContainerCreationWnd_NameTextBox_Width,
		ContainerCreationWnd_NameTextBox_Height,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_NAMETEXTBOX);

	SendMessage(hWnd, EM_SETCUEBANNER, false, (LPARAM)L"Название");
}

static void create_taskTextBox(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
		ContainerCreationWnd_TaskTextBox_X,
		ContainerCreationWnd_TaskTextBox_Y,
		ContainerCreationWnd_TaskTextBox_Width,
		ContainerCreationWnd_TaskTextBox_Height,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_TASKTEXTBOX);

	SendMessage(hWnd, EM_SETLIMITTEXT, 0, NULL);
	SendMessage(hWnd, EM_SETCUEBANNER, false, (LPARAM)L"Задача");
}

static void create_tagsTextBox(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
		ContainerCreationWnd_TagsTextBox_X,
		ContainerCreationWnd_TagsTextBox_Y,
		ContainerCreationWnd_TagsTextBox_Width,
		ContainerCreationWnd_TagsTextBox_Height,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_TAGSTEXTBOX);

	SendMessage(hWnd, EM_SETCUEBANNER, false, (LPARAM)L"Тег");
}

static void create_applyButton(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"BUTTON",
		L"Принять",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		ContainerCreationWnd_ApplyButton_X,
		ContainerCreationWnd_ApplyButton_Y,
		ContainerCreationWnd_ApplyButton_Width,
		ContainerCreationWnd_ApplyButton_Height,
		hWndParent,
		(HMENU)ID_CONTAINERCREATIONWND_APPLYBUTTON,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_APPLYBUTTON);
}

static void create_tagsListView(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		WC_LISTVIEW,
		NULL,
		WS_CHILD | WS_VISIBLE | LVS_REPORT,
		ContainerCreationWnd_TagsListView_X,
		ContainerCreationWnd_TagsListView_Y,
		ContainerCreationWnd_TagsListView_Width,
		ContainerCreationWnd_TagsListView_Height,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	ListView_SetExtendedListViewStyleEx(hWnd, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_TAGSLISTVIEW);

	LVCOLUMN lvcolumn;
	lvcolumn.mask = LVCF_WIDTH | LVCF_TEXT;
	lvcolumn.cx = ContainerCreationWnd_TagsListView_Width;
	lvcolumn.pszText = (LPWSTR)L"Тег";

	ListView_InsertColumn(hWnd, 1, &lvcolumn);
}

static void create_applyTagButton(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"BUTTON",
		L">>",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		ContainerCreationWnd_ApplyTagButton_X,
		ContainerCreationWnd_ApplyTagButton_Y,
		ContainerCreationWnd_ApplyTagButton_Width,
		ContainerCreationWnd_ApplyTagButton_Height,
		hWndParent,
		(HMENU)ID_CONTAINERCREATIONWND_APPLYTAGBUTTON,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_APPLYTAGBUTTON);
}

static void create_taskTypeHelpText(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"STATIC",
		L"Тип задачи:",
		WS_VISIBLE | WS_CHILD,
		ContainerCreationWnd_TaskTypeHelpText_X,
		ContainerCreationWnd_TaskTypeHelpText_Y,
		ContainerCreationWnd_TaskTypeHelpText_Width,
		ContainerCreationWnd_TaskTypeHelpText_Height,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_TASKTYPEHELPTEXT);
}
