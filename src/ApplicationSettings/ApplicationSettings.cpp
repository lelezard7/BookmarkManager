#define UNICODE

#include "..\Common\Debug.h"
#include "ApplicationSettings.h"

LaunchMethod ApplicationSettings::containerCreationWindowLaunchMethod_ = LaunchMethod::SHOW_CLOSED_WINDOW;
TaskType ApplicationSettings::defaultTaskType_ = TASKTYPE_NOTSPECIFIED;


void ApplicationSettings::setLaunchMethodContainerCreationWindow(LaunchMethod launchMethod)
{
	containerCreationWindowLaunchMethod_ = launchMethod;
}

LaunchMethod ApplicationSettings::getLaunchMethodContainerCreationWindow()
{
	return containerCreationWindowLaunchMethod_;
}


void ApplicationSettings::setDefaultTaskType(TaskType taskType)
{
	defaultTaskType_ = taskType;
}

TaskType ApplicationSettings::getDefaultTaskType()
{
	return defaultTaskType_;
}
