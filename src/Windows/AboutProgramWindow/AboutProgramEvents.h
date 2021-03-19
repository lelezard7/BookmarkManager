/**
* 
*/

#pragma once
#ifndef _ABOUT_PROGRAM_WND_EVENTS_
#define _ABOUT_PROGRAM_WND_EVENTS_

#include <Windows.h>


INT_PTR aboutProgWnd_initialization(HWND hDlg);
INT_PTR aboutProgWnd_setColorDlg();
INT_PTR aboutProgWnd_setColorStatic(WPARAM, LPARAM);
INT_PTR aboutProgWnd_setColorBtn(WPARAM);

INT_PTR aboutProgWnd_closeDlg(HWND hDlg);
INT_PTR aboutProgWnd_openLink(HWND hDlg, LPARAM);

#endif
