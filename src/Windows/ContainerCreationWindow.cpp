//TODO: Написать ошибки для разработчиков define DEBUG

#ifndef UNICODE
#define UNICODE
#endif

#include "ContainerCreationWindow.h"
#include "..\Total\HandleManager.h"
#include "..\Total\BmDef.h"
#include "..\ApplicationSettings\ApplicationSettings.h"
#include "..\Total\GeneralOperations.h"
#include <CommCtrl.h>


LRESULT CALLBACK ContainerCreationWindow::WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
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

	case WM_GETMINMAXINFO: {	
		GeneralOperations::setMinimumWindowSize(350, 400, lParam);
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
		HWND* hWndParent;

		hWndParent = HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd");
		EnableWindow(*hWndParent, true);
		SetFocus(*hWndParent);

		if (ApplicationSettings::getStartupMethodContainerCreationWindow() == StartupMethod::SHOW_CLOSED_WINDOW)
		{
			ShowWindow(hWnd, false);
		}
		else
		{
			HandleManager::removeHandleWnd(L"containerCreationWindow_wnd");
			HandleManager::removeHandleWnd(L"containerCreationWindow_nameTextBox");
			HandleManager::removeHandleWnd(L"containerCreationWindow_applyButton");
			HandleManager::removeHandleWnd(L"containerCreationWindow_adressTextBox");
			HandleManager::removeHandleWnd(L"containerCreationWindow_tagsTextBox");
			HandleManager::removeHandleWnd(L"containerCreationWindow_tagsListView");
			DestroyWindow(hWnd);
		}
		return 0;
	}

	default: {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
}

void ContainerCreationWindow::create_containerCreationWindow(HINSTANCE hInstance)
{
	HWND* hWndParent = HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd");
	HWND* hWnd = HandleManager::addHandleWnd(L"containerCreationWindow_wnd");

	*hWnd = CreateWindow(
		CONTAINERCREATIONWND_CLASSNAME,
		CONTAINERCREATIONWND_WNDNAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		600, 500,
		*hWndParent,
		NULL,
		hInstance,
		NULL);

	create_applyButton(*hWnd, hInstance);
	create_nameTextBox(*hWnd, hInstance);
	create_adressTextBox(*hWnd, hInstance);
	create_tagsTextBox(*hWnd, hInstance);
	create_tagsListView(*hWnd, hInstance);

	GeneralOperations::moveWindowToCenterScreen(*hWnd);

	ShowWindow(*hWnd, true);
	EnableWindow(*hWndParent, false);
}


void ContainerCreationWindow::create_nameTextBox(HWND hWndParent, HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(hWndParent, &rect);

	HWND* hTextBox = HandleManager::addHandleWnd(L"containerCreationWindow_nameTextBox");

	*hTextBox = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		5, 20,
		(rect.right / 2) - 4, 25,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	SendMessage(*hTextBox, EM_SETCUEBANNER, false, (LPARAM)L"Название");
	SendMessage(*hTextBox, EM_SETLIMITTEXT, 640, NULL); //TODO: Test
}

void ContainerCreationWindow::create_adressTextBox(HWND hWndParent, HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(hWndParent, &rect);

	HWND* hTextBox = HandleManager::addHandleWnd(L"containerCreationWindow_adressTextBox");

	*hTextBox = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		(rect.right / 2) + 4, 20,
		(rect.right / 2) - 9, 25,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	SendMessage(*hTextBox, EM_SETCUEBANNER, false, (LPARAM)L"Адрес");
}

void ContainerCreationWindow::create_tagsTextBox(HWND hWndParent, HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(hWndParent, &rect);

	HWND* hTextBox = HandleManager::addHandleWnd(L"containerCreationWindow_tagsTextBox");

	*hTextBox = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		5, 55,
		rect.right - 10, 25,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	SendMessage(*hTextBox, EM_SETCUEBANNER, false, (LPARAM)L"Тег");
}

void ContainerCreationWindow::create_applyButton(HWND hWndParent, HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(hWndParent, &rect);

	HWND* hButton = HandleManager::addHandleWnd(L"containerCreationWindow_applyButton");

	*hButton = CreateWindow(
		L"BUTTON",
		L"Применить",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		rect.right - 107, rect.bottom - 40,
		100, 25,
		hWndParent,
		(HMENU)ID_CONTAINERCREATIONWND_APPLYBUTTON,
		hInstance,
		NULL);
}

