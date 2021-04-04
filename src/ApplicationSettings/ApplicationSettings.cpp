#define UNICODE

#include "..\Common\Debug.h"
#include "ApplicationSettings.h"

LaunchMethod ApplicationSettings::containerCreationWindowLaunchMethod_ = LaunchMethod::CONTINUE_UNFINISHED_CREATION;
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

void ApplicationSettings::restoreDefaultSettings()
{
	containerCreationWindowLaunchMethod_ = LaunchMethod::CONTINUE_UNFINISHED_CREATION;
	defaultTaskType_ = TASKTYPE_NOTSPECIFIED;
}
