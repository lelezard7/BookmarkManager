/*
*		bookmarkManagerWindow is the main window of the application.
*/

#pragma once
#ifndef _BOOKMARKMANAGERWINDOW_
#define _BOOKMARKMANAGERWINDOW_

#include <Windows.h>

namespace BookmarkManagerWindow
{
	LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
	HWND create_bookmarkManagerWindow(HINSTANCE hInstance);

	HMENU create_menu();
	void create_mainListView(HWND hWndParent, HINSTANCE hInstance);
	void create_addButton(HWND hWndParent, HINSTANCE hInstance);
	void create_openButton(HWND hWndParent, HINSTANCE hInstance);
	void create_cleanButton(HWND hWndParent, HINSTANCE hInstance);

	void addButton_pressed();
	void openButton_pressed();

	/*		Resizes and positions controls when the window is resized.		*/
	void adjustmentOfControls(HWND hWnd);

	/*		Displays the created container in mainListView.		*/
	void showCreatedContainer(LPARAM lParam);
}

#endif
