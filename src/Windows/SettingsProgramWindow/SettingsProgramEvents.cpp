#define UNICODE

#include "..\..\ApplicationSettings\ApplicationSettings.h"
#include "..\..\HandleManager\HandleManager.h"
#include "..\..\Common\CommonOperations.h"
#include "..\..\Common\BkmDef.h"
#include "..\..\Common\Debug.h"
#include "..\..\res\res.h"
#include <SaveModule.h>
#include "SettingsProgramEvents.h"


static void ContainerCreationWndBehavior_radioButtons_changeEnable(HWND);

INT_PTR settingsProgWnd_initialization(HWND hDlg)
{
	HWND hTaskTypeComobBox = GetDlgItem(hDlg, BKM_DEFAULTTASKTYPE_COMBOBOX);
	fillComboBoxTaskTypes(hTaskTypeComobBox);

	if (ApplicationSettings::getDefaultTaskType() != TASKTYPE_NOTSPECIFIED)
	{
		CheckDlgButton(hDlg, BKM_DEFAULTTASKTYPE_CHECKBOX, true);
		EnableWindow(hTaskTypeComobBox, true);
		SendMessage(hTaskTypeComobBox, CB_SETCURSEL, ApplicationSettings::getDefaultTaskType(), NULL);
	}


	if (ApplicationSettings::getLaunchMethodContainerCreationWindow() == LaunchMethod::SHOW_CLOSED_WINDOW) {
		CheckDlgButton(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_1, BST_CHECKED);
	}
	else {
		ContainerCreationWndBehavior_radioButtons_changeEnable(hDlg);

		if (ApplicationSettings::getLaunchMethodContainerCreationWindow() == LaunchMethod::CREATE_NEW_WINDOW) {
			CheckDlgButton(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_2, BST_CHECKED);
		}
		else if (ApplicationSettings::getLaunchMethodContainerCreationWindow() == LaunchMethod::CONTINUE_UNFINISHED_CREATION) {
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
static void save();

INT_PTR applySettings(HWND hDlg)
{
	changeDefaultTaskType(hDlg);
	changeStartupMethod(hDlg);
	save();

	return TRUE;
}

static void changeDefaultTaskType(HWND hDlg)
{
	if (IsDlgButtonChecked(hDlg, BKM_DEFAULTTASKTYPE_CHECKBOX) == BST_UNCHECKED) {
		ApplicationSettings::setDefaultTaskType(TASKTYPE_NOTSPECIFIED);
		return;
	}

	HWND hTaskTypeComobBox = GetDlgItem(hDlg, BKM_DEFAULTTASKTYPE_COMBOBOX);
	int index = SendMessage(hTaskTypeComobBox, CB_GETCURSEL, NULL, NULL);
	ApplicationSettings::setDefaultTaskType(index);
}

static void changeStartupMethod(HWND hDlg)
{
	if (IsDlgButtonChecked(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_1) == BST_CHECKED) {
		ApplicationSettings::setLaunchMethodContainerCreationWindow(LaunchMethod::SHOW_CLOSED_WINDOW);
		return;
	}

	if (IsDlgButtonChecked(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_2) == BST_CHECKED) {
		ApplicationSettings::setLaunchMethodContainerCreationWindow(LaunchMethod::CREATE_NEW_WINDOW);

		if (HandleManager::checkExistence(HNAME_CONTAINERCREATIONWND_WND)) {
			HWND hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND);
			SendMessage(hWnd, WM_CLOSE, NULL, NULL);
		}
	}
	else if (IsDlgButtonChecked(hDlg, BKM_ADDCONTAINERWNDBEHAVIOR_3) == BST_CHECKED) {
		ApplicationSettings::setLaunchMethodContainerCreationWindow(LaunchMethod::CONTINUE_UNFINISHED_CREATION);
	}
}

static void save()
{
	Tag mainTag;

	mainTag.setFlag(TSF_SUBTAGS);
	mainTag.setName(L"Settings");
	mainTag.addAttribute(L"SaveVer", SAVEMODULE_VERSIONNAME);
	mainTag.addAttribute(L"BkmVer", BOOKMARKMANAGER_VERSIONNAME);

	Tag* settingsTag[2];
	settingsTag[0] = mainTag.createSubTag(1);
	settingsTag[1] = mainTag.createSubTag(2);
	{
		settingsTag[0]->setFlag(TSF_VALUE);
		settingsTag[0]->setName(L"defaultTaskType");
		settingsTag[0]->setValue(std::to_wstring(ApplicationSettings::getDefaultTaskType()));

		settingsTag[1]->setFlag(TSF_VALUE);
		settingsTag[1]->setName(L"launchMethod_window");
		int launchMethod = static_cast<int>(ApplicationSettings::getLaunchMethodContainerCreationWindow());
		settingsTag[1]->setValue(std::to_wstring(launchMethod));

		mainTag.applySubTags();
	}

	XmlFile newXmlFile;

	newXmlFile.open(L"Settings.bkms", OpenMode::WRITE);
	newXmlFile.write(mainTag);
	newXmlFile.close();
}
