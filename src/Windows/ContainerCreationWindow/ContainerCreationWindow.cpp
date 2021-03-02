#define UNICODE

#include "ContainerCreationWindow.h"
#include "..\..\Common\BkmDef.h"
#include "..\..\ApplicationSettings\ApplicationSettings.h"
#include "..\..\Common\CommonOperations.h"
#include "..\..\Common\PositionAndSizeControls.h"
#include <CommCtrl.h>


LRESULT CALLBACK ContainerCreationWindow::WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE: {
		adjustmentOfControls();
		return 0;
	}

	case WM_GETMINMAXINFO: {	
		CommonOperations::setMinimumWindowSize(350, 400, lParam);
		return 0;
	}

	case WM_COMMAND: {
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
			case ID_CONTAINERCREATIONWND_APPLYBUTTON: {
				fill_container();
				return 0;
			}
			}
		}
		return 0;
	}

	case WM_CLOSE: {
		return close_window(hWnd);
	}

	default: {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
}

void ContainerCreationWindow::create_containerCreationWindow(HINSTANCE hInstance)
{
	HWND hWndParent = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERNWND_WND);

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

	create_taskTypeDropDList(hWnd, hInstance);
	create_applyButton(hWnd, hInstance);
	create_nameTextBox(hWnd, hInstance);
	create_adressTextBox(hWnd, hInstance);
	create_tagsTextBox(hWnd, hInstance);
	create_tagsListView(hWnd, hInstance);

	CommonOperations::moveWindowToCenterScreen(hWnd);

	ShowWindow(hWnd, true);
	EnableWindow(hWndParent, false);
}


void ContainerCreationWindow::create_taskTypeDropDList(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"COMBOBOX",
		NULL,
		WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
		ContainerCreationWnd_taskTypeDropDList_X,
		ContainerCreationWnd_taskTypeDropDList_Y,
		ContainerCreationWnd_taskTypeDropDList_WIDTH,
		ContainerCreationWnd_taskTypeDropDList_HEIGHT,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_TaskTypeDropDList);

	SendMessage(hWnd, CB_INSERTSTRING, -1, (LPARAM)L"URL");
	SendMessage(hWnd, CB_INSERTSTRING, -1, (LPARAM)L"Program");
	//SendMessage(hWnd, CB_SETCURSEL, 0, NULL); //TODO: Сделать зависимость от настроек и блокировку
	//кнопки Принять в случае нулевого выбора.
}

void ContainerCreationWindow::create_nameTextBox(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | WS_TABSTOP, //TODO: WS_TABSTOP не работает
		ContainerCreationWnd_nameTextBox_X,
		ContainerCreationWnd_nameTextBox_Y,
		ContainerCreationWnd_nameTextBox_WIDTH,
		ContainerCreationWnd_nameTextBox_HEIGHT,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_NameTextBox);

	SendMessage(hWnd, EM_SETCUEBANNER, false, (LPARAM)L"Name");
}

void ContainerCreationWindow::create_adressTextBox(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | WS_TABSTOP,
		ContainerCreationWnd_adressTextBox_X,
		ContainerCreationWnd_adressTextBox_Y,
		ContainerCreationWnd_adressTextBox_WIDTH,
		ContainerCreationWnd_adressTextBox_HEIGHT,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_AdressTextBox);

	SendMessage(hWnd, EM_SETLIMITTEXT, 0, NULL);
	SendMessage(hWnd, EM_SETCUEBANNER, false, (LPARAM)L"Adress");
}

void ContainerCreationWindow::create_tagsTextBox(HWND hWndParent, HINSTANCE hInstance)
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

	SendMessage(hWnd, EM_SETCUEBANNER, false, (LPARAM)L"Tag");
}

void ContainerCreationWindow::create_applyButton(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"BUTTON",
		L"Apply",
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

void ContainerCreationWindow::create_tagsListView(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		WC_LISTVIEW,
		NULL,
		WS_CHILD | WS_VISIBLE | LVS_EDITLABELS | LVS_REPORT, //TODO: Удалить LVS_EDITLABELS ?
		ContainerCreationWnd_tagsListView_X,
		ContainerCreationWnd_tagsListView_Y,
		ContainerCreationWnd_tagsListView_WIDTH,
		ContainerCreationWnd_tagsListView_HEIGHT,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	HandleManager::addHandleWnd(hWnd, HNAME_CONTAINERCREATIONWND_TagsListView);

	LVCOLUMN lvcolumn;
	lvcolumn.mask = LVCF_WIDTH | LVCF_TEXT;
	lvcolumn.cx = 250;
	lvcolumn.pszText = (LPWSTR)L"Tag";

	ListView_InsertColumn(hWnd, 1, &lvcolumn);
}


void ContainerCreationWindow::fill_container()
{
	HWND	hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeDropDList);
	Container	container;

	//		We write down the value of the taskTypeDropDList in the container.
	size_t	length = GetWindowTextLength(hWnd) + (size_t)1;
	PWSTR	content = new WCHAR[length];
	GetWindowText(hWnd, content, length);

	if (!std::wcscmp(content, L"URL"))
	{
		container.setTaskType(TaskTypes::URL);
	}
	else if (!std::wcscmp(content, L"Program"))
	{
		container.setTaskType(TaskTypes::PROGRAM);
	}
	delete[] content;
	content = nullptr;

	//		We write down the values of the nameTextBox and adressTextBox in the container.
	bool errorCode_nameTB = setDataFromTextBox(HNAME_CONTAINERCREATIONWND_NameTextBox, ContainerDataTypes::NAME, container);
	bool errorCode_adressTB = setDataFromTextBox(HNAME_CONTAINERCREATIONWND_AdressTextBox, ContainerDataTypes::TASK, container);

	/*
	*		If nameTextBox or adressTextBox is not full.
	*		You can break the code this way only until you add the container to the archive!
	*/
	if (!(errorCode_nameTB && errorCode_adressTB))
	{
		container.clear();
		hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND);
		MessageBox(NULL, L"The \"Name\" and \"Task\" fields must be filled!", L"Input Error", MB_OK | MB_ICONWARNING);
		return;
	}

	ID id = Archive::addContainer(container);

	hWnd = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERNWND_WND);
	SendMessage(hWnd, UM_SHOWCREATEDCONTAINER, NULL, id);
	hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND);
	SendMessage(hWnd, WM_CLOSE, NULL, NULL);
}

