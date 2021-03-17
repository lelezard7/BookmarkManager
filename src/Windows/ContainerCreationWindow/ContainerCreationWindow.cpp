﻿#define UNICODE

#include "ContainerCreationWindow.h"
#include "..\..\Common\BkmDef.h"
#include "..\..\ApplicationSettings\ApplicationSettings.h"
#include "..\..\Common\CommonOperations.h"
#include "..\..\Common\PositionAndSizeControls.h"
#include "..\..\res\res.h"
#include <CommCtrl.h>

#define COLORBK			(RGB(70, 68, 81))
#define COLORText		(RGB(255, 255, 250))
HBRUSH staticBK;


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
		switch (LOWORD(wParam))
		{
		case BKM_ID_ENTER: {
			HWND currentFocus = GetFocus();

			if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsTextBox))
				applyTag();
			else
				fill_container();

			return 0;
		}

		case BKM_ID_TAB: {
			HWND currentFocus = GetFocus();

			if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_NameTextBox))
				SetFocus(HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_AdressTextBox));
			else if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_AdressTextBox))
				SetFocus(HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeDropDList));
			else if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeDropDList))
				SetFocus(HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsTextBox));
			else if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsTextBox))
				SetFocus(HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_ApplyButton));
				
			return 0;
		}

		case ID_CONTAINERCREATIONWND_APPLYBUTTON: {
			fill_container();
			return 0;
		}

		case ID_CONTAINERCREATIONWND_APPLYTAGBUTTON: {
			applyTag();
			return 0;
		}
		}
		return 0;
	}

	case WM_CTLCOLORSTATIC: {
		SetBkColor((HDC)wParam, COLORBK);
		SetTextColor((HDC)wParam, COLORText);
		return (LRESULT)staticBK;
	}

	case WM_CLOSE: {
		return close_window(hWnd, lParam);
	}

	default: {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
}

void ContainerCreationWindow::create_containerCreationWindow(HINSTANCE hInstance)
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
	staticBK = CreateSolidBrush(COLORBK);

	create_taskTypeDropDList(hWnd, hInstance);
	create_nameTextBox(hWnd, hInstance);
	create_adressTextBox(hWnd, hInstance);
	create_tagsTextBox(hWnd, hInstance);
	create_applyButton(hWnd, hInstance);
	create_tagsListView(hWnd, hInstance);
	create_applyTagButton(hWnd, hInstance);
	create_taskTypeHelpText(hWnd, hInstance);

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

	createTaskTypesCB(hWnd);

	TaskTypes_ID DefaultTaskType = ApplicationSettings::getDefaultTaskType();
	if (DefaultTaskType != TASKT_NOTSPECIFIED)
	{
		SendMessage(hWnd, CB_SETCURSEL, DefaultTaskType, NULL);
	}
}

void ContainerCreationWindow::create_nameTextBox(HWND hWndParent, HINSTANCE hInstance)
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

	SendMessage(hWnd, EM_SETCUEBANNER, false, (LPARAM)L"Name");
}

