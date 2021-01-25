#include "GeneralOperations.h"

void moveWindowToCenterScreen(HWND hWnd, HWND hWndInsertAfter)
{
	RECT rect;

	GetWindowRect(hWnd, &rect);
	SetWindowPos(hWnd, hWndInsertAfter, SCREENX - ((rect.right - rect.left) / 2), SCREENY - ((rect.bottom - rect.top) / 2), NULL, NULL, SWP_NOSIZE);
}