#define UNICODE

#include "CommonOperations.h"
#include "BkmDef.h"
#include "..\HandleManager\HandleManager.h"
#include <CommCtrl.h>

static TaskTypes_Index_t TaskTypes_index = 0;
static TaskTypes_t TaskTypes;


void TaskTypesCollection::addTaskType(const PWSTR name)
{
	TaskTypes.emplace(std::make_pair(TaskTypes_index, name));
	TaskTypes_index++;
}

bool TaskTypesCollection::findTaskType(TaskTypes_Index_t index)
{
	return TaskTypes.find(index) != TaskTypes.end();
}

PWSTR TaskTypesCollection::getTaskType(TaskTypes_Index_t index)
{
	return TaskTypes[index];
}

void fillComboBoxTaskTypes(HWND hWnd)
{
	for (auto i : TaskTypes)
		SendMessage(hWnd, CB_INSERTSTRING, -1, (LPARAM)i.second);
}


void moveWindowToCenterScreen(HWND hWnd, HWND hWndInsertAfter)
{
	RECT _rect;
	GetWindowRect(hWnd, &_rect);

	SetWindowPos(hWnd, hWndInsertAfter,
		CENTERSCREEN_X - ((_rect.right - _rect.left) / 2),
		CENTERSCREEN_Y - ((_rect.bottom - _rect.top) / 2),
		NULL, NULL, SWP_NOSIZE);
}

void setMinimumWindowSize(const LONG width, const LONG height, LPARAM lParam)
{
	LPMINMAXINFO _lpminmaxinfo = (LPMINMAXINFO)lParam;
	_lpminmaxinfo->ptMinTrackSize.x = width;
	_lpminmaxinfo->ptMinTrackSize.y = height;
}

LONG getClientRectValue(HWND hWnd, ClientRectCoordinates clientRectCoordinates)
{
	RECT _rect;

	if (!GetClientRect(hWnd, &_rect))
		return 0;

	switch (clientRectCoordinates)
	{
	case ClientRectCoordinates::BOTTOM:	return _rect.bottom;
	case ClientRectCoordinates::LEFT:	return _rect.left;
	case ClientRectCoordinates::TOP:	return _rect.top;
	case ClientRectCoordinates::RIGHT:	return _rect.right;
	}

	return 0;
}

size_t mainLV_getSelectedId()
{
	HWND hWnd = HandleManager::getHandleWnd(HNAME_BOOKMARKMANAGERWND_MainListView);
	size_t lvIndex = ListView_GetNextItem(hWnd, -1, LVNI_SELECTED);

	PWSTR buffer_id = new WCHAR[0xF4240];  //TODO: Сделать нормальное ограничение размеров во всей программе.
	ListView_GetItemText(hWnd, lvIndex, 0, buffer_id, 0xF4240);

	size_t id = std::stoull(buffer_id);
	delete[] buffer_id;

	return id;
}
