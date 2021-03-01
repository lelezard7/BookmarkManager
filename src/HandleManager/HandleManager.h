/*
*		HandleManager is responsible for creating and storing window handles.
*		The handles are named by template:
*				("the name of the .h file must be equal to the name of the .cpp file" -
					- General requirements // src/BookmarkManager.cpp)
*				1) filename with lowercase letter_handle name with lowercase letter
*				2) if one window is created in one file then the window hendle is named like this:
*					filename with lowercase letter_wnd
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
	///*
	//*		addHandleWnd create a new handle and gives it the name given by the parameter 'name'.
	//* 
	//*		If the name already exsist then return nullptr else window handle.
	//*/
	//static HWND* addHandleWnd(cHandleName name);
	///*
	//*		Writes the created handle to 'localHandle'.
	//*		If the name already exsist then return false else true.
	//*/
	//static bool addHandleWnd(cHandleName name, HWND*& localHandle);

	//static HWND* createHandleWnd(cHandleName name);

	static HWND getHandleWnd(const HandleName name);
	static bool addHandleWnd(HWND hWnd, const HandleName name);
	static bool checkExistence(const HandleName name);
	static bool checkExistence(const CheckList& checkList);
	static bool removeHandleWnd(const HandleName name);

	///*
	//*		getHandleWnd look for a handle by name.
	//* 
	//*		If the name found returns it else nullptr.
	//*/
	//static HWND* getHandleWnd(cHandleName name);
	///*
	//*		Writes the found handle to 'localHandle'.
	//*		If the name found returns true else false.
	//*/
	//static bool getHandleWnd(cHandleName name, HWND*& localHandle);
	//
	///*
	//*		checkExistence checks the existence of names in the 'handleContainer_'.
	//*		If all names are found returns true else false.
	//*		In checkExistence you can transfer both one name and an array of names.
	//*		You can pass an array to a function in two ways:
	//*				1) Put at the end of the array '\0'
	//*					HandleName сhecklist[]{ L"name_1", L"name_2", L"\0" };
	//*				2) Specify the size of the array.
	//*/
	//static bool checkExistence(cHandleName name);
	//static bool checkExistence(pcHandleName names);
	//static bool checkExistence(pcHandleName names, const size_t size);

	///*
	//*		removeHandleWnd removes the window handle for the specified name
	//*		and the name itself from 'handleContainer_'.
	//*		if successfully return true else false.
	//*/
	//static bool removeHandleWnd(cHandleName name);
};

#endif
