#define UNICODE

#include "..\..\Common\Debug.h"
#include "..\..\res\res.h"
#include "AboutProgramWindow.h"
#include "AboutProgramEvents.h"
#include <CommCtrl.h>


INT_PTR CALLBACK AboutProc(_In_ HWND hDlg, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:			return aboutProgWnd_initialization(hDlg);
	case WM_CTLCOLORDLG:		return aboutProgWnd_setColorDlg();
	case WM_CTLCOLORSTATIC:		return aboutProgWnd_setColorStatic(wParam, lParam);
	case WM_CTLCOLORBTN:		return aboutProgWnd_setColorBtn(wParam);

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ABOUTWND_OK:
		case IDCANCEL:			return aboutProgWnd_closeDlg(hDlg);
		}
	}

	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
		case NM_CLICK:			return aboutProgWnd_openLink(hDlg, lParam);
		}
	}

	default:	return FALSE;
	}
}
