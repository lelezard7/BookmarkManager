/*
* 
*/

#pragma once
#ifndef _SETTINGSPROGRAMWINDOW_
#define _SETTINGSPROGRAMWINDOW_

#include <Windows.h>


namespace SettingsProgramWindow
{
	LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
	void create_settingsProgramWindow(HINSTANCE hInstance);

	void create_navigationPanel(HWND hWndParent, HINSTANCE hInstance);
		void create_taskTypeDropDList(HWND hWndParent, HINSTANCE hInstance);
		void create_enableTaskTypeCheckBox(HWND hWndParent, HINSTANCE hInstance);

	//		Resizes and positions controls when the window is resized.
	void adjustmentOfControls();
}

#endif
