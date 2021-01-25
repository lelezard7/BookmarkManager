#include "main.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX			mw_wndClass = { NULL };
	MSG					mw_msg;

	mw_wndClass.lpszClassName = MW_MAINCLASSNAME;
	mw_wndClass.lpfnWndProc = WndProc;
	mw_wndClass.hInstance = hInstance;
	mw_wndClass.cbSize = sizeof(WNDCLASSEX);
	mw_wndClass.style = CS_HREDRAW | CS_VREDRAW;
	mw_wndClass.hbrBackground = CreateSolidBrush(RGB(70, 68, 81));
	mw_wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);

	if (!RegisterClassEx(&mw_wndClass))
	{
		MessageBox(NULL, L"Не удалось зарегистрировать класс окна", L"Error", MB_OK);
		return 0;
	}

	HMENU mw_menu = mw_createMenu();


	HWND mw_wnd = CreateWindow(
		MW_MAINCLASSNAME,
		MW_MAINWNDNAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 650,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!mw_wnd)
	{
		MessageBox(NULL, L"Не удалось создать окно", L"Error", MB_OK);
		return 0;
	}

	SetMenu(mw_wnd, mw_menu);
	moveWindowToCenterScreen(mw_wnd);
	mw_createListView(mw_wnd, hInstance);
	mw_createAddButton(mw_wnd, hInstance);
	mw_createOpenButton(mw_wnd, hInstance);
	mw_createCleanButton(mw_wnd, hInstance);

	addw_createWindow(mw_wnd, hInstance);

	ShowWindow(mw_wnd, nCmdShow);
	UpdateWindow(mw_wnd);


	while (GetMessage(&mw_msg, NULL, NULL, NULL))
	{
		TranslateMessage(&mw_msg);
		DispatchMessage(&mw_msg);
	}

	return (int)mw_msg.wParam;
}

LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	HDC				wp_hDc;
	PAINTSTRUCT		wp_paintstruct;
	RECT			rect;

	switch (msg)
	{
	case WM_PAINT: {
		wp_hDc = BeginPaint(hWnd, &wp_paintstruct);

		EndPaint(hWnd, &wp_paintstruct);
		return 0;
	}

	case WM_SIZE: {
		GetClientRect(hWnd, &rect);

		SetWindowPos(mw_listView, HWND_TOP, NULL, NULL, rect.right - 10, rect.bottom - 50, SWP_NOMOVE);
		SetWindowPos(mw_addButton, HWND_TOP, rect.right - 107, rect.bottom - 40, NULL, NULL, SWP_NOSIZE);
		SetWindowPos(mw_openButton, HWND_TOP, rect.left + 7, rect.bottom - 40, NULL, NULL, SWP_NOSIZE);
		SetWindowPos(mw_cleanButton, HWND_TOP, rect.left + 112, rect.bottom - 40, NULL, NULL, SWP_NOSIZE);
		return 0;
	}

	case WM_COMMAND: {
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
			case MW_MENU_FILE_IDCLOSE: {
				PostMessage(hWnd, WM_CLOSE, NULL, NULL);
				return 0;
			}

			case IDADDBUTTON: {
				moveWindowToCenterScreen(addw_wnd);
				ShowWindow(addw_wnd, true);
				return 0;
			}
			}
		}
		return 0;
	}

	case WM_GETMINMAXINFO: {
		LPMINMAXINFO lpminmaxinfo = (LPMINMAXINFO)lParam;
		lpminmaxinfo->ptMinTrackSize.x = 350;
		lpminmaxinfo->ptMinTrackSize.y = 400;
		return 0;
	}

	case WM_CLOSE: {
		DestroyWindow(hWnd); //TODO: Спрашивать о сохранении файла
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

HMENU mw_createMenu()
{
	HMENU	mw_mainMenu = CreateMenu();
	HMENU	mw_filePopupMenu = CreatePopupMenu();
	HMENU	mw_helpPopupMenu = CreatePopupMenu();

	AppendMenu(mw_mainMenu, MF_STRING | MF_POPUP, (UINT)mw_filePopupMenu, MW_MENU_FILESTRING);
	{
		AppendMenu(mw_filePopupMenu, MF_STRING, MW_MENU_FILE_IDSETTINGS, MW_MENU_FILE_SETTINGSSTRING);
		AppendMenu(mw_filePopupMenu, MF_STRING, MW_MENU_FILE_IDCLOSE, MW_MENU_FILE_CLOSESTRING);
	}

	AppendMenu(mw_mainMenu, MF_STRING | MF_POPUP, (UINT)mw_helpPopupMenu, MW_MENU_HELPSTRING);
	{
		AppendMenu(mw_helpPopupMenu, MF_STRING, MW_MENU_HELP_IDHOWTOUSE, MW_MENU_HELP_HOWTOUSESTRING);
		AppendMenu(mw_helpPopupMenu, MF_STRING, MW_MENU_HELP_IDABOUTPROGRAM, MW_MENU_HELP_ABOUTPROGRAMSTRING);
	}

	return mw_mainMenu;
}

HWND mw_createListView(HWND hWndParent, HINSTANCE hInstance)
{
	INITCOMMONCONTROLSEX	icex;
	RECT					rect;
	 
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);

	GetClientRect(hWndParent, &rect);

	mw_listView = CreateWindow(
		WC_LISTVIEW,
		NULL,
		WS_CHILD | WS_VISIBLE | LVS_EDITLABELS | LVS_REPORT,
		5, 5,
		rect.right - 10, rect.bottom - 50,
		hWndParent,
		NULL,
		hInstance,
		NULL
	);

	LVCOLUMN column;
	column.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_FMT;
	column.cx = 250;
	column.pszText = (LPWSTR)L"Name";
	column.iSubItem = 12;

	ListView_InsertColumn(mw_listView, 12, &column);

	return mw_listView;
}

HWND mw_createAddButton(HWND hWndParent, HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(hWndParent, &rect);

	mw_addButton = CreateWindow(
		L"BUTTON",
		L"Добавить",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		rect.right - 107, rect.bottom - 40,
		100, 25,
		hWndParent,
		(HMENU)IDADDBUTTON,
		hInstance,
		NULL
	);

	return mw_addButton;
}

HWND mw_createOpenButton(HWND hWndParent, HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(hWndParent, &rect);

	mw_openButton = CreateWindow(
		L"BUTTON",
		L"Открыть",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		rect.left + 7, rect.bottom - 40,
		100, 25,
		hWndParent,
		NULL,
		hInstance,
		NULL
	);

	return mw_openButton;
}

HWND mw_createCleanButton(HWND hWndParent, HINSTANCE hInstance)
{
	RECT	rect;
	GetClientRect(hWndParent, &rect);

	mw_cleanButton = CreateWindow(
		L"BUTTON",
		L"Очистить",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		rect.left + 112, rect.bottom - 40,
		100, 25,
		hWndParent,
		NULL,
		hInstance,
		NULL
	);

	return mw_cleanButton;
}
