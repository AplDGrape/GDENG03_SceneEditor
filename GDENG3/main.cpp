#include "AppWindow.h"
#include "EngineTime.h"
#include <iostream>
#include <chrono>

int main() 
{
	//EngineTime::initialize();

	/*AppWindow app;
	if (app.init())
	{
		while (app.isRun())
		{
			app.broadcast();
		}
	}*/

	AppWindow::initialize();
	AppWindow* runningApp = (AppWindow*)AppWindow::getInstance();
	runningApp->initializeEngine();
	runningApp->createInterface();

	while(runningApp->isRun())
	{
		runningApp->broadcast();
	}

	return 0;
}