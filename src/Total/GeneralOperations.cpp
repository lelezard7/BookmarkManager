#ifndef UNICODE
#define UNICODE
#endif

#include "GeneralOperations.h"
#include "BmDef.h"


void GeneralOperations::moveWindowToCenterScreen(HWND hWnd, HWND hWndInsertAfter)
{
	RECT rect;
	GetWindowRect(hWnd, &rect);

	SetWindowPos(hWnd, hWndInsertAfter,
		CENTERSCREEN_X - ((rect.right - rect.left) / 2),
		CENTERSCREEN_Y - ((rect.bottom - rect.top) / 2),
		NULL, NULL, SWP_NOSIZE);
}

void GeneralOperations::setMinimumWindowSize(LONG width, LONG height, LPARAM lParam)
{
	LPMINMAXINFO lpminmaxinfo = (LPMINMAXINFO)lParam;
	lpminmaxinfo->ptMinTrackSize.x = width;
	lpminmaxinfo->ptMinTrackSize.y = height;
}
