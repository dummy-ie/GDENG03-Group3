#include "AppWindow.h"

using namespace mrlol;

int main()
{
	AppWindow* runningApp = AppWindow::get();
	while (runningApp->isRunning()) {}
	return 0;
}