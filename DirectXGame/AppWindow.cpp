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
	//
	// Vertex list[] =
	// {
	// 	//X - Y - Z
	// 	{-0.5f,-0.5f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0,  0,1,0 }, // POS1
	// 	{-0.5f,0.5f,0.0f,     -0.11f,0.78f,0.0f,    1,1,0,  0,1,1 }, // POS2
	// 	{ 0.5f,-0.5f,0.0f,     0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },// POS2
	// 	{ 0.5f,0.5f,0.0f,      0.88f,0.77f,0.0f,    1,1,1,  0,0,1 }
	// };
	//
	// vb = GraphicsEngine::get()->createVertexBuffer();
	// UINT size_list = ARRAYSIZE(list);
	//
	// void* shader_byte_code = nullptr;
	// size_t size_shader = 0;
	// GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "main", &shader_byte_code, &size_shader);
	//
	// vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	// vb->load(list, sizeof(Vertex), size_list, shader_byte_code, size_shader);
	//
	// GraphicsEngine::get()->releaseCompiledShader();
	//
	//
	// GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "main", &shader_byte_code, &size_shader);
	// ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	// GraphicsEngine::get()->releaseCompiledShader();
	//
	// Constant cc;
	// cc.angle = 0;
	//
	// cb = GraphicsEngine::get()->createConstantBuffer();
	// cb->load(&cc, sizeof(Constant));

	qList[0] = new Quad(
		{ 0.3f, 0.25f },
		{ .2f, .2f },
		{ .5f, .8f },
		{ 1.0f, 0.0f, 0.0f });

	qList[1] = new Quad(
		{ 0.25f, 0.3f },
		{ -0.5f, .2f },
		{ -0.5f, .8f },
		{ 0.0f, 1.0f, 0.0f });

	qList[2] = new Quad(
		{ 0.25, 0.25 },
		{ .2, -.5 },
		{ .0f, -.8f },
		{ 0, 0, 1 });
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

	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

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
		q->draw(m_delta_time);
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
