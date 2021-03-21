/**
*
*/

#pragma once
#ifndef _CONTAINER_CREATION_WND_EVENTS_
#define _CONTAINER_CREATION_WND_EVENTS_

#include <Windows.h>


LRESULT contCreatWnd_initialization();
LRESULT contCreatWnd_adjustmentControls();
LRESULT contCreatWnd_closeWnd(HWND hWnd, LPARAM);
LRESULT contCreatWnd_setColorStatic(WPARAM);
LRESULT contCreatWnd_applyTag();
LRESULT contCreatWnd_fillContainer();

LRESULT contCreatWnd_enter_pressed();
LRESULT contCreatWnd_delete_pressed();
LRESULT contCreatWnd_tab_pressed();

#endif
