/*
*		Common operations on window and controls are descrided here.
*/

#pragma once
#ifndef _COMMONOPERATIONS_
#define _COMMONOPERATIONS_

#include "Debug.h"
#include <Windows.h>

enum class ClientRectCoordinates;


class CommonOperations
{
	CommonOperations() = delete;

public:
	/*		
	*		moveWindowToCenterScreen moves the window to the center of the screen.
	*		The second parameter specifies the location in Z-order.
	*/
	static void moveWindowToCenterScreen(HWND hWnd, HWND hWndInsertAfter = HWND_TOP);
	static void setMinimumWindowSize(const LONG width, const LONG height, LPARAM lParam);

	/*		
	*		Receives the coordinates of the client area and returns the valuespecified
	*		in the 'ClientRectCoordinates'.
	*		If the function succeeds, the return value is nonzero.
	*		If the function fails, the return value is zero.
	*/
	static LONG getClientRectValue(HWND hWnd, ClientRectCoordinates clientRectCoordinates);
};

enum class ClientRectCoordinates
{
	BOTTOM,
	LEFT,
	TOP,
	RIGHT
};

#endif
