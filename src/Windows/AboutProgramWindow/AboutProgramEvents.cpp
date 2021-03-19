#define UNICODE

#include "..\..\Common\BkmDef.h"
#include "..\..\Common\Debug.h"
#include "..\..\res\res.h"
#include "AboutProgramEvents.h"
#include <CommCtrl.h>

static HGDIOBJ color_bk;
static HGDIOBJ color_bk_sysLink;


INT_PTR aboutProgWnd_initialization(HWND hDlg)
{
	std::wstring newText = L"Bookmark Manager: âåðñèÿ " + std::wstring(BOOKMARKMANAGER_VERSIONNAME);
	SetDlgItemText(hDlg, ABOUTWND_TEXT_1, newText.c_str());

	color_bk = CreateSolidBrush(COLOR_BK);
	color_bk_sysLink = CreateSolidBrush(COLOR_BK_SYSLINK);

	return TRUE;
}

INT_PTR aboutProgWnd_setColorDlg()
{
	return (INT_PTR)color_bk;
}

INT_PTR aboutProgWnd_setColorStatic(WPARAM wParam, LPARAM lParam)
{
	SetTextColor((HDC)wParam, COLOR_TEXT);

	int id = GetWindowLongPtr((HWND)lParam, GWL_ID);
	if (id == ABOUTWND_SYSLINK_1)
	{
		SetBkColor((HDC)wParam, COLOR_BK_SYSLINK);
		return (INT_PTR)color_bk_sysLink;
	}

	SetBkColor((HDC)wParam, COLOR_BK);
	return (INT_PTR)color_bk;
}

INT_PTR aboutProgWnd_setColorBtn(WPARAM wParam)
{
	SetBkColor((HDC)wParam, COLOR_BK);
	return (INT_PTR)color_bk;
}

INT_PTR aboutProgWnd_closeDlg(HWND hDlg)
{
	EndDialog(hDlg, NULL);
	DeleteObject(color_bk);
	DeleteObject(color_bk_sysLink);

	return TRUE;
}

INT_PTR aboutProgWnd_openLink(HWND hDlg, LPARAM lParam)
{
	PNMLINK pnmlink = (PNMLINK)lParam;
	LITEM   litem = pnmlink->item;

	HINSTANCE errCode = ShellExecute(NULL, L"open", litem.szUrl, NULL, NULL, SW_SHOW);
	if ((int)errCode <= 32) {
		std::wstring errMessage = L"Ñould not open link: " + std::wstring(litem.szUrl) +
			L"\nError code: " + std::to_wstring((int)errCode);
		MessageBox(hDlg, errMessage.c_str(), L"Bookmark Manager", MB_OK | MB_ICONWARNING);
	}

	return TRUE;
}
