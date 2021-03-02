/*
*		This header connects to all other files. Here you can write everything that will help in debugging.
*/

#pragma once
#ifndef _DEBUG_
#define _DEBUG_

#include <Windows.h>
#include <string>

//		Comment if the debugging mode is off.
#define BKM_DEBUG

/*
*		If BKM_DEBUG is defined, displays the message in the chosen way.
* 
*		debugMessage first calls debugMessage_console, and then debugMessage_messageBox.
*/
void debugMessage(std::wstring message);

//		debugMessage_console adds to the end '\n'.
void debugMessage_console(std::wstring message);
void debugMessage_messageBox(const std::wstring message);

#endif
