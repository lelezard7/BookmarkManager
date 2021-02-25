//TODO: Сделать смену языка
//TODO: Add a license
//TODO: delete 'pragma comment'

/*
*		General requirements:
*				1) The name of the .h file must be equal to the name of the .cpp file.
*/

/*
*		BookmarkManager.cpp initiates common controls, registers window classes.
*		Then creates the main window and displays it. Finally, it triggers a message loop.
*/

#ifndef UNICODE
#define UNICODE
#endif

#include "Windows\BookmarkManagerWindow\BookmarkManagerWindow.h"
#include "Windows\ContainerCreationWindow\ContainerCreationWindow.h"
#include "Windows\AboutProgramWindow\AboutProgramWindow.h"
#include "Common\BkmDef.h"
#include "HandleManager\HandleManager.h"
#include "res\Resource.h"
#include <Windows.h>
#include <CommCtrl.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

/*		Later a help on possible errors will be created and bool will possibly be replaced.		*/
typedef bool ErrorCode;

/*		Initialization of common controls.		*/
ErrorCode initialization_commCtrl();
/*		Registering window classes.		*/
ErrorCode register_windowClasses(HINSTANCE hInstance);


INT WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	/*
	*		Common controls are initiated here and classes of all windows are recorded.
	*		If one of these steps fails the program stops running.
	*/
	if (!initialization_commCtrl())
	{
		MessageBox(NULL, L"Не удалось инициализировать общие элементы управления", L"Error", MB_OK);
		return 1;
	}

	if (!register_windowClasses(hInstance))
	{
		MessageBox(NULL, L"Не удалось зарегистрировать класс окна", L"Error", MB_OK);
		return 1;
	}

	/*		Create the main window and show it.		*/
	HWND hWnd = BookmarkManagerWindow::create_bookmarkManagerWindow(hInstance);
	ShowWindow(hWnd, true);
	UpdateWindow(hWnd);

	MSG	msg;
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

ErrorCode initialization_commCtrl() //TODO: Вынести общий знаменатель в функцию.
{
	INITCOMMONCONTROLSEX	commonControl;

	/*		List View		*/
	commonControl.dwSize = sizeof(INITCOMMONCONTROLSEX);
	commonControl.dwICC = ICC_LISTVIEW_CLASSES;

	if (!InitCommonControlsEx(&commonControl))
		return false;

	///*		List View		*/
	//commonControl.dwSize = sizeof(INITCOMMONCONTROLSEX);
	//commonControl.dwICC = ICC_;

	//if (!InitCommonControlsEx(&commonControl))
	//	return false;

	return true;
}

ErrorCode register_windowClasses(HINSTANCE hInstance)
{
	WNDCLASSEX	wndClass = { NULL };

	/*		BookmarkManagerWindow class.		*/
	wndClass.lpszClassName = BOOKMARKMANAGERWND_CLASSNAME;
	wndClass.lpfnWndProc = BookmarkManagerWindow::WndProc;
	wndClass.hInstance = hInstance;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hbrBackground = CreateSolidBrush(RGB(70, 68, 81));
	wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wndClass.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(BKM_ICON_1), IMAGE_ICON, NULL, NULL, LR_SHARED);
	
	if (!RegisterClassEx(&wndClass))
		return false;

	/*		ContainerCreationWindow class.		*/
	wndClass.lpszClassName = CONTAINERCREATIONWND_CLASSNAME;
	wndClass.lpfnWndProc = ContainerCreationWindow::WndProc;
	wndClass.hInstance = hInstance;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hbrBackground = CreateSolidBrush(RGB(70, 68, 81));
	wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);

	if (!RegisterClassEx(&wndClass))
		return false;

	/*		AboutProgramWindow class.		*/
	wndClass.lpszClassName = ABOUTPROGRAMNWND_CLASSNAME;
	wndClass.lpfnWndProc = AboutProgramWindow::WndProc;
	wndClass.hInstance = hInstance;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hbrBackground = CreateSolidBrush(RGB(70, 68, 81));
	wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);

	if (!RegisterClassEx(&wndClass))
		return false;

	return true;
}