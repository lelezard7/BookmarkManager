/*
*		Common operations on window and controls are descrided here.
*/

#pragma once
#ifndef _COMMONOPERATIONS_
#define _COMMONOPERATIONS_

#include "Debug.h"
#include <Windows.h>
#include <map>


enum class ClientRectCoordinates;

typedef int	TaskTypes_Index_t;
typedef std::map<TaskTypes_Index_t, PWSTR> TaskTypes_t;

class TaskTypesCollection
{
	TaskTypesCollection() = delete;
	~TaskTypesCollection() = delete;
public:
	static void addTaskType(const PWSTR name);
	static bool findTaskType(TaskTypes_Index_t index);
	static PWSTR getTaskType(TaskTypes_Index_t index);
};

void fillComboBoxTaskTypes(HWND hWnd);
void moveWindowToCenterScreen(HWND hWnd, HWND hWndInsertAfter = HWND_TOP);
void setMinimumWindowSize(const LONG width, const LONG height, LPARAM lParam);

/*		
*		Receives the coordinates of the client area and returns the valuespecified
*		in the 'ClientRectCoordinates'.
*		If the function succeeds, the return value is nonzero.
*		If the function fails, the return value is zero.
*/
LONG getClientRectValue(HWND hWnd, ClientRectCoordinates clientRectCoordinates);
size_t mainLV_getSelectedId();


enum class ClientRectCoordinates
{
	BOTTOM,
	LEFT,
	TOP,
	RIGHT
};

#endif
