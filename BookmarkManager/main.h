//TODO: Добавить лицензию

#pragma once
#ifndef _BokMar_
#define _BokMar_

#include "BmDef.h"

#include <iostream>
#include <Windows.h>

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR lpCmdLine, _In_ int nCmdShow);
LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam);

void moveWindowToCenterScreen(HWND hWnd, HWND hWndInsertAfter = HWND_TOP);

#endif // !_BokMar_
