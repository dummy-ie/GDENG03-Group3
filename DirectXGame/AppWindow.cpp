#include "AppWindow.h"
#include <Windows.h>

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::initialize() {
	sharedInstance = new AppWindow();
	sharedInstance->onCreate();

}

void AppWindow::destroy() {
	if (sharedInstance != NULL) {
		sharedInstance->onDestroy();
		delete sharedInstance;
	}
}

void AppWindow::onCreate()
{
	bRunning = true;
	Window::init();

}



void AppWindow::initializeEngine() {
	GraphicsEngine::initialize();
	EngineTime::initialize();
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
	RECT rc = this->getClientWindowRect();

	this->swapChain = GraphicsEngine::getInstance()->getSwapChain();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	this->swapChain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	// Initialize three distinct quads with different colors
	m_quad = new Quad(0.0f, 0.0f, 0.0f); 
	m_quad->init(GraphicsEngine::getInstance()->getD3DDevice());

}


bool AppWindow::isRunning()
{
	return bRunning;
}


void AppWindow::onUpdate() {
	Window::onUpdate();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->swapChain, 0, 0.3f, 0.4f, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	this->m_quad->render(EngineTime::getDeltaTime());

	this->swapChain->present(true);
}

void AppWindow::onDestroy() {
	// Stop rendering first
	bRunning = false; // If this flag controls the rendering loop

	// Release resources in reverse order of creation
	if (m_quad) m_quad->release();
	if (m_quad2) m_quad2->release();
	if (m_quad3) m_quad3->release();

	// Release the swap chain and any other graphics resources
	GraphicsEngine::getInstance()->destroy(); // Ensure this cleans up the DeviceContext, SwapChain, etc.

	// Optionally set pointers to null after release
	m_quad = nullptr;
	m_quad2 = nullptr;
	m_quad3 = nullptr;
}



