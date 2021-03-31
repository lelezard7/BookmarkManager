/**
*		ApplicationSettings sets and stores application settings.
*/

#pragma once
#ifndef _APPLICATION_SETTINGS_
#define _APPLICATION_SETTINGS_

#include "..\Archive\TaskTypesCollection.h"
#include <Windows.h>

enum class LaunchMethod;


class ApplicationSettings
{	
	/*
	*		Stores the way to launch ContainerCreationWindow.
	*		Launch options are listed in 'enum class StartupMethod'.
	*/
	static LaunchMethod containerCreationWindowLaunchMethod_;
	static TaskType defaultTaskType_;

	ApplicationSettings() = delete;
	~ApplicationSettings() = delete;

public:
	/*		Sets and gets the launch method for ContainerCreationWindow.		*/
	static void setLaunchMethodContainerCreationWindow(LaunchMethod launchMethod);
	static LaunchMethod getLaunchMethodContainerCreationWindow();

	static void setDefaultTaskType(TaskType taskType);
	static TaskType getDefaultTaskType();
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
*				3) CONTINUE_UNFINISHED_CREATION - a new window will be created only if the
*					user clicks "Apply" and the container is successfully created.
*		
*		If the user wants to close ContainerCreationWindow, and so that the data that he
*		entered in ContainerCreationWindow is saved, he must specify SHOW_CLOSED_WINDOW
*		in the settings.
*/
enum class LaunchMethod
{
	CREATE_NEW_WINDOW,
	SHOW_CLOSED_WINDOW,
	CONTINUE_UNFINISHED_CREATION
};

#endif
