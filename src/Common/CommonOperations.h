/*
*		Common operations on window and controls are descrided here.
*/

#pragma once
#ifndef _COMMONOPERATIONS_
#define _COMMONOPERATIONS_

#include <Windows.h>


class CommonOperations
{
	CommonOperations() = delete;

public:
	/*		
	*		moveWindowToCenterScreen moves the window to the center of the screen.
	*		The second parameter specifies the location in Z-order.
	*/
	static void moveWindowToCenterScreen(HWND hWnd, HWND hWndInsertAfter = HWND_TOP);
	static void setMinimumWindowSize(LONG width, LONG height, LPARAM lParam);
};

#endif
