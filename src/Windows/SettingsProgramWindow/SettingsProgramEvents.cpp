#define UNICODE

#include "..\..\ApplicationSettings\ApplicationSettings.h"
#include "..\..\HandleManager\HandleManager.h"
#include "..\..\Common\BkmDef.h"
#include "..\..\Common\Debug.h"
#include "..\..\res\res.h"
#include "SettingsProgramEvents.h"


static void ContainerCreationWndBehavior_radioButtons_changeEnable(HWND);

INT_PTR settingsProgWnd_initialization(HWND hDlg)
{
	HWND hTaskTypeComobBox = GetDlgItem(hDlg, BKM_DEFAULTTASKTYPE_COMBOBOX);
	fillComboBoxTaskTypes(hTaskTypeComobBox);

	if (ApplicationSettings::getDefaultTaskType() != TASKTTYPE_NOTSPECIFIED)
	{
		CheckDlgButton(hDlg, BKM_DEFAULTTASKTYPE_CHECKBOX, true);
		EnableWindow(hTaskTypeComobBox, true);
		SendMessage(hTaskTypeComobBox, CB_SETCURSEL, ApplicationSettings::getDefaultTaskType(), NULL);
	}


	if (ApplicationSettings::getStartupMethodContainerCreationWindow() == StartupMethod::SHOW_CLOSED_WINDOW) {
		CheckDlgButton(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_1, BST_CHECKED);
	}
	else {
		ContainerCreationWndBehavior_radioButtons_changeEnable(hDlg);

		if (ApplicationSettings::getStartupMethodContainerCreationWindow() == StartupMethod::CREATE_NEW_WINDOW) {
			CheckDlgButton(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_2, BST_CHECKED);
		}
		else if (ApplicationSettings::getStartupMethodContainerCreationWindow() == StartupMethod::CONTINUE_UNFINISHED_CREATION) {
			CheckDlgButton(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_3, BST_CHECKED);
		}
	}

	return TRUE;
}

static void ContainerCreationWndBehavior_radioButtons_changeEnable(HWND hDlg)
{
	HWND hRadioButton_1 = GetDlgItem(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_2);
	HWND hRadioButton_2 = GetDlgItem(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_3);

	bool check = IsDlgButtonChecked(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_1) == BST_UNCHECKED;
	EnableWindow(hRadioButton_1, check);
	EnableWindow(hRadioButton_2, check);
}

INT_PTR settingsProgWnd_taskTypeComobBox_changeEnable(HWND hDlg)
{
	HWND hTaskTypeComobBox = GetDlgItem(hDlg, BKM_DEFAULTTASKTYPE_COMBOBOX);

	bool check = IsDlgButtonChecked(hDlg, BKM_DEFAULTTASKTYPE_CHECKBOX) == BST_CHECKED;
	EnableWindow(hTaskTypeComobBox, check);
	PropSheet_Changed(GetParent(hDlg), hDlg);

	return TRUE;
}

INT_PTR settingsProgWnd_applyButton_turnOn(HWND hDlg)
{
	PropSheet_Changed(GetParent(hDlg), hDlg);

	return TRUE;
}

INT_PTR behavior_1_radioButtons_changeEnable(HWND hDlg)
{
	ContainerCreationWndBehavior_radioButtons_changeEnable(hDlg);
	PropSheet_Changed(GetParent(hDlg), hDlg);

	return TRUE;
}



static void changeDefaultTaskType(HWND);
static void changeStartupMethod(HWND);

INT_PTR applySettings(HWND hDlg)
{
	changeDefaultTaskType(hDlg);
	changeStartupMethod(hDlg);

	return TRUE;
}

static void changeDefaultTaskType(HWND hDlg)
{
	if (IsDlgButtonChecked(hDlg, BKM_DEFAULTTASKTYPE_CHECKBOX) == BST_UNCHECKED) {
		ApplicationSettings::setDefaultTaskType(TASKTTYPE_NOTSPECIFIED);
		return;
	}

	HWND hTaskTypeComobBox = GetDlgItem(hDlg, BKM_DEFAULTTASKTYPE_COMBOBOX);
	int index = SendMessage(hTaskTypeComobBox, CB_GETCURSEL, NULL, NULL);
	ApplicationSettings::setDefaultTaskType(index);
}

static void changeStartupMethod(HWND hDlg)
{
	if (IsDlgButtonChecked(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_1) == BST_CHECKED) {
		ApplicationSettings::setStartupMethodContainerCreationWindow(StartupMethod::SHOW_CLOSED_WINDOW);
		return;
	}

	if (IsDlgButtonChecked(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_2) == BST_CHECKED) {
		ApplicationSettings::setStartupMethodContainerCreationWindow(StartupMethod::CREATE_NEW_WINDOW);

		if (HandleManager::checkExistence(HNAME_CONTAINERCREATIONWND_WND)) {
			HWND hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND);
			SendMessage(hWnd, WM_CLOSE, NULL, NULL);
		}
	}
	else if (IsDlgButtonChecked(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_3) == BST_CHECKED) {
		ApplicationSettings::setStartupMethodContainerCreationWindow(StartupMethod::CONTINUE_UNFINISHED_CREATION);
	}
}
