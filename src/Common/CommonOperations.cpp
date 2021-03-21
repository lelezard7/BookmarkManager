#define UNICODE

#include "..\HandleManager\HandleManager.h"
#include "..\Archive\TaskTypesCollection.h"
#include "CommonOperations.h"
#include "BkmDef.h"
#include "Debug.h"
#include <CommCtrl.h>


void moveWindowToCenterScreen(HWND hWnd, HWND hWndInsertAfter)
{
	RECT rect;
	GetWindowRect(hWnd, &rect);

	SetWindowPos(hWnd, hWndInsertAfter,
		CENTERSCREEN_X - ((rect.right - rect.left) / 2),
		CENTERSCREEN_Y - ((rect.bottom - rect.top) / 2),
		NULL, NULL, SWP_NOSIZE);
}

bool setMinimumWindowSize(const LONG width, const LONG height, LPARAM lParam)
{
	LPMINMAXINFO lpminmaxinfo = (LPMINMAXINFO)lParam;
	lpminmaxinfo->ptMinTrackSize.x = width;
	lpminmaxinfo->ptMinTrackSize.y = height;

	return true;
}

LONG getClientRectValue(HWND hWnd, ClientRectCoordinates clientRectCoordinates)
{
	RECT rect;

	if (!GetClientRect(hWnd, &rect))
		return 0;

	switch (clientRectCoordinates)
	{
	case ClientRectCoordinates::BOTTOM:	return rect.bottom;
	case ClientRectCoordinates::LEFT:	return rect.left;
	case ClientRectCoordinates::TOP:	return rect.top;
	case ClientRectCoordinates::RIGHT:	return rect.right;
	}

	return 0;
}

void fillComboBoxTaskTypes(HWND hWnd)
{
	for (size_t i = 0; i < TaskTypesCollection::size(); i++) {
		PWSTR taskType = TaskTypesCollection::getTaskTypeName(i);
		SendMessage(hWnd, CB_INSERTSTRING, -1, (LPARAM)taskType);
	}
}