void ContainerCreationWindow::create_adressTextBox(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
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

void ContainerCreationWindow::create_applyTagButton(HWND hWndParent, HINSTANCE hInstance)
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

void ContainerCreationWindow::create_taskTypeHelpText(HWND hWndParent, HINSTANCE hInstance)
{
	HWND hWnd = CreateWindow(
		L"STATIC",
		L"Task Type:",
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


void ContainerCreationWindow::fill_container()
{


	//HWND	hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeDropDList);
	//Container	container;

	////Checks if the issue type is set.
	//int index = SendMessage(hWnd, CB_GETCURSEL, NULL, NULL);
	//if (index != -1)
	//{
	//	container.setTaskType(index);
	//}
	//else
	//{
	//	MessageBox(hWnd, L"Task type not selected", L"Input Error", MB_OK | MB_ICONWARNING);
	//	return;
	//}


	////		We write down the values of the nameTextBox and adressTextBox in the container.
	//bool errorCode_nameTB = setDataFromTextBox(HNAME_CONTAINERCREATIONWND_NameTextBox, ContainerDataTypes::NAME, container);
	//bool errorCode_adressTB = setDataFromTextBox(HNAME_CONTAINERCREATIONWND_AdressTextBox, ContainerDataTypes::TASK, container);

	///*
	//*		If nameTextBox or adressTextBox is not full.
	//*		You can break the code this way only until you add the container to the archive!
	//*/
	//if (!(errorCode_nameTB && errorCode_adressTB))
	//{
	//	container.clear();
	//	hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND);
	//	MessageBox(hWnd, L"The \"Name\" and \"Task\" fields must be filled!", L"Input Error", MB_OK | MB_ICONWARNING);
	//	return;
	//} //TODO: Возможен ввод пробелов. Исправить.
	//

	//HWND hTagsListView = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsListView);
	//int tagsCount = ListView_GetItemCount(hTagsListView);
	//WCHAR buffer[1000];
	//LVITEM lvitem;
	//lvitem.mask = LVIF_TEXT;
	//lvitem.pszText = buffer;
	//lvitem.cchTextMax = 1000;
	//for (size_t i = 0; i < tagsCount; i++)
	//{
	//	lvitem.iItem = i;
	//	ListView_GetItem(hTagsListView, &lvitem);
	//	container.addTag(lvitem.pszText);
	//}

	//ID id = Archive::addContainer(container);

	//hWnd = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_WND);
	//SendMessage(hWnd, UM_SHOWCREATEDCONTAINER, NULL, id);
	//hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND);
	//SendMessage(hWnd, WM_CLOSE, NULL, true);
	Container	container;
	typedef void (Container::* gg)(const PWSTR);
	gg g = &container.setName;
	Content f = &container.setName;
	setDataFromTextBox(HNAME_CONTAINERCREATIONWND_NameTextBox, , container);
}

bool ContainerCreationWindow::setDataFromTextBox(HandleName hTextBoxName, Content content, Container& container)
{
	HWND	hWnd = HandleManager::getHandleWnd(hTextBoxName);
	size_t	length = GetWindowTextLength(hWnd) + (size_t)1;
	PWSTR	buffer = new WCHAR[length];

	GetWindowText(hWnd, buffer, length);
	container.
	delete[] buffer;

	return (length == 1) ? false : true;
}

//bool ContainerCreationWindow::setDataFromTextBox(HandleName hTextBoxName, ContainerDataTypes dataType, Container& container)
//{
//
//	return 0;
//	//HWND	hWnd = HandleManager::getHandleWnd(hTextBoxName);
//	//size_t	length = GetWindowTextLength(hWnd) + (size_t)1;
//	//PWSTR	content = new WCHAR[length];
//
//	//GetWindowText(hWnd, content, length);
//	//container.setContent(dataType, content, length);
//	//delete[] content;
//
//	//return (length == 1)? false : true;
//}

void ContainerCreationWindow::applyTag()
{
	HWND hTagsTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsTextBox);
	size_t	length = GetWindowTextLength(hTagsTextBox) + (size_t)1;
	PWSTR buffer = new WCHAR[length];

	GetWindowText(hTagsTextBox, buffer, length);

	HWND hTagsListView = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsListView);
	LVITEM lvitem = { NULL };
	lvitem.mask = LVIF_TEXT;
	lvitem.pszText = buffer;

	ListView_InsertItem(hTagsListView, &lvitem);
	delete[] buffer;
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
	сheckList.push_back(HNAME_CONTAINERCREATIONWND_ApplyTagButton);
	сheckList.push_back(HNAME_CONTAINERCREATIONWND_TaskTypeHelpText);
	
	if (HandleManager::checkExistence(сheckList))
	{
		HWND hApplyButton = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_ApplyButton);
		HWND hNameTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_NameTextBox);
		HWND hAdressTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_AdressTextBox);
		HWND hTagsTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsTextBox);
		HWND hTagsListView = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsListView);
		HWND hTaskTypeDropDList = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeDropDList);
		HWND hApplyTagButton = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_ApplyTagButton);
		HWND hTaskTypeHelpText = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeHelpText);

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
		SetWindowPos(hApplyTagButton, HWND_TOP, ContainerCreationWnd_applyTagButton_X,
			ContainerCreationWnd_applyTagButton_Y,
			ContainerCreationWnd_applyTagButton_WIDTH,
			ContainerCreationWnd_applyTagButton_HEIGHT, NULL);
		SetWindowPos(hTaskTypeHelpText, HWND_TOP, ContainerCreationWnd_taskTypeHelpText_X,
			ContainerCreationWnd_taskTypeHelpText_Y,
			ContainerCreationWnd_taskTypeHelpText_WIDTH,
			ContainerCreationWnd_taskTypeHelpText_HEIGHT, NULL);
	}
}

LRESULT ContainerCreationWindow::close_window(HWND hWnd, LPARAM lParam)
{
	StartupMethod startupmethod = ApplicationSettings::getStartupMethodContainerCreationWindow();

	if (startupmethod == StartupMethod::CREATE_NEW_WINDOW
		|| (lParam == true && startupmethod == StartupMethod::CONTINUE_UNFINISHED_CREATION))
	{
		HWND hWndParent = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_WND);
		EnableWindow(hWndParent, true);
		SetFocus(hWndParent);

		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeDropDList);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_NameTextBox);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_ApplyButton);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_AdressTextBox);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TagsTextBox);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TagsListView);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_ApplyTagButton);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeHelpText);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_WND);
		DestroyWindow(hWnd);
		DeleteObject(staticBK);
	}
	else
	{
		HWND hWndParent = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_WND);
		EnableWindow(hWndParent, true);
		SetFocus(hWndParent);

		ShowWindow(hWnd, false);
	}

	return 0;
}
