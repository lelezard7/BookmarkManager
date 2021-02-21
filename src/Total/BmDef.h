#pragma once
#ifndef _BMDEF_
#define _BMDEF_

/*		Application information.		*/
#define BOOKMARKMANAGER_VERSION					0x0003

/*		Class names.		*/
#define BOOKMARKMANAGERWND_CLASSNAME			(L"BookmarkManagerWindow")
#define CONTAINERCREATIONWND_CLASSNAME			(L"ContainerCreationWindow")
#define ABOUTPROGRAMNWND_CLASSNAME				(L"AboutProgramWindow")

/*		Window names.		*/
#define BOOKMARKMANAGERNWND_WNDNAME				(L"Bookmark Manager")
#define CONTAINERCREATIONWND_WNDNAME			(L"Bookmark Manager: Add")
#define ABOUTPROGRAMNWND_WNDNAME				(L"Bookmark Manager: About program")

/*		ID of window buttons.		*/
#define ID_BOOKMARKMANAGERNWND_ADDBUTTON		11
#define ID_BOOKMARKMANAGERNWND_OPENBUTTON		12
#define ID_BOOKMARKMANAGERNWND_CLEANBUTTON		13
#define ID_CONTAINERCREATIONWND_APPLYBUTTON		14

/*		ID of menu bar buttons.		*/
#define ID_MENU_CLOSEPROGRAM					30
#define ID_MENU_SETTINGSPROGRAM					31
#define ID_MENU_HOWTOUSE						32
#define ID_MENU_ABOUTPROGRAM					33

/*		User messages.		*/
#define UM_SHOWCREATEDCONTAINER					(WM_USER + 0x0001)

/*		Other.		*/
#define CENTERSCREEN_X							(GetSystemMetrics(SM_CXSCREEN) / 2)
#define CENTERSCREEN_Y							(GetSystemMetrics(SM_CYSCREEN) / 2)

#endif
