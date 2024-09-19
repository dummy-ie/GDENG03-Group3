#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();

	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_Hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list0[] =
	{
		// Rainbow triangle
		{-0.8f,		-0.8f,	0.0f,		1, 0, 0},
		{-0.5f,		-0.2f,		0.0f,		0, 1, 0},
		{-0.2f,		-0.8f,	0.0f,		0, 0, 1},
	};
	vertex list1[] =
	{

		// Rainbow rectangle
		{-0.8f,		0.2f,	0.0f,		1, 0,0},
		{-0.8f,		0.8f,		0.0f,		0, 1,0},
		{-0.2f,		0.2f,	0.0f,		0, 0,1},
		{-0.2f,		0.8f,		0.0f,		1, 1,0},

	};
	vertex list2[] =
	{
		// Green rectangle
		{0.0f,		-0.5f,	0.0f,		0, 1,0},
		{0.0f,		0.5f,		0.0f,		0, 1,0},
		{0.5f,		-0.5f,	0.0f,		0, 1,0},
		{0.5f,		0.5f,		0.0f,		0, 1,0},
	};

	m_vb0 = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list0 = ARRAYSIZE(list0);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "main", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb0->load(list0, sizeof(vertex), size_list0, shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	m_vb1 = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list1 = ARRAYSIZE(list1);

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "main", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb1->load(list1, sizeof(vertex), size_list1, shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	m_vb2 = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list2 = ARRAYSIZE(list2);

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "main", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb2->load(list2, sizeof(vertex), size_list2, shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "main", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(
		this->m_swap_chain,
		0,
		0,
		0,
		1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb0);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb0->getSizeVertexList(), 0);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb1);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb1->getSizeVertexList(), 0);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb2);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb2->getSizeVertexList(), 0);

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_vb0->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();

	GraphicsEngine::get()->release();
}
