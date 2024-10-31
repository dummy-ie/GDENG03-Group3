#include "AppWindow.h"


int main()
{
	AppWindow* runningApp = AppWindow::get();
	while (runningApp->isRunning()) {}
	return 0;
}