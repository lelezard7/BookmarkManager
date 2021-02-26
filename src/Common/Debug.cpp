#ifndef UNICODE
#define UNICODE
#endif

#include "Debug.h"
#include <debugapi.h>


void debugMessage(std::wstring message)
{
#ifdef BKM_DEBUG
	debugMessage_console(message);
	debugMessage_messageBox(message);
#endif
}

void debugMessage_console(std::wstring message)
{
#ifdef BKM_DEBUG
	OutputDebugString((message + L"\n").c_str());
#endif
}

void debugMessage_messageBox(const std::wstring message)
{
#ifdef BKM_DEBUG
	MessageBox(NULL, message.c_str(), L"DEBUG", MB_OK | MB_ICONWARNING);
#endif
}
