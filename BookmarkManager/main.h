//TODO: Add a license

#pragma once
#ifndef _MAINWND_
#define _MAINWND_
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "BmDef.h"
#include "AddWindow.h"
#include "GeneralOperations.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <CommCtrl.h>

HWND mw_listView;
HWND mw_addButton;
HWND mw_openButton;
HWND mw_cleanButton;

//extern (AddWindow)
HWND addw_wnd;
HWND addw_applyButton;
HWND addw_nameTextBox;
HWND addw_adressTextBox;
HWND addw_tagsTextBox;
HWND addw_tagslistView;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR lpCmdLine, _In_ int nCmdShow);
LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam);

HMENU mw_createMenu();
HWND mw_createListView(HWND hWndParent, HINSTANCE hInstance);
HWND mw_createAddButton(HWND hWndParent, HINSTANCE hInstance);
HWND mw_createOpenButton(HWND hWndParent, HINSTANCE hInstance);
HWND mw_createCleanButton(HWND hWndParent, HINSTANCE hInstance);

#endif // !_MAINWND_
