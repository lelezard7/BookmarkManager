#define UNICODE

#include "ApplicationSettings.h"

StartupMethod ApplicationSettings::runContainerCreationWindow_ = StartupMethod::SHOW_CLOSED_WINDOW;


void ApplicationSettings::setStartupMethodContainerCreationWindow(StartupMethod startupMethod)
{
	runContainerCreationWindow_ = startupMethod;
}

StartupMethod ApplicationSettings::getStartupMethodContainerCreationWindow()
{
	return runContainerCreationWindow_;
}
