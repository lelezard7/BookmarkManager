/**
*		ContainerCreationWindow is the window in which the user creates the container.
*		What is a container and what is included in it, see Archive.h (src/Archive/Archive.h)											
*/

#pragma once
#ifndef _CONTAINER_CREATION_WND_
#define _CONTAINER_CREATION_WND_

#include <Windows.h>


LRESULT CALLBACK ContainerCreatProc(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM);
void create_containerCreationWindow(HINSTANCE);

#endif
