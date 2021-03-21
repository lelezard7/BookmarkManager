#define UNICODE

#include "..\..\ApplicationSettings\ApplicationSettings.h"
#include "..\..\Common\PositionAndSizeControls.h"
#include "..\..\HandleManager\HandleManager.h"
#include "..\..\Archive\Archive.h"
#include "..\..\Common\BkmDef.h"
#include "..\..\Common\Debug.h"
#include "ContainerCreationEvents.h"
#include <CommCtrl.h>

static HBRUSH color_bk;


LRESULT contCreatWnd_initialization()
{
	color_bk = CreateSolidBrush(COLOR_BK);
	return 0;
}

LRESULT contCreatWnd_adjustmentControls()
{
	HWND hApplyButton = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_APPLYBUTTON);
	HWND hNameTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_NAMETEXTBOX);
	HWND hTaskTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TASKTEXTBOX);
	HWND hTagsTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TAGSTEXTBOX);
	HWND hTagsListView = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TAGSLISTVIEW);
	HWND hTaskTypeComboBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TASKTYPECOMBOBOX);
	HWND hApplyTagButton = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_APPLYTAGBUTTON);
	HWND hTaskTypeHelpText = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TASKTYPEHELPTEXT);

	SetWindowPos(hApplyButton, HWND_TOP, ContainerCreationWnd_ApplyButton_X,
		ContainerCreationWnd_ApplyButton_Y,
		ContainerCreationWnd_ApplyButton_Width,
		ContainerCreationWnd_ApplyButton_Height, NULL);
	SetWindowPos(hNameTextBox, HWND_TOP, ContainerCreationWnd_NameTextBox_X,
		ContainerCreationWnd_NameTextBox_Y,
		ContainerCreationWnd_NameTextBox_Width,
		ContainerCreationWnd_NameTextBox_Height, NULL);
	SetWindowPos(hTaskTextBox, HWND_TOP, ContainerCreationWnd_TaskTextBox_X,
		ContainerCreationWnd_TaskTextBox_Y,
		ContainerCreationWnd_TaskTextBox_Width,
		ContainerCreationWnd_TaskTextBox_Height, NULL);
	SetWindowPos(hTagsTextBox, HWND_TOP, ContainerCreationWnd_TagsTextBox_X,
		ContainerCreationWnd_TagsTextBox_Y,
		ContainerCreationWnd_TagsTextBox_Width,
		ContainerCreationWnd_TagsTextBox_Height, NULL);
	SetWindowPos(hTagsListView, HWND_TOP, ContainerCreationWnd_TagsListView_X,
		ContainerCreationWnd_TagsListView_Y,
		ContainerCreationWnd_TagsListView_Width,
		ContainerCreationWnd_TagsListView_Height, NULL);
	SetWindowPos(hTaskTypeComboBox, HWND_TOP, ContainerCreationWnd_TaskTypeComboBox_X,
		ContainerCreationWnd_TaskTypeComboBox_Y,
		ContainerCreationWnd_TaskTypeComboBox_Width,
		ContainerCreationWnd_TaskTypeComboBox_Height, NULL);
	SetWindowPos(hApplyTagButton, HWND_TOP, ContainerCreationWnd_ApplyTagButton_X,
		ContainerCreationWnd_ApplyTagButton_Y,
		ContainerCreationWnd_ApplyTagButton_Width,
		ContainerCreationWnd_ApplyTagButton_Height, NULL);
	SetWindowPos(hTaskTypeHelpText, HWND_TOP, ContainerCreationWnd_TaskTypeHelpText_X,
		ContainerCreationWnd_TaskTypeHelpText_Y,
		ContainerCreationWnd_TaskTypeHelpText_Width,
		ContainerCreationWnd_TaskTypeHelpText_Height, NULL);

	ListView_SetColumnWidth(hTagsListView, 0, ContainerCreationWnd_TagsListView_Width);

	return 0;
}

LRESULT contCreatWnd_closeWnd(HWND hWnd, LPARAM lParam)
{
	HWND hWndParent = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_WND);
	EnableWindow(hWndParent, true);
	SetFocus(hWndParent);

	LaunchMethod launchMethod = ApplicationSettings::getLaunchMethodContainerCreationWindow();

	if (launchMethod == LaunchMethod::CREATE_NEW_WINDOW ||
		(lParam == APPLYBUTTON_PRESSED &&
			launchMethod == LaunchMethod::CONTINUE_UNFINISHED_CREATION))
	{
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TASKTYPECOMBOBOX);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_NAMETEXTBOX);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_APPLYBUTTON);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TASKTEXTBOX);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TAGSTEXTBOX);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TAGSLISTVIEW);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_APPLYTAGBUTTON);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TASKTYPEHELPTEXT);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_WND);
		DestroyWindow(hWnd);
		DeleteObject(color_bk);
	}
	else {
		ShowWindow(hWnd, false);
	}

	return 0;
}

LRESULT contCreatWnd_setColorStatic(WPARAM wParam)
{
	SetBkColor((HDC)wParam, COLOR_BK);
	SetTextColor((HDC)wParam, COLOR_TEXT);

	return (LRESULT)color_bk;
}

