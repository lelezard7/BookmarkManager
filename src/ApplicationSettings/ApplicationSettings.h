/*
*		ApplicationSettings sets and stores application settings.
*/

#pragma once
#ifndef _APPLICATIONSETTINGS_
#define _APPLICATIONSETTINGS_

enum class StartupMethod;

class ApplicationSettings
{	
	/*
	*		Stores the way to launch ContainerCreationWindow.
	*		Launch options are listed in 'enum class StartupMethod'.
	*/
	static StartupMethod runContainerCreationWindow_;
	ApplicationSettings() = delete;

public:
	/*		Sets and gets the launch method for ContainerCreationWindow.		*/
	static void setStartupMethodContainerCreationWindow(StartupMethod startupMethod);
	static StartupMethod getStartupMethodContainerCreationWindow();
};

/*
*		Stores ContainerCreationWindow launch methods.
*		runContainerCreationWindow_ takes the following values:
*				1) CREATE_NEW_WINDOW - when ContainerCreationWindow is closed,
*					the window is destroyed. And when you call it again, a new instance
*					of the window ContainerCreationWindow is created.
*				2) SHOW_CLOSED_WINDOW (default) - when ContainerCreationWindow is
*					closed the window is not destroyed but hides and when it is called
*					again it is shown.
*		
*		If the user wants to close ContainerCreationWindow, and so that the data that he
*		entered in ContainerCreationWindow is saved, he must specify SHOW_CLOSED_WINDOW
*		in the settings.
*/
enum class StartupMethod
{
	CREATE_NEW_WINDOW,
	SHOW_CLOSED_WINDOW
};

#endif
