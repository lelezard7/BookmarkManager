/*
* 
*/

#pragma once
#ifndef _ABOUTPROGRAMWINDOW_
#define _ABOUTPROGRAMWINDOW_

#include <Windows.h>

namespace AboutProgramWindow
{
	LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
	void create_aboutProgramWindow(HINSTANCE hInstance);

}

#endif
