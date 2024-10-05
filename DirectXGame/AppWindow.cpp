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

	Vertex list[4] = {
		//X - Y - Z
		{{-0.6f,-0.8f,0.0f},    {-0.4f,0.2f,0.0f},  { 0,0,0}, { 0,1,0} }, // POS1
		{{-0.8f,0.5f,0.0f},     {-0.2f,0.7f,0.0f},   { 1,1,0}, { 0,1,1} }, // POS2
		{ {0.9f,-0.4f,0.0f},    {0.2f,-0.6f,0.0f},  { 0,0,1}, { 1,0,0} },// POS2
		{ {-0.6f,-0.8f,0.0f},    { 0.8f,0.8f,0.0f},   { 1,1,1}, { 0,0,1} }
	};

	// qList[0] = new Quad(
	// 	{ 1.0f, 1.0f },
	// 	{ -0.2f, 0.2f, 0.0f },
	// 	{ 0.5f, -0.8f, 0.0f },
	// 	{ 1.0f, 0.0f, 0.0f });

	qList[0] = new Quad(list);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(
		this->swapChain,
		0.15,
		0.2,
		0.60,
		1);

	const RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// m_angle += 1.57f * m_delta_time;
	// Constant cc;
	// cc.angle = m_angle;
	//
	// cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	//
	// GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vs, cb);
	// GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(ps, cb);
	//
	// //SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	// GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
	// GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);
	//
	//
	// //SET THE VERTICES OF THE TRIANGLE TO DRAW
	// GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vb);
	//
	// // FINALLY DRAW THE TRIANGLE
	// GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vb->getSizeVertexList(), 0);

	//qList[0]->update(m_delta_time);

	for (Quad* q : qList)
	{
		q->draw(EngineTime::getDeltaTime(), getClientWindowRect());
	}

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
