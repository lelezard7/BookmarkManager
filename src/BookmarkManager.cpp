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
static bool register_windowClasses(HINSTANCE hInstance);
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

	initialization_settings();

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
	//XmlFile file;
	//file.open(L"dfd.bkm", OpenMode::WRITE);
	//file.

	//file.open(L"dfd.bkm", OpenMode::WRITE);

	//XmlFile file2;
	//file2.open(L"dfd.bkm", OpenMode::WRITE);

	//XmlFile file3;
	//file3.open(L"dfd.bkm", OpenMode::APPEND);










	//XmlFile newXmlFile;

	//if (newXmlFile.open(L"Settings.bkms", OpenMode::READ)) //TODO: Проверять существование файла
	//{
	//	TagStructure* mainTag = newXmlFile.read();
	//	newXmlFile.close(L"Settings.bkms");

	//	TagStructure filter;
	//	TagPath searchTag;
	//	searchTag.setTagStructure(*mainTag);

	//	filter.setTag("defaultTaskType");
	//	searchTag.setFlags(TPF_TAG);
	//	SearchResult searchResult = searchTag.search(filter);
	//	ApplicationSettings::setDefaultTaskType(std::stoi(searchResult[0]->getValue()));

	//	filter.setTag("launchMethod_window");
	//	searchTag.setFlags(TPF_TAG);
	//	searchResult = searchTag.search(filter);
	//	ApplicationSettings::setLaunchMethodContainerCreationWindow((LaunchMethod)std::stoi(searchResult[0]->getValue()));
	//}

	return true;
}
