#pragma once
#ifndef _BKMDEF_
#define _BKMDEF_

#include "Debug.h"


/*		Application information.		*/
#define BOOKMARKMANAGER_VERSION								0004
#define BOOKMARKMANAGER_VERSIONNAME							(L"0.0.0.4")

/*		Class names.		*/
#define CLASSNAME_BOOKMARKMANAGERWND						(L"BookmarkManagerWindow")
#define CLASSNAME_CONTAINERCREATIONWND						(L"ContainerCreationWindow")

/*		Window names.		*/
#define WNDNAME_BOOKMARKMANAGERNWND							(L"Bookmark Manager")
#define WNDNAME_CONTAINERCREATIONWND						(L"Bookmark Manager: Add")

/*		ID of window buttons.		*/
#define ID_BOOKMARKMANAGERWND_ADDBUTTON						11
#define ID_BOOKMARKMANAGERWND_OPENBUTTON					12
#define ID_BOOKMARKMANAGERWND_CLEARBUTTON					13
#define ID_CONTAINERCREATIONWND_APPLYBUTTON					14
#define ID_CONTAINERCREATIONWND_APPLYTAGBUTTON				15


/*		Handles names.		*/

//		BookmarkManagerWindow
#define HNAME_BOOKMARKMANAGERWND_WND						1
#define HNAME_BOOKMARKMANAGERWND_MainListView				2
#define HNAME_BOOKMARKMANAGERWND_AddButton					3
#define HNAME_BOOKMARKMANAGERWND_OpenButton					4
#define HNAME_BOOKMARKMANAGERWND_ClearButton				5

//		ContainerCreationWindow
#define HNAME_CONTAINERCREATIONWND_WND						51
#define HNAME_CONTAINERCREATIONWND_TaskTypeDropDList		52
#define HNAME_CONTAINERCREATIONWND_NameTextBox				53
#define HNAME_CONTAINERCREATIONWND_AdressTextBox			54
#define HNAME_CONTAINERCREATIONWND_TagsTextBox				55
#define HNAME_CONTAINERCREATIONWND_ApplyButton				56
#define HNAME_CONTAINERCREATIONWND_TagsListView				57
#define HNAME_CONTAINERCREATIONWND_ApplyTagButton			58
#define HNAME_CONTAINERCREATIONWND_TaskTypeHelpText			59

/*		User messages.		*/
#define UM_SHOWCREATEDCONTAINER								(WM_USER + 0x0002)

/*		Other.		*/
#define CENTERSCREEN_X										(GetSystemMetrics(SM_CXSCREEN) / 2)
#define CENTERSCREEN_Y										(GetSystemMetrics(SM_CYSCREEN) / 2)

#endif
