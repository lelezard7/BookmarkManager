/*
*		HandleManager is responsible for creating and storing window handles.
* 
*		Handles are defined by template:
*			HNAME_WINDOWNAME_WND	№
*				or
*			HNAME_WINDOWNAME_ControlName	№
*/

#pragma once
#ifndef _HANDLEMANAGER_
#define _HANDLEMANAGER_

#include "..\Common\Debug.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <map>

typedef size_t HandleName;
typedef std::vector<HandleName> CheckList;

class HandleManager
{
	static std::map<HandleName, HWND> handleContainer_;

	HandleManager() = delete;
	
public:
	/*
	*		Returns a handle with the specified name.
	* 
	*		If a handle with the specified name exists, returns it. If does not exist
	*		returns nullptr and calls debugMessage with the
	*		message "Handle with the name HANDLENAME does not exist!".
	*/
	static HWND getHandleWnd(const HandleName name);

	/*		
	*		Adds the handle to the collection.
	* 
	*		If the name already exists will return false, otherwise true.
	*		If BKM_DEBUG is defined and you pass a name that already exists to
	*		the function, the debugMessage function will be called with the
	*		message "The HANDLENAME handle already exists!".
	*/
	static bool addHandleWnd(HWND hWnd, const HandleName name);

	/*
	*		Checks if a handle with the specified name exists or not.
	* 
	*		If you need to check several names, you can create
	*		a CheckList which is a vector of handle names:
	*			typedef std::vector<HandleName> CheckList;
	*		
	*		Returns true if all names were found and false if not.
	*/
	static bool checkExistence(const HandleName name);
	static bool checkExistence(const CheckList& checkList);

	/*
	*		Removes a handle with the specified name from the collection.
	* 
	*		Returns true if the handle was successfully removed, otherwise
	*		it returns false and calls debugMessage with the
	*		message "Handle with name HANDLENAME not found!"
	*/
	static bool removeHandleWnd(const HandleName name);
};

#endif