void ContainerCreationWindow::create_tagsListView(HWND hWndParent, HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(hWndParent, &rect);

	HWND* hListView = HandleManager::addHandleWnd(L"containerCreationWindow_tagsListView");

	*hListView = CreateWindow(
		WC_LISTVIEW,
		NULL,
		WS_CHILD | WS_VISIBLE | LVS_EDITLABELS | LVS_REPORT, //TODO: delete LVS_EDITLABELS
		5, 85,
		rect.right - 10, (rect.bottom - 85) - 80,
		hWndParent,
		NULL,
		hInstance,
		NULL);

	LVCOLUMN lvcolumn;
	lvcolumn.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_FMT; //TODO: Откорректировать
	lvcolumn.cx = 250;
	lvcolumn.pszText = (LPWSTR)L"Тег";
	lvcolumn.iSubItem = 12;

	ListView_InsertColumn(*hListView, 1, &lvcolumn);
}


void ContainerCreationWindow::fill_container()
{
	HWND*		hWnd = nullptr;
	Container	container;

	bool errorCode_nameTB = setDataFromTextBox(L"containerCreationWindow_nameTextBox", ContainerDataTypes::NAME, container);
	bool errorCode_adressTB = setDataFromTextBox(L"containerCreationWindow_adressTextBox", ContainerDataTypes::TASK, container);

	/*
	*		If nameTextBox or adressTextBox is not full.
	*		You can interrupt it this way, just until you add it to the archive.
	*/
	if (!(errorCode_nameTB && errorCode_adressTB))
	{
		container.clear();
		hWnd = HandleManager::getHandleWnd(L"containerCreationWindow_wnd");
		MessageBox(*hWnd, L"Поля \"Имя\" и \"Задача\" должны быть заполнены!", L"Input Error", MB_OK | MB_ICONWARNING);
		return;
	}

	ID id = Archive::addContainer(container);

	hWnd = HandleManager::getHandleWnd(L"bookmarkManagerWindow_wnd");
	SendMessage(*hWnd, UM_SHOWCREATEDCONTAINER, NULL, id);
	hWnd = HandleManager::getHandleWnd(L"containerCreationWindow_wnd");
	SendMessage(*hWnd, WM_CLOSE, NULL, NULL);
}

bool ContainerCreationWindow::setDataFromTextBox(PCWSTR hTextBoxName, ContainerDataTypes dataType, Container& container)
{
	HWND*	hWnd = HandleManager::getHandleWnd(hTextBoxName);
	size_t	length = GetWindowTextLength(*hWnd) + (size_t)1;
	PWSTR	content = new WCHAR[length];

	GetWindowText(*hWnd, content, length);
	container.setContent(dataType, content, length);
	delete[] content;

	return (length == 1)? false : true;
}

void ContainerCreationWindow::adjustmentOfControls(HWND hWnd)
{
	HandleName сhecklist[]{ L"containerCreationWindow_nameTextBox", L"containerCreationWindow_adressTextBox",
							L"containerCreationWindow_tagsTextBox", L"containerCreationWindow_applyButton",
							L"containerCreationWindow_tagsListView", L"\0" };
	
	if (HandleManager::checkExistence(сhecklist))
	{
		RECT	rect;
		GetClientRect(hWnd, &rect);
		
		HWND* hApplyButton = HandleManager::getHandleWnd(L"containerCreationWindow_applyButton");
		HWND* hNameTextBox = HandleManager::getHandleWnd(L"containerCreationWindow_nameTextBox");
		HWND* hAdressTextBox = HandleManager::getHandleWnd(L"containerCreationWindow_adressTextBox");
		HWND* hTagsTextBox = HandleManager::getHandleWnd(L"containerCreationWindow_tagsTextBox");
		HWND* hTagsListView = HandleManager::getHandleWnd(L"containerCreationWindow_tagsListView");

		SetWindowPos(*hApplyButton, HWND_TOP, rect.right - 107, rect.bottom - 40, NULL, NULL, SWP_NOSIZE);
		SetWindowPos(*hNameTextBox, HWND_TOP, NULL, NULL, (rect.right / 2) - 4, 25, SWP_NOMOVE);
		SetWindowPos(*hAdressTextBox, HWND_TOP, (rect.right / 2) + 4, 20, (rect.right / 2) - 9, 25, NULL);
		SetWindowPos(*hTagsTextBox, HWND_TOP, NULL, NULL, rect.right - 10, 25, SWP_NOMOVE);
		SetWindowPos(*hTagsListView, HWND_TOP, NULL, NULL, rect.right - 10, (rect.bottom - 85) - 80, SWP_NOMOVE);
	}
}