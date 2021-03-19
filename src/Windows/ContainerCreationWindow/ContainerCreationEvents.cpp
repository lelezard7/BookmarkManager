#define UNICODE

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
	HWND hApplyButton = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_ApplyButton);
	HWND hNameTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_NameTextBox);
	HWND hTaskTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTextBox);
	HWND hTagsTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsTextBox);
	HWND hTagsListView = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsListView);
	HWND hTaskTypeComboBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeComboBox);
	HWND hApplyTagButton = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_ApplyTagButton);
	HWND hTaskTypeHelpText = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeHelpText);

	SetWindowPos(hApplyButton, HWND_TOP, ContainerCreationWnd_applyButton_X,
		ContainerCreationWnd_applyButton_Y,
		ContainerCreationWnd_applyButton_WIDTH,
		ContainerCreationWnd_applyButton_HEIGHT, NULL);
	SetWindowPos(hNameTextBox, HWND_TOP, ContainerCreationWnd_nameTextBox_X,
		ContainerCreationWnd_nameTextBox_Y,
		ContainerCreationWnd_nameTextBox_WIDTH,
		ContainerCreationWnd_nameTextBox_HEIGHT, NULL);
	SetWindowPos(hTaskTextBox, HWND_TOP, ContainerCreationWnd_taskTextBox_X,
		ContainerCreationWnd_taskTextBox_Y,
		ContainerCreationWnd_taskTextBox_WIDTH,
		ContainerCreationWnd_taskTextBox_HEIGHT, NULL);
	SetWindowPos(hTagsTextBox, HWND_TOP, ContainerCreationWnd_tagsTextBox_X,
		ContainerCreationWnd_tagsTextBox_Y,
		ContainerCreationWnd_tagsTextBox_WIDTH,
		ContainerCreationWnd_tagsTextBox_HEIGHT, NULL);
	SetWindowPos(hTagsListView, HWND_TOP, ContainerCreationWnd_tagsListView_X,
		ContainerCreationWnd_tagsListView_Y,
		ContainerCreationWnd_tagsListView_WIDTH,
		ContainerCreationWnd_tagsListView_HEIGHT, NULL);
	SetWindowPos(hTaskTypeComboBox, HWND_TOP, ContainerCreationWnd_taskTypeComboBox_X,
		ContainerCreationWnd_taskTypeComboBox_Y,
		ContainerCreationWnd_taskTypeComboBox_WIDTH,
		ContainerCreationWnd_taskTypeComboBox_HEIGHT, NULL);
	SetWindowPos(hApplyTagButton, HWND_TOP, ContainerCreationWnd_applyTagButton_X,
		ContainerCreationWnd_applyTagButton_Y,
		ContainerCreationWnd_applyTagButton_WIDTH,
		ContainerCreationWnd_applyTagButton_HEIGHT, NULL);
	SetWindowPos(hTaskTypeHelpText, HWND_TOP, ContainerCreationWnd_taskTypeHelpText_X,
		ContainerCreationWnd_taskTypeHelpText_Y,
		ContainerCreationWnd_taskTypeHelpText_WIDTH,
		ContainerCreationWnd_taskTypeHelpText_HEIGHT, NULL);

	return 0;
}

LRESULT contCreatWnd_closeWnd(HWND hWnd, LPARAM lParam)
{
	HWND hWndParent = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_WND);
	EnableWindow(hWndParent, true);
	SetFocus(hWndParent);

	StartupMethod startupmethod = ApplicationSettings::getStartupMethodContainerCreationWindow();

	if (startupmethod == StartupMethod::CREATE_NEW_WINDOW ||
		(lParam == APPLYBUTTON_PRESSED &&
			startupmethod == StartupMethod::CONTINUE_UNFINISHED_CREATION))
	{
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeComboBox);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_NameTextBox);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_ApplyButton);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTextBox);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TagsTextBox);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TagsListView);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_ApplyTagButton);
		HandleManager::removeHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeHelpText);
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
	HWND	hTagsTextBox = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsTextBox);
	size_t	length = GetWindowTextLength(hTagsTextBox) + (size_t)1;
	PWSTR	buffer = new WCHAR[length];

	GetWindowText(hTagsTextBox, buffer, length);

	LVITEM lvitem = { NULL };
	lvitem.mask = LVIF_TEXT;
	lvitem.pszText = buffer;

	HWND hTagsListView = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsListView);
	ListView_InsertItem(hTagsListView, &lvitem);

	delete[] buffer;
	return 0;
}



LRESULT contCreatWnd_enter_pressed()
{
	HWND currentFocus = GetFocus();

	if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsTextBox))
		contCreatWnd_applyTag();
	else
		contCreatWnd_fillContainer();

	return 0;
}

LRESULT contCreatWnd_tab_pressed()
{
	HWND currentFocus = GetFocus();

	if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_NameTextBox))
		SetFocus(HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTextBox));

	else if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTextBox))
		SetFocus(HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsTextBox));

	else if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsTextBox))
		SetFocus(HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeComboBox));

	else if (currentFocus == HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeComboBox))
		SetFocus(HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_ApplyButton));

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

	bool errCode_name = fillDataFromTextBoxes(container, HNAME_CONTAINERCREATIONWND_NameTextBox, ContainerDataTypes::NAME);
	bool errCode_task = fillDataFromTextBoxes(container, HNAME_CONTAINERCREATIONWND_TaskTextBox, ContainerDataTypes::TASK);
	if (!(errCode_name && errCode_task)) {
		container.clear();
		MessageBox(hWnd, L"Поля \"Имя\" и \"Задача\" должны быть заполнены!", L"Bookmark Manager", MB_OK | MB_ICONWARNING);
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
	HWND hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TaskTypeComboBox);
	int index = SendMessage(hWnd, CB_GETCURSEL, NULL, NULL);

	if (index == -1)
		return false;

	container.setTaskType(index);
	return true;
}

static bool fillTags(Container& container)
{
	HWND hWnd = HandleManager::getHandleWnd(HNAME_CONTAINERCREATIONWND_TagsListView);
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