LRESULT contCreatWnd_applyTag()
{
	HWND	hTagsTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TAGSTEXTBOX);
	size_t	length = GetWindowTextLength(hTagsTextBox) + (size_t)1;
	PWSTR	buffer = new WCHAR[length];

	GetWindowText(hTagsTextBox, buffer, length);

	LVITEM lvitem = { NULL };
	lvitem.mask = LVIF_TEXT;
	lvitem.pszText = buffer;

	HWND hTagsListView = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TAGSLISTVIEW);
	ListView_InsertItem(hTagsListView, &lvitem);

	SetWindowText(hTagsTextBox, L"");
	delete[] buffer;

	return 0;
}



LRESULT contCreatWnd_enter_pressed()
{
	HWND currentFocus = GetFocus();

	if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TAGSTEXTBOX))
		contCreatWnd_applyTag();
	else
		contCreatWnd_fillContainer();

	return 0;
}

LRESULT contCreatWnd_delete_pressed()
{
	HWND hMainLv = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TAGSLISTVIEW);
	size_t index = ListView_GetNextItem(hMainLv, -1, LVNI_SELECTED);

	if (index == -1 || GetFocus() != hMainLv)
		return 0;

	ListView_DeleteItem(hMainLv, index);
	return 0;
}

LRESULT contCreatWnd_tab_pressed()
{
	HWND currentFocus = GetFocus();

	if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_NAMETEXTBOX))
		SetFocus(HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TASKTEXTBOX));

	else if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TASKTEXTBOX))
		SetFocus(HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TAGSTEXTBOX));

	else if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TAGSTEXTBOX))
		SetFocus(HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TASKTYPECOMBOBOX));

	else if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TASKTYPECOMBOBOX))
		SetFocus(HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_APPLYBUTTON));

	return 0;
}



static bool fillDataFromTextBoxes(Container& container, HandleName hTextBoxName, ContainerDataTypes dataType);
static bool fillTaskType(Container& container);
static bool fillTags(Container& container);

LRESULT contCreatWnd_fillContainer()
{
	HWND hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_WND);
	Container container;

	bool errCode = fillTaskType(container);
	if (!errCode) {
		//Очищать контейнер напрямую, а не из архива можно только до его добавления туда.
		container.clear();
		MessageBox(hWnd, L"Тип задачи не задан!", L"Bookmark Manager", MB_OK | MB_ICONWARNING);
		return 0;
	}

	bool errCode_name = fillDataFromTextBoxes(container, HNAME_CONTAINERCREATIONWND_NAMETEXTBOX, ContainerDataTypes::NAME);
	bool errCode_task = fillDataFromTextBoxes(container, HNAME_CONTAINERCREATIONWND_TASKTEXTBOX, ContainerDataTypes::TASK);
	if (!(errCode_name && errCode_task)) {
		container.clear();
		MessageBox(hWnd, L"Поля \"Название\" и \"Задача\" должны быть заполнены!", L"Bookmark Manager", MB_OK | MB_ICONWARNING);
		return 0;
	}

	fillTags(container);

	Archive_Id id = Archive::addContainer(container);

	HWND hWndParent = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_WND);
	SendMessage(hWndParent, UM_SHOWCREATEDCONTAINER, id, NULL);
	SendMessage(hWnd, WM_CLOSE, NULL, APPLYBUTTON_PRESSED);

	return 0;
}

static bool fillTaskType(Container& container)
{
	HWND hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TASKTYPECOMBOBOX);
	int index = SendMessage(hWnd, CB_GETCURSEL, NULL, NULL);

	if (index == -1)
		return false;

	container.setTaskType(index);
	return true;
}

static bool fillTags(Container& container)
{
	HWND hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TAGSLISTVIEW);
	size_t tagsCount = ListView_GetItemCount(hWnd);

	if (!tagsCount)
		return true;

	PWSTR buffer = new WCHAR[0xF4240];
	LVITEM lvitem;
	lvitem.mask = LVIF_TEXT;
	lvitem.pszText = buffer;
	lvitem.cchTextMax = 0xF4240;

	for (size_t i = 0; i < tagsCount; i++) {
		lvitem.iItem = i;
		ListView_GetItem(hWnd, &lvitem);
		container.addTag(lvitem.pszText);
	}

	delete[] buffer;
	return true;
}

static bool fillDataFromTextBoxes(Container& container, HandleName hTextBoxName, ContainerDataTypes dataType)
{
	HWND	hWnd = HandleManager::getHandleWnd(hTextBoxName);
	size_t	length = GetWindowTextLength(hWnd) + (size_t)1;

	PWSTR buffer = new WCHAR[length];
	GetWindowText(hWnd, buffer, length);

	int spaceCounter = 0;
	for (size_t i = 0; i < length - 1; i++) {
		if (buffer[i] != L' ')
			break;

		spaceCounter++;
	}

	if (spaceCounter) {
		std::wstring newText = buffer;
		newText.erase(0, spaceCounter);
		length -= spaceCounter;
		wcscpy_s(buffer, length, newText.c_str());
	}

	if (length - 1 == 0) {
		delete[] buffer;
		return false;
	}

	switch (dataType)
	{
	case ContainerDataTypes::NAME:	container.setName(buffer, length);	break;
	case ContainerDataTypes::TASK:	container.setTask(buffer, length);	break;
	}

	delete[] buffer;
	return true;
}
