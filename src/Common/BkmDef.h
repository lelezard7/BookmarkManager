#pragma once
#ifndef _BKMDEF_
#define _BKMDEF_

#include "Debug.h"


/*		Application information.		*/
#define BOOKMARKMANAGER_VERSION								0x0003

/*		Class names.		*/
#define CLASSNAME_BOOKMARKMANAGERWND						(L"BookmarkManagerWindow")
#define CLASSNAME_CONTAINERCREATIONWND						(L"ContainerCreationWindow")
#define CLASSNAME_ABOUTPROGRAMNWND							(L"AboutProgramWindow")
#define CLASSNAME_SETTINGSPROGRAMWND						(L"SettingsProgramWindow")

/*		Window names.		*/
#define WNDNAME_BOOKMARKMANAGERNWND							(L"Bookmark Manager")
#define WNDNAME_CONTAINERCREATIONWND						(L"Bookmark Manager: Add")
#define WNDNAME_ABOUTPROGRAMNWND							(L"About Bookmark Manager")
#define WNDNAME_SETTINGSPROGRAMWND							(L"Bookmark Manager: Settings")

/*		ID of window buttons.		*/
#define ID_BOOKMARKMANAGERNWND_ADDBUTTON					11
#define ID_BOOKMARKMANAGERNWND_OPENBUTTON					12
#define ID_BOOKMARKMANAGERNWND_CLEANBUTTON					13
#define ID_CONTAINERCREATIONWND_APPLYBUTTON					14

/*		ID of menu bar buttons.		*/
#define ID_MENU_CLOSEPROGRAM								51
#define ID_MENU_SETTINGSPROGRAM								52
#define ID_MENU_NEWFILE										53
#define ID_MENU_OPENFILE									54
#define ID_MENU_SAVEFILE									55
#define ID_MENU_HOWTOUSE									56
#define ID_MENU_ABOUTPROGRAM								57


/*		Handles names.		*/

//		BookmarkManagerWindow
#define HNAME_BOOKMARKMANAGERNWND_WND						1
#define HNAME_BOOKMARKMANAGERNWND_MainListView				2
#define HNAME_BOOKMARKMANAGERNWND_AddButton					3
#define HNAME_BOOKMARKMANAGERNWND_OpenButton				4
#define HNAME_BOOKMARKMANAGERNWND_ClearButton				5

//		AboutProgramWindow
#define HNAME_ABOUTPROGRAMWND_WND							51

//		ContainerCreationWindow
#define HNAME_CONTAINERCREATIONWND_WND						101
#define HNAME_CONTAINERCREATIONWND_TaskTypeDropDList		102
#define HNAME_CONTAINERCREATIONWND_NameTextBox				103
#define HNAME_CONTAINERCREATIONWND_AdressTextBox			104
#define HNAME_CONTAINERCREATIONWND_TagsTextBox				105
#define HNAME_CONTAINERCREATIONWND_ApplyButton				106
#define HNAME_CONTAINERCREATIONWND_TagsListView				107

//		SettingsProgramWindow
#define HNAME_SETTINGSPROGRAMWND_WND						151
#define HNAME_SETTINGSPROGRAMWND_NavigationPanel			152
#define HNAME_SETTINGSPROGRAMWND_EnableTaskTypeCheckBox		153
#define HNAME_SETTINGSPROGRAMWND_TaskTypeDropDList			154


/*		User messages.		*/
#define UM_SHOWCREATEDCONTAINER								(WM_USER + 0x0002)

/*		Other.		*/
#define CENTERSCREEN_X										(GetSystemMetrics(SM_CXSCREEN) / 2)
#define CENTERSCREEN_Y										(GetSystemMetrics(SM_CYSCREEN) / 2)

#endif
