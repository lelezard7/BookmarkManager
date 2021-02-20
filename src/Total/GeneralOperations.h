/*
*		General operations on window and controls are descrided here.
*/

#pragma once
#ifndef _GENERALOPERATIONS_
#define _GENERALOPERATIONS_

#include <Windows.h>


class GeneralOperations
{
	GeneralOperations() = delete;

public:
	/*		
	*		moveWindowToCenterScreen moves the window to the center of the screen.
	*		The second parameter specifies the location in Z-order.
	*/
	static void moveWindowToCenterScreen(HWND hWnd, HWND hWndInsertAfter = HWND_TOP);
	static void setMinimumWindowSize(LONG width, LONG height, LPARAM lParam);
};

#endif
