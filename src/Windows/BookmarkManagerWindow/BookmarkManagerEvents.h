/**
* 
*/

#pragma once
#ifndef _BOOKMARK_MANAGER_WND_EVENTS_
#define _BOOKMARK_MANAGER_WND_EVENTS_

#include <Windows.h>


LRESULT bkmManagerWnd_adjustmentControls(HWND hWnd);
LRESULT showCreatedContainer(WPARAM);

LRESULT bkmManagerWnd_ClearMainListView(HWND hWnd);
LRESULT bkmManagerWnd_startСontainer(HWND hWnd);
LRESULT bkmManagerWnd_delete_pressed(HWND hWnd);
LRESULT bkmManagerWnd_addButton_pressed(HWND hWnd);

LRESULT bkmManagerWnd_menu_help_howToUse(HWND hWnd);
LRESULT bkmManagerWnd_menu_help_aboutProg(HWND hWnd);
LRESULT bkmManagerWnd_menu_file_close(HWND hWnd);
LRESULT bkmManagerWnd_menu_file_save();
LRESULT bkmManagerWnd_menu_file_open();

LRESULT bkmManagerWnd_closeProgram(HWND hWnd);
LRESULT bkmManagerWnd_destroyWindow();

#endif
