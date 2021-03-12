#define UNICODE

#include "AboutProgramWindow.h"
#include "..\..\HandleManager\HandleManager.h"
#include "..\..\Common\CommonOperations.h"
#include "..\..\Common\BkmDef.h"
#include "..\..\res\res.h"
#include <CommCtrl.h>

#define COLORBK			(RGB(70, 68, 81))
#define COLORBKSYSLINK	(RGB(136, 68, 81))
#define COLORTEXT		(RGB(255, 255, 255))

static HGDIOBJ colorBk;
static HGDIOBJ colorBkSysLink;


INT_PTR CALLBACK AboutProgramWindow::DlgProc(_In_ HWND hDlg, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG: {
		std::wstring newText = L"Bookmark Manager: version " + std::wstring(BOOKMARKMANAGER_VERSIONNAME);
		SetDlgItemText(hDlg, ABOUTWND_TEXT_1, newText.c_str());

		colorBk = CreateSolidBrush(COLORBK);
		colorBkSysLink = CreateSolidBrush(COLORBKSYSLINK);
		return TRUE;
	}

	case WM_CTLCOLORDLG: {
		return (INT_PTR)colorBk;
	}

	case WM_CTLCOLORSTATIC: {
		SetTextColor((HDC)wParam, COLORTEXT);

		int id = GetWindowLongPtr((HWND)lParam, GWL_ID);
		if (id == ABOUTWND_SYSLINK_1)
		{
			SetBkColor((HDC)wParam, COLORBKSYSLINK);
			return (INT_PTR)colorBkSysLink;
		}

		SetBkColor((HDC)wParam, COLORBK);
		return (INT_PTR)colorBk;
	}

	case WM_CTLCOLORBTN: {
		SetBkColor((HDC)wParam, COLORBK);
		return (INT_PTR)colorBk;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case ABOUTWND_OK:
		case IDCANCEL: {
			EndDialog(hDlg, NULL);
			DeleteObject(colorBk);
			DeleteObject(colorBkSysLink);
			return TRUE;
		}
		}
	}

	case WM_NOTIFY: {
		switch (((LPNMHDR)lParam)->code)
		{
		case NM_CLICK: {
			PNMLINK pnmlink = (PNMLINK)lParam;
			LITEM   item = pnmlink->item;
			ShellExecute(NULL, L"open", item.szUrl, NULL, NULL, SW_SHOW);
			return TRUE;
		}
		}
	}
	}
	return FALSE;
}
