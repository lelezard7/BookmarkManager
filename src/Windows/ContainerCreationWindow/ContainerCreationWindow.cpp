#ifndef UNICODE
#define UNICODE
#endif

#include "ContainerCreationWindow.h"
#include "..\..\HandleManager\HandleManager.h"
#include "..\..\Common\BkmDef.h"
#include "..\..\ApplicationSettings\ApplicationSettings.h"
#include "..\..\Common\CommonOperations.h"
#include "..\..\Common\PositionAndSizeControls.h"
#include <CommCtrl.h>
#include <Richedit.h>


LRESULT CALLBACK ContainerCreationWindow::WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	HDC			hDC;
	PAINTSTRUCT	paintstruct;

	switch (msg)
	{
	//case WM_PAINT: {
	//	hDC = BeginPaint(hWnd, &paintstruct);

	//	EndPaint(hWnd, &paintstruct);
	//	return 0;
	//}

	//case WM_SIZE: {
	//	/*		Resizes and positions controls.		*/
	//	adjustmentOfControls();
	//	return 0;
	//}

	//case WM_GETMINMAXINFO: {	
	//	CommonOperations::setMinimumWindowSize(350, 400, lParam);
	//	return 0;
	//}

	//case WM_COMMAND: {
	//	if (HIWORD(wParam) == 0)
	//	{
	//		switch (LOWORD(wParam))
	//		{
	//		case ID_CONTAINERCREATIONWND_APPLYBUTTON: {
	//			fill_container();
	//			return 0;
	//		}
	//		}
	//	}
	//	return 0;
	//}

	//case WM_CLOSE: {
	//	HWND* hWndParent;

	//	hWndParent = HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd");
	//	EnableWindow(*hWndParent, true);
	//	SetFocus(*hWndParent);

	//	if (ApplicationSettings::getStartupMethodContainerCreationWindow() == StartupMethod::SHOW_CLOSED_WINDOW)
	//	{
	//		ShowWindow(hWnd, false);
	//	}
	//	else
	//	{
	//		HandleManager::removeHandleWnd(L"containerCreationWindow_wnd");
	//		HandleManager::removeHandleWnd(L"containerCreationWindow_nameTextBox");
	//		HandleManager::removeHandleWnd(L"containerCreationWindow_applyButton");
	//		HandleManager::removeHandleWnd(L"containerCreationWindow_adressTextBox");
	//		HandleManager::removeHandleWnd(L"containerCreationWindow_tagsTextBox");
	//		HandleManager::removeHandleWnd(L"containerCreationWindow_tagsListView");
	//		FreeLibrary(GetModuleHandle(L"Msftedit.dll")); //TODO: Test
	//		DestroyWindow(hWnd);
	//	}
	//	return 0;
	//}

	default: {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
}

//void ContainerCreationWindow::create_containerCreationWindow(HINSTANCE hInstance)
//{
//	HWND* hWndParent = HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd");
//	HWND* hWnd = HandleManager::addHandleWnd(L"containerCreationWindow_wnd");
//
//	*hWnd = CreateWindow(
//		CONTAINERCREATIONWND_CLASSNAME,
//		CONTAINERCREATIONWND_WNDNAME,
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, CW_USEDEFAULT,
//		600, 500,
//		*hWndParent,
//		NULL,
//		hInstance,
//		NULL);
//
//	LoadLibrary(L"Msftedit.dll");
//
//	create_taskTypeDropDList(*hWnd, hInstance);
//	create_applyButton(*hWnd, hInstance);
//	create_nameTextBox(*hWnd, hInstance);
//	create_adressTextBox(*hWnd, hInstance);
//	create_tagsTextBox(*hWnd, hInstance);
//	create_tagsListView(*hWnd, hInstance);
//
//	CommonOperations::moveWindowToCenterScreen(*hWnd);
//
//	ShowWindow(*hWnd, true);
//	EnableWindow(*hWndParent, false);
//}
//
//
//void ContainerCreationWindow::create_taskTypeDropDList(HWND hWndParent, HINSTANCE hInstance)
//{
//	HWND* hDropDList = HandleManager::addHandleWnd(L"containerCreationWindow_taskTypeDropDList");
//
//	*hDropDList = CreateWindow(
//		L"COMBOBOX",
//		NULL,
//		WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
//		ContainerCreationWnd_taskTypeDropDList_X,
//		ContainerCreationWnd_taskTypeDropDList_Y,
//		ContainerCreationWnd_taskTypeDropDList_WIDTH,
//		ContainerCreationWnd_taskTypeDropDList_HEIGHT,
//		hWndParent,
//		NULL,
//		hInstance,
//		NULL);
//
//	SendMessage(*hDropDList, CB_INSERTSTRING, -1, (LPARAM)L"URL");
//	SendMessage(*hDropDList, CB_INSERTSTRING, -1, (LPARAM)L"Program");
//	SendMessage(*hDropDList, CB_SETCURSEL, 0, NULL);
//}
//
//void ContainerCreationWindow::create_nameTextBox(HWND hWndParent, HINSTANCE hInstance)
//{
//	HWND* hTextBox = HandleManager::addHandleWnd(L"containerCreationWindow_nameTextBox");
//
//	*hTextBox = CreateWindow(
//		MSFTEDIT_CLASS,
//		NULL,
//		WS_VISIBLE | WS_CHILD | WS_HSCROLL | WS_TABSTOP, //TODO: WS_TABSTOP doesn't work
//		ContainerCreationWnd_nameTextBox_X,
//		ContainerCreationWnd_nameTextBox_Y,
//		ContainerCreationWnd_nameTextBox_WIDTH,
//		ContainerCreationWnd_nameTextBox_HEIGHT,
//		hWndParent,
//		NULL,
//		hInstance,
//		NULL);
//
//	SendMessage(*hTextBox, EM_SHOWSCROLLBAR, SB_HORZ, false);
//	SendMessage(*hTextBox, EM_SETCUEBANNER, false, (LPARAM)L"Название"); //TODO: doesn't work
//
//}
//
//void ContainerCreationWindow::create_adressTextBox(HWND hWndParent, HINSTANCE hInstance)
//{
//	HWND* hTextBox = HandleManager::addHandleWnd(L"containerCreationWindow_adressTextBox");
//
//	*hTextBox = CreateWindow(
//		MSFTEDIT_CLASS,
//		NULL,
//		WS_VISIBLE | WS_CHILD | WS_HSCROLL | WS_TABSTOP,
//		ContainerCreationWnd_adressTextBox_X,
//		ContainerCreationWnd_adressTextBox_Y,
//		ContainerCreationWnd_adressTextBox_WIDTH,
//		ContainerCreationWnd_adressTextBox_HEIGHT,
//		hWndParent,
//		NULL,
//		hInstance,
//		NULL);
//
//	SendMessage(*hTextBox, EM_SHOWSCROLLBAR, SB_HORZ, false);
//	SendMessage(*hTextBox, EM_SETCUEBANNER, false, (LPARAM)L"Адрес"); //TODO: doesn't work
//}
//
//void ContainerCreationWindow::create_tagsTextBox(HWND hWndParent, HINSTANCE hInstance)
//{
//	HWND* hTextBox = HandleManager::addHandleWnd(L"containerCreationWindow_tagsTextBox");
//
//	*hTextBox = CreateWindow(
//		L"EDIT",
//		NULL,
//		WS_VISIBLE | WS_CHILD | WS_BORDER,
//		ContainerCreationWnd_tagsTextBox_X,
//		ContainerCreationWnd_tagsTextBox_Y,
//		ContainerCreationWnd_tagsTextBox_WIDTH,
//		ContainerCreationWnd_tagsTextBox_HEIGHT,
//		hWndParent,
//		NULL,
//		hInstance,
//		NULL);
//
//	SendMessage(*hTextBox, EM_SETCUEBANNER, false, (LPARAM)L"Тег");
//}
//
//void ContainerCreationWindow::create_applyButton(HWND hWndParent, HINSTANCE hInstance)
//{
//	HWND* hButton = HandleManager::addHandleWnd(L"containerCreationWindow_applyButton");
//
//	*hButton = CreateWindow(
//		L"BUTTON",
//		L"Применить",
//		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
//		ContainerCreationWnd_applyButton_X,
//		ContainerCreationWnd_applyButton_Y,
//		ContainerCreationWnd_applyButton_WIDTH,
//		ContainerCreationWnd_applyButton_HEIGHT,
//		hWndParent,
//		(HMENU)ID_CONTAINERCREATIONWND_APPLYBUTTON,
//		hInstance,
//		NULL);
//}
//
//void ContainerCreationWindow::create_tagsListView(HWND hWndParent, HINSTANCE hInstance)
//{
//	HWND* hListView = HandleManager::addHandleWnd(L"containerCreationWindow_tagsListView");
//
//	*hListView = CreateWindow(
//		WC_LISTVIEW,
//		NULL,
//		WS_CHILD | WS_VISIBLE | LVS_EDITLABELS | LVS_REPORT, //TODO: delete LVS_EDITLABELS
//		ContainerCreationWnd_tagsListView_X,
//		ContainerCreationWnd_tagsListView_Y,
//		ContainerCreationWnd_tagsListView_WIDTH,
//		ContainerCreationWnd_tagsListView_HEIGHT,
//		hWndParent,
//		NULL,
//		hInstance,
//		NULL);
//
//	LVCOLUMN lvcolumn;
//	lvcolumn.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_FMT; //TODO: Откорректировать
//	lvcolumn.cx = 250;
//	lvcolumn.pszText = (LPWSTR)L"Тег";
//	lvcolumn.iSubItem = 12;
//
//	ListView_InsertColumn(*hListView, 1, &lvcolumn);
//}
//
//
//void ContainerCreationWindow::fill_container()
//{
//	HWND*		hWnd = HandleManager::getHandleWnd(L"containerCreationWindow_taskTypeDropDList");
//	Container	container;
//
//	//		We write down the value of the taskTypeDropDList in the container.
//	size_t	length = GetWindowTextLength(*hWnd) + (size_t)1;
//	PWSTR	content = new WCHAR[length];
//	GetWindowText(*hWnd, content, length);
//
//	if (!std::wcscmp(content, L"URL"))
//	{
//		container.setTaskType(TaskTypes::URL);
//	}
//	else if (!std::wcscmp(content, L"Program"))
//	{
//		container.setTaskType(TaskTypes::PROGRAM);
//	}
//	delete[] content;
//
//	//		We write down the values of the nameTextBox and adressTextBox in the container.
//	bool errorCode_nameTB = setDataFromTextBox(L"containerCreationWindow_nameTextBox", ContainerDataTypes::NAME, container);
//	bool errorCode_adressTB = setDataFromTextBox(L"containerCreationWindow_adressTextBox", ContainerDataTypes::TASK, container);
//
//	/*
//	*		If nameTextBox or adressTextBox is not full.
//	*		You can break the code this way only until you add the container to the archive!
//	*/
//	if (!(errorCode_nameTB && errorCode_adressTB))
//	{
//		container.clear();
//		hWnd = HandleManager::getHandleWnd(L"containerCreationWindow_wnd");
//		MessageBox(*hWnd, L"Поля \"Имя\" и \"Задача\" должны быть заполнены!", L"Input Error", MB_OK | MB_ICONWARNING);
//		return;
//	}
//
//	ID id = Archive::addContainer(container);
//
//	hWnd = HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd");
//	SendMessage(*hWnd, UM_SHOWCREATEDCONTAINER, NULL, id);
//	hWnd = HandleManager::getHandleWnd(L"containerCreationWindow_wnd");
//	SendMessage(*hWnd, WM_CLOSE, NULL, NULL);
//}
//
//bool ContainerCreationWindow::setDataFromTextBox(PCWSTR hTextBoxName, ContainerDataTypes dataType, Container& container)
//{
//	HWND*	hWnd = HandleManager::getHandleWnd(hTextBoxName);
//	size_t	length = GetWindowTextLength(*hWnd) + (size_t)1;
//	PWSTR	content = new WCHAR[length];
//
//	GetWindowText(*hWnd, content, length);
//	container.setContent(dataType, content, length);
//	delete[] content;
//
//	return (length == 1)? false : true;
//}
//
//void ContainerCreationWindow::adjustmentOfControls()
//{
//	HandleName сhecklist[]{ L"containerCreationWindow_nameTextBox", L"containerCreationWindow_adressTextBox",
//							L"containerCreationWindow_tagsTextBox", L"containerCreationWindow_applyButton",
//							L"containerCreationWindow_tagsListView", L"containerCreationWindow_taskTypeDropDList", L"\0" };
//	
//	if (HandleManager::checkExistence(сhecklist))
//	{
//		HWND* hApplyButton = HandleManager::getHandleWnd(L"containerCreationWindow_applyButton");
//		HWND* hNameTextBox = HandleManager::getHandleWnd(L"containerCreationWindow_nameTextBox");
//		HWND* hAdressTextBox = HandleManager::getHandleWnd(L"containerCreationWindow_adressTextBox");
//		HWND* hTagsTextBox = HandleManager::getHandleWnd(L"containerCreationWindow_tagsTextBox");
//		HWND* hTagsListView = HandleManager::getHandleWnd(L"containerCreationWindow_tagsListView");
//		HWND* hTaskTypeDropDList = HandleManager::getHandleWnd(L"containerCreationWindow_taskTypeDropDList");
//
//		SetWindowPos(*hApplyButton, HWND_TOP, ContainerCreationWnd_applyButton_X,
//			ContainerCreationWnd_applyButton_Y,
//			ContainerCreationWnd_applyButton_WIDTH,
//			ContainerCreationWnd_applyButton_HEIGHT, NULL);
//		SetWindowPos(*hNameTextBox, HWND_TOP, ContainerCreationWnd_nameTextBox_X,
//			ContainerCreationWnd_nameTextBox_Y,
//			ContainerCreationWnd_nameTextBox_WIDTH,
//			ContainerCreationWnd_nameTextBox_HEIGHT, NULL);
//		SetWindowPos(*hAdressTextBox, HWND_TOP, ContainerCreationWnd_adressTextBox_X,
//			ContainerCreationWnd_adressTextBox_Y,
//			ContainerCreationWnd_adressTextBox_WIDTH,
//			ContainerCreationWnd_adressTextBox_HEIGHT, NULL);
//		SetWindowPos(*hTagsTextBox, HWND_TOP, ContainerCreationWnd_tagsTextBox_X,
//			ContainerCreationWnd_tagsTextBox_Y,
//			ContainerCreationWnd_tagsTextBox_WIDTH,
//			ContainerCreationWnd_tagsTextBox_HEIGHT, NULL);
//		SetWindowPos(*hTagsListView, HWND_TOP, ContainerCreationWnd_tagsListView_X,
//			ContainerCreationWnd_tagsListView_Y,
//			ContainerCreationWnd_tagsListView_WIDTH,
//			ContainerCreationWnd_tagsListView_HEIGHT, NULL);
//		SetWindowPos(*hTaskTypeDropDList, HWND_TOP, ContainerCreationWnd_taskTypeDropDList_X,
//			ContainerCreationWnd_taskTypeDropDList_Y,
//			ContainerCreationWnd_taskTypeDropDList_WIDTH,
//			ContainerCreationWnd_taskTypeDropDList_HEIGHT, NULL);
//	}
//}