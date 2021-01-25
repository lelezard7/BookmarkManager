//TODO: Add a license

#pragma once
#ifndef _ADDWND_
#define _ADDWND_

#include "GeneralOperations.h"
#include <Windows.h>
#include <CommCtrl.h>

extern HWND addw_wnd;
extern HWND addw_applyButton;
extern HWND addw_nameTextBox;
extern HWND addw_adressTextBox;
extern HWND addw_tagsTextBox;
extern HWND addw_tagslistView;

LRESULT CALLBACK AddWndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam);

HWND addw_createWindow(HWND hWndParent, HINSTANCE hInstance);
HWND addw_createNameTextBox(HINSTANCE hInstance);
HWND addw_createAdressTextBox(HINSTANCE hInstance);
HWND addw_createTagsTextBox(HINSTANCE hInstance);
HWND addw_createApplyButton(HINSTANCE hInstance);
HWND addw_createTagsListView(HINSTANCE hInstance);

#endif // !_ADDWND_