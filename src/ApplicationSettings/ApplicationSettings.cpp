#define UNICODE

#include "ApplicationSettings.h"

StartupMethod ApplicationSettings::runContainerCreationWindow_ = StartupMethod::SHOW_CLOSED_WINDOW;
TaskTypes_Index_t ApplicationSettings::defaultTaskType = TASKTTYPE_NOTSPECIFIED;


void ApplicationSettings::setStartupMethodContainerCreationWindow(StartupMethod startupMethod)
{
	runContainerCreationWindow_ = startupMethod;
}

StartupMethod ApplicationSettings::getStartupMethodContainerCreationWindow()
{
	return runContainerCreationWindow_;
}


void ApplicationSettings::setDefaultTaskType(TaskTypes_Index_t index)
{
	defaultTaskType = index;
}

TaskTypes_Index_t ApplicationSettings::getDefaultTaskType()
{
	return defaultTaskType;
}
