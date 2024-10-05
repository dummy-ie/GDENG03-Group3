#include "AppWindow.h"

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::get()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
}

void AppWindow::destroy()
{
	if (sharedInstance != NULL)
		sharedInstance->release();

	delete sharedInstance;
}

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();

	//GraphicsEngine::get()->init();
	GraphicsEngine::initialize();
	swapChain = GraphicsEngine::get()->createSwapChain();

	const RECT rc = this->getClientWindowRect();
	swapChain->init(this->m_Hwnd, rc.right - rc.left, rc.bottom - rc.top);

	qList[0] = new Quad(
		{ 1.0f, 1.0f },
		{ -0.2f, 0.2f, 0.0f },
		{ 0.5f, -0.8f, 0.0f },
		{ 1.0f, 0.0f, 0.0f });

	cList[0] = new Cube();

	// qList[1] = new Quad(
	// 	{ 0.25f, 0.3f },
	// 	{ -0.5f, .2f },
	// 	{ -0.5f, .8f },
	// 	{ 0.0f, 1.0f, 0.0f });
	//
	// qList[2] = new Quad(
	// 	{ 0.25, 0.25 },
	// 	{ .2, -.5 },
	// 	{ .0f, -.8f },
	// 	{ 0, 0, 1 });
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	ticks += EngineTime::getDeltaTime() * 1.0f;

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(
		this->swapChain,
		0.15,
		0.2,
		0.60,
		1);

	const RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	for (Quad* q : qList)
	{
		q->draw(EngineTime::getDeltaTime(), getClientWindowRect());
	}

	// for (Cube* c : cList)
	// {
	// 	c->draw(EngineTime::getDeltaTime(), getClientWindowRect());
	// }

	swapChain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	//vb->release();
	swapChain->release();
	//vs->release();
	//ps->release();

	//GraphicsEngine::get()->release();
	GraphicsEngine::destroy();
}

void AppWindow::updateQuadPosition()
{

}
