/**
*		Common operations on window and controls are descrided here.
*/

#pragma once
#ifndef _COMMON_OPERATIONS_
#define _COMMON_OPERATIONS_

#include <Windows.h>

enum class ClientRectCoordinates;


void moveWindowToCenterScreen(HWND hWnd, HWND hWndInsertAfter = HWND_TOP);
bool setMinimumWindowSize(const LONG width, const LONG height, LPARAM);

/*		
*		Receives the coordinates of the client area and returns the valuespecified
*		in the 'ClientRectCoordinates'.
*		If the function succeeds, the return value is nonzero.
*		If the function fails, the return value is zero.
*/
LONG getClientRectValue(HWND hWnd, ClientRectCoordinates clientRectCoordinates);
void fillComboBoxTaskTypes(HWND hWnd);


enum class ClientRectCoordinates
{
	BOTTOM,
	LEFT,
	TOP,
	RIGHT
};

#endif
