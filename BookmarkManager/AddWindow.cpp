#include "AddWindow.h"

LRESULT CALLBACK AddWndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	HDC			addwp_hDc;
	PAINTSTRUCT addwp_paintstruct;
	RECT		rect;

	switch (msg)
	{
	case WM_PAINT: {
		addwp_hDc = BeginPaint(hWnd, &addwp_paintstruct);

		EndPaint(hWnd, &addwp_paintstruct);
		return 0;
	}

	case WM_SIZE: {
		GetClientRect(hWnd, &rect);

		SetWindowPos(addw_applyButton, HWND_TOP, rect.right - 107, rect.bottom - 40, NULL, NULL, SWP_NOSIZE);
		SetWindowPos(addw_nameTextBox, HWND_TOP, NULL, NULL, (rect.right / 2) - 4, 25, SWP_NOMOVE);
		SetWindowPos(addw_adressTextBox, HWND_TOP, (rect.right / 2) + 4, 20, (rect.right / 2) - 9, 25, NULL);
		SetWindowPos(addw_tagsTextBox, HWND_TOP, NULL, NULL, rect.right - 10, 25, SWP_NOMOVE);
		SetWindowPos(addw_tagslistView, HWND_TOP, NULL, NULL, rect.right - 10, (rect.bottom - 85) - 80, SWP_NOMOVE);
		return 0;
	}

	case WM_GETMINMAXINFO: {
		LPMINMAXINFO lpminmaxinfo = (LPMINMAXINFO)lParam;
		lpminmaxinfo->ptMinTrackSize.x = 350;
		lpminmaxinfo->ptMinTrackSize.y = 400;
		return 0;
	}

	case WM_CLOSE: {
		ShowWindow(hWnd, false);
		return 0;
	}

	default: {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
}

HWND addw_createWindow(HWND hWndParent, HINSTANCE hInstance)
{
	WNDCLASSEX addWindow = { NULL };

	addWindow.lpszClassName = MW_ADDCLASSNAME;
	addWindow.lpfnWndProc = AddWndProc;
	addWindow.hInstance = hInstance;
	addWindow.cbSize = sizeof(WNDCLASSEX);
	addWindow.style = CS_HREDRAW | CS_VREDRAW;
	addWindow.hbrBackground = CreateSolidBrush(RGB(70, 68, 81));
	addWindow.hCursor = LoadCursor(hInstance, IDC_ARROW);

	if (!RegisterClassEx(&addWindow))
	{
		MessageBox(NULL, L"Не удалось зарегистрировать класс окна", L"Error", MB_OK);
		return 0;
	}

	addw_wnd = CreateWindow(
		MW_ADDCLASSNAME,
		MW_ADDWNDNAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		600, 500,
		hWndParent,
		NULL,
		hInstance,
		NULL
	);

	if (!addw_wnd)
	{
		MessageBox(NULL, L"Не удалось создать окно", L"Error", MB_OK);
		return 0;
	}

	moveWindowToCenterScreen(addw_wnd);
	addw_createApplyButton(hInstance);
	addw_createNameTextBox(hInstance);
	addw_createAdressTextBox(hInstance);
	addw_createTagsTextBox(hInstance);
	addw_createTagsListView(hInstance);

	return addw_wnd;
}

HWND addw_createNameTextBox(HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(addw_wnd, &rect);

	addw_nameTextBox = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		5, 20,
		(rect.right / 2) - 4, 25,
		addw_wnd,
		NULL,
		hInstance,
		NULL
	);

	SendMessage(addw_nameTextBox, EM_SETCUEBANNER, false, (LPARAM)L"Название");

	return addw_nameTextBox;
}

HWND addw_createAdressTextBox(HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(addw_wnd, &rect);

	addw_adressTextBox = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		(rect.right / 2) + 4, 20,
		(rect.right / 2) - 9, 25,
		addw_wnd,
		NULL,
		hInstance,
		NULL
	);

	SendMessage(addw_adressTextBox, EM_SETCUEBANNER, false, (LPARAM)L"Адрес");

	return addw_adressTextBox;
}

HWND addw_createTagsTextBox(HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(addw_wnd, &rect);

	addw_tagsTextBox = CreateWindow(
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		5, 55,
		rect.right - 10, 25,
		addw_wnd,
		NULL,
		hInstance,
		NULL
	);

	SendMessage(addw_tagsTextBox, EM_SETCUEBANNER, false, (LPARAM)L"Тег");

	return addw_tagsTextBox;
}

HWND addw_createApplyButton(HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(addw_wnd, &rect);

	addw_applyButton = CreateWindow(
		L"BUTTON",
		L"Применить",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		rect.right - 107, rect.bottom - 40,
		100, 25,
		addw_wnd,
		NULL,
		hInstance,
		NULL
	);

	return addw_applyButton;
}

HWND addw_createTagsListView(HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(addw_wnd, &rect);

	addw_tagslistView = CreateWindow(
		WC_LISTVIEW,
		NULL,
		WS_CHILD | WS_VISIBLE | LVS_EDITLABELS | LVS_REPORT,
		5, 85,
		rect.right - 10, (rect.bottom - 85) - 80,
		addw_wnd,
		NULL,
		hInstance,
		NULL
	);

	LVCOLUMN column;
	column.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_FMT;
	column.cx = 250;
	column.pszText = (LPWSTR)L"Тег";
	column.iSubItem = 12;

	ListView_InsertColumn(addw_tagslistView, 12, &column);

	return addw_tagslistView;
}
