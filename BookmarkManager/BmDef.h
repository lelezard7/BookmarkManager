//TODO: Add a license

#pragma once
#ifndef _BmDef_
#define _BmDef_

//TODO: �������� ������� �������� ���� � �� �������

#define MW_MAINCLASSNAME					TEXT("MainWindowClassName")
#define MW_MAINWNDNAME						TEXT("Bookmark Manager")
#define MW_ADDCLASSNAME						TEXT("AddWindowClassName")
#define MW_ADDWNDNAME						TEXT("Bookmark Manager: Add")

#define IDADDBUTTON							11
											
#define MW_MENU_FILE_IDCLOSE				30
#define MW_MENU_FILE_IDSETTINGS				31
#define MW_MENU_HELP_IDHOWTOUSE				32
#define MW_MENU_HELP_IDABOUTPROGRAM			33
											
//TODO: ������� ����� �����
#define MW_MENU_FILESTRING					TEXT("����")
#define MW_MENU_HELPSTRING					TEXT("�������")
#define MW_MENU_FILE_CLOSESTRING			TEXT("�������")
#define MW_MENU_FILE_SETTINGSSTRING			TEXT("���������")
#define MW_MENU_HELP_HOWTOUSESTRING			TEXT("��� ������������")
#define MW_MENU_HELP_ABOUTPROGRAMSTRING		TEXT("� ���������")

#define SCREENY								(GetSystemMetrics(SM_CYSCREEN) / 2)
#define SCREENX								(GetSystemMetrics(SM_CXSCREEN) / 2)

#endif // !_BmDef_