bool ContainerCreationWindow::setDataFromTextBox(HandleName hTextBoxName, ContainerDataTypes dataType, Container& container)
{
	HWND	hWnd = HandleManager::getHandleWnd(hTextBoxName);
	size_t	length = GetWindowTextLength(hWnd) + (size_t)1;
	PWSTR	content = new WCHAR[length];

	GetWindowText(hWnd, content, length);
	container.setContent(dataType, content, length);
	delete[] content;

	return (length == 1)? false : true;
}

void ContainerCreationWindow::adjustmentOfControls()
{
	CheckList сheckList;
	сheckList.push_back(HNAME_CONTAINERCREATIONWND_NameTextBox);
	сheckList.push_back(HNAME_CONTAINERCREATIONWND_AdressTextBox);
	сheckList.push_back(HNAME_CONTAINERCREATIONWND_TagsTextBox);
	сheckList.push_back(HNAME_CONTAINERCREATIONWND_ApplyButton);
	сheckList.push_back(HNAME_CONTAINERCREATIONWND_TagsListView);
	сheckList.push_back(HNAME_CONTAINERCREATIONWND_TaskTypeDropDList);
	
	if (HandleManager::checkExistence(сheckList))
	{
		HWND hApplyButton = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_ApplyButton);
		HWND hNameTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_NameTextBox);
		HWND hAdressTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_AdressTextBox);
		HWND hTagsTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsTextBox);
		HWND hTagsListView = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsListView);
		HWND hTaskTypeDropDList = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeDropDList);

		SetWindowPos(hApplyButton, HWND_TOP, ContainerCreationWnd_applyButton_X,
			ContainerCreationWnd_applyButton_Y,
			ContainerCreationWnd_applyButton_WIDTH,
			ContainerCreationWnd_applyButton_HEIGHT, NULL);
		SetWindowPos(hNameTextBox, HWND_TOP, ContainerCreationWnd_nameTextBox_X,
			ContainerCreationWnd_nameTextBox_Y,
			ContainerCreationWnd_nameTextBox_WIDTH,
			ContainerCreationWnd_nameTextBox_HEIGHT, NULL);
		SetWindowPos(hAdressTextBox, HWND_TOP, ContainerCreationWnd_adressTextBox_X,
			ContainerCreationWnd_adressTextBox_Y,
			ContainerCreationWnd_adressTextBox_WIDTH,
			ContainerCreationWnd_adressTextBox_HEIGHT, NULL);
		SetWindowPos(hTagsTextBox, HWND_TOP, ContainerCreationWnd_tagsTextBox_X,
			ContainerCreationWnd_tagsTextBox_Y,
			ContainerCreationWnd_tagsTextBox_WIDTH,
			ContainerCreationWnd_tagsTextBox_HEIGHT, NULL);
		SetWindowPos(hTagsListView, HWND_TOP, ContainerCreationWnd_tagsListView_X,
			ContainerCreationWnd_tagsListView_Y,
			ContainerCreationWnd_tagsListView_WIDTH,
			ContainerCreationWnd_tagsListView_HEIGHT, NULL);
		SetWindowPos(hTaskTypeDropDList, HWND_TOP, ContainerCreationWnd_taskTypeDropDList_X,
			ContainerCreationWnd_taskTypeDropDList_Y,
			ContainerCreationWnd_taskTypeDropDList_WIDTH,
			ContainerCreationWnd_taskTypeDropDList_HEIGHT, NULL);
	}
}

LRESULT ContainerCreationWindow::close_window(HWND hWnd)
{
	HWND hWndParent = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERNWND_WND);
	EnableWindow(hWndParent, true);
	SetFocus(hWndParent);

	if (ApplicationSettings::getStartupMethodContainerCreationWindow() == StartupMethod::SHOW_CLOSED_WINDOW)
	{
		ShowWindow(hWnd, false);
	}
	else
	{
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeDropDList);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_NameTextBox);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_ApplyButton);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_AdressTextBox);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TagsTextBox);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TagsListView);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_WND);
		DestroyWindow(hWnd);
	}
	return 0;
}
