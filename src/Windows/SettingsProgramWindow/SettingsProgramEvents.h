/**
* 
*/

#pragma once
#ifndef _SETTINGS_PROGRAM_WND_EVENTS
#define _SETTINGS_PROGRAM_WND_EVENTS

#include <Windows.h>


INT_PTR settingsProgWnd_initialization(HWND hDlg);
INT_PTR settingsProgWnd_taskTypeComobBox_changeEnable(HWND hDlg);
INT_PTR settingsProgWnd_applyButton_turnOn(HWND hDlg);
INT_PTR behavior_1_radioButtons_changeEnable(HWND hDlg);
INT_PTR applySettings(HWND hDlg);

#endif
