//TODO: Add a license

#pragma once
#ifndef _BmDef_
#define _BmDef_

//TODO: Добавить макросы размеров окон и их позиций

#define MW_MAINCLASSNAME					TEXT("MainWindowClassName")
#define MW_MAINWNDNAME						TEXT("Bookmark Manager")
#define MW_ADDCLASSNAME						TEXT("AddWindowClassName")
#define MW_ADDWNDNAME						TEXT("Bookmark Manager: Add")

#define IDADDBUTTON							11
											
#define MW_MENU_FILE_IDCLOSE				30
#define MW_MENU_FILE_IDSETTINGS				31
#define MW_MENU_HELP_IDHOWTOUSE				32
#define MW_MENU_HELP_IDABOUTPROGRAM			33
											
//TODO: Сделать смену языка
#define MW_MENU_FILESTRING					TEXT("Файл")
#define MW_MENU_HELPSTRING					TEXT("Справка")
#define MW_MENU_FILE_CLOSESTRING			TEXT("Закрыть")
#define MW_MENU_FILE_SETTINGSSTRING			TEXT("Настройка")
#define MW_MENU_HELP_HOWTOUSESTRING			TEXT("Как использовать")
#define MW_MENU_HELP_ABOUTPROGRAMSTRING		TEXT("О программе")

#define SCREENY								(GetSystemMetrics(SM_CYSCREEN) / 2)
#define SCREENX								(GetSystemMetrics(SM_CXSCREEN) / 2)

#endif // !_BmDef_
