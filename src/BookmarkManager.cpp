//TODO: Add a license
//TODO: Удалить 'pragma comment'

/*
*		General requirements:
*				1) The name of the .h file must be equal to the name of the .cpp file.
*/

/*
*		BookmarkManager.cpp initiates common controls, registers window classes.
*		Then creates the main window and displays it. Finally, it triggers a message loop.
*/

#define UNICODE

#include "Windows\ContainerCreationWindow\ContainerCreationWindow.h"
#include "Windows\BookmarkManagerWindow\BookmarkManagerWindow.h"
#include "ApplicationSettings\ApplicationSettings.h"
#include "Archive\TaskTypesCollection.h"
#include "HandleManager\HandleManager.h"
#include "Common\BkmDef.h"
#include "Common\Debug.h"
#include "res\res.h"
#include <SaveModule.h>
#include <Windows.h>
#include <CommCtrl.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


static bool initialization_commCtrl();
static bool register_windowClasses(HINSTANCE);
static bool initialization_settings();

INT WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	if (!initialization_commCtrl()) {
		MessageBox(NULL, L"Не удалось инициализировать общие элементы управления", L"Bookmark Manager", MB_OK);
		return 1;
	}

	if (!register_windowClasses(hInstance)) {
		MessageBox(NULL, L"Не удалось зарегистрировать класс окна", L"Bookmark Manager", MB_OK);
		return 1;
	}

	TaskTypesCollection::addTaskType(L"URL");
	TaskTypesCollection::addTaskType(L"Программа");

	if (!initialization_settings()) {
		ApplicationSettings::restoreDefaultSettings();
	}

	HWND hWnd = create_bookmarkManagerWindow(hInstance, pCmdLine);
	ShowWindow(hWnd, true);
	UpdateWindow(hWnd);

	MSG	msg;
	HACCEL accel = LoadAccelerators(hInstance, MAKEINTRESOURCE(BKM_ACCELERATOR));
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		if (HandleManager::checkExistence(HNAME_CONTAINERCREATIONWND_WND))
		{
			HWND hCreatContainerWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND);

			if (GetActiveWindow() == hCreatContainerWnd)
				if (TranslateAccelerator(hCreatContainerWnd, accel, &msg))
					continue;
		}

		if (TranslateAccelerator(hWnd, accel, &msg))
			continue;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	TaskTypesCollection::clear();
	return (int)msg.wParam;
}

static bool initialization_commCtrl()
{
	INITCOMMONCONTROLSEX	commonControl;

	/*		ListView Control		*/
	commonControl.dwSize = sizeof(INITCOMMONCONTROLSEX);
	commonControl.dwICC = ICC_LISTVIEW_CLASSES;
	if (!InitCommonControlsEx(&commonControl))
		return false;

	/*		SysLink Control		*/
	commonControl.dwSize = sizeof(INITCOMMONCONTROLSEX);
	commonControl.dwICC = ICC_LINK_CLASS;
	if (!InitCommonControlsEx(&commonControl))
		return false;

	return true;
}

static bool register_windowClasses(HINSTANCE hInstance)
{
	WNDCLASSEX	wndClass = { NULL };

	/*		BookmarkManagerWindow class.		*/
	wndClass.lpszClassName = CLASSNAME_BOOKMARKMANAGERWND;
	wndClass.lpfnWndProc = BkmManagerProc;
	wndClass.hInstance = hInstance;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hbrBackground = CreateSolidBrush(COLOR_BK);
	wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wndClass.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(BKM_ICON_1), IMAGE_ICON, NULL, NULL, LR_SHARED);
	
	if (!RegisterClassEx(&wndClass))
		return false;

	/*		ContainerCreationWindow class.		*/
	wndClass.lpszClassName = CLASSNAME_CONTAINERCREATIONWND;
	wndClass.lpfnWndProc = ContainerCreatProc;
	wndClass.hInstance = hInstance;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hbrBackground = CreateSolidBrush(COLOR_BK);
	wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);

	if (!RegisterClassEx(&wndClass))
		return false;

	return true;
}

static bool initialization_settings()
{
	XmlFile newXmlFile;
	if (!newXmlFile.open(L"Settings.bkms"))
		return true;

	Tag rootTag = newXmlFile.read();
	newXmlFile.close();

	if (rootTag == Tag())
		return true;


	Tag filterTag;
	XmlFilter filter;

	filter.setTarget(rootTag);
	filter.setFlags(XFF_NAME);


	filterTag.setName(L"defaultTaskType");
	filter.setFilter(filterTag);

	SearchResult searchResult = filter.search();
	if (searchResult == SearchResult())
		return false;

	Tag tag = searchResult.getTag(0);
	if (tag == Tag())
		return false;

	ApplicationSettings::setDefaultTaskType(std::stoi(tag.getValue()));


	filterTag.setName(L"launchMethod_window");
	filter.setFilter(filterTag);

	searchResult = filter.search();
	if (searchResult == SearchResult())
		return false;

	tag = searchResult.getTag(0);
	if (tag == Tag())
		return false;

	ApplicationSettings::setLaunchMethodContainerCreationWindow((LaunchMethod)std::stoi(tag.getValue()));

	return true;
}
