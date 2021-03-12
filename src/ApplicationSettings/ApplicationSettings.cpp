#define UNICODE

#include "ApplicationSettings.h"

StartupMethod ApplicationSettings::runContainerCreationWindow_ = StartupMethod::SHOW_CLOSED_WINDOW;
TaskTypes_ID ApplicationSettings::defaultTaskType = TASKT_NOTSPECIFIED;


void ApplicationSettings::setStartupMethodContainerCreationWindow(StartupMethod startupMethod)
{
	runContainerCreationWindow_ = startupMethod;
}

StartupMethod ApplicationSettings::getStartupMethodContainerCreationWindow()
{
	return runContainerCreationWindow_;
}


void ApplicationSettings::setDefaultTaskType(TaskTypes_ID id)
{
	defaultTaskType = id;
}

TaskTypes_ID ApplicationSettings::getDefaultTaskType()
{
	return defaultTaskType;
}
