#include "AppWindow.h"

using namespace gdeng03;

int main()
{
	AppWindow* runningApp = AppWindow::get();
	while (runningApp->isRunning()) {}
	return 0;
}