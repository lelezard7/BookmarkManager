#define UNICODE

#include "CommonOperations.h"
#include "BkmDef.h"


void CommonOperations::moveWindowToCenterScreen(HWND hWnd, HWND hWndInsertAfter)
{
	RECT _rect;
	GetWindowRect(hWnd, &_rect);

	SetWindowPos(hWnd, hWndInsertAfter,
		CENTERSCREEN_X - ((_rect.right - _rect.left) / 2),
		CENTERSCREEN_Y - ((_rect.bottom - _rect.top) / 2),
		NULL, NULL, SWP_NOSIZE);
}

void CommonOperations::setMinimumWindowSize(const LONG width, const LONG height, LPARAM lParam)
{
	LPMINMAXINFO _lpminmaxinfo = (LPMINMAXINFO)lParam;
	_lpminmaxinfo->ptMinTrackSize.x = width;
	_lpminmaxinfo->ptMinTrackSize.y = height;
}

LONG CommonOperations::getClientRectValue(HWND hWnd, ClientRectCoordinates clientRectCoordinates)
{
	RECT _rect;

	if (!GetClientRect(hWnd, &_rect))
		return 0;

	switch (clientRectCoordinates)
	{
	case ClientRectCoordinates::BOTTOM: {
		return _rect.bottom;
	}

	case ClientRectCoordinates::LEFT: {
		return _rect.left;
	}

	case ClientRectCoordinates::RIGHT: {
		return _rect.right;
	}

	case ClientRectCoordinates::TOP: {
		return _rect.top;
	}
	}

	return 0;
}
