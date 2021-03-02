/*
*		ContainerCreationWindow is the window in which the user creates the container.
*		What is a container and what is included in it, see Archive.h (src/Archive/Archive.h)											
*/

#pragma once
#ifndef _ADDITEMSWINDOW_
#define _ADDITEMSWINDOW_

#include "..\..\Common\Debug.h"
#include "..\..\Archive\Archive.h"
#include "..\..\HandleManager\HandleManager.h"
#include <Windows.h>


namespace ContainerCreationWindow
{
	LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
	void create_containerCreationWindow(HINSTANCE hInstance);

	void create_taskTypeDropDList(HWND hWndParent, HINSTANCE hInstance);
	void create_nameTextBox(HWND hWndParent, HINSTANCE hInstance);
	void create_adressTextBox(HWND hWndParent, HINSTANCE hInstance);
	void create_tagsTextBox(HWND hWndParent, HINSTANCE hInstance);
	void create_applyButton(HWND hWndParent, HINSTANCE hInstance);
	void create_tagsListView(HWND hWndParent, HINSTANCE hInstance);

	/*
	*		Creates a container, fills it, adds it to Archive and
	*		sends an UM_SHOWCREATEDCONTAINER message to the bookmarkManagerWindow -> WndProc.
	*		The unique id of created container is sent as lParam.
	*		About id, see Archive.h (src/Archive/Archive.h)
	*/
	void fill_container();

	//		Called 'fill_container' function. Fills the container with data from Text Boxes.
	bool setDataFromTextBox(HandleName hTextBoxName, ContainerDataTypes dataType, Container& container);

	//		Resizes and positions controls when the window is resized.
	void adjustmentOfControls();
	LRESULT close_window(HWND hWnd);
}

#endif
