/**
*		bookmarkManagerWindow is the main window of the application.
*/

#pragma once
#ifndef _BOOKMARK_MANAGER_WND_
#define _BOOKMARK_MANAGER_WND_

#include <Windows.h>


LRESULT CALLBACK BkmManagerProc(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM);
HWND create_bookmarkManagerWindow(HINSTANCE);

#endif
