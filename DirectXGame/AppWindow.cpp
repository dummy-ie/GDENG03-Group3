#include "AppWindow.h"
#include <Windows.h>

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};


__declspec(align(16))
struct constant
{
	float m_angle;
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

	//Texture Loading

	this->m_texture = new Texture();
	if (!TextureLoader::loadTexture(GraphicsEngine::get()->getD3DDevice(), L"Textures\myTexture.raw", *m_texture))
	{
		// Handle texture loading error
	}

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] =
	{
		//X - Y - Z
		{-0.5f,-0.5f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0,  0,1,0 }, // POS1
		{-0.5f,0.5f,0.0f,     -0.11f,0.78f,0.0f,    1,1,0,  0,1,1 }, // POS2
		{ 0.5f,-0.5f,0.0f,     0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },// POS3
		{ 0.5f,0.5f,0.0f,      0.88f,0.77f,0.0f,    1,1,1,  0,0,1 }
	};

	vertex list2[] =
	{
		// X - Y - Z (Upright Triangle with No Overlap and Proper Dimensions)
		{ 0.3f,  0.0f, 0.0f,   1, 0, 0}, // Bottom-left (Red)
		{ 0.3f,  0.5f, 0.0f,   0, 1, 0}, // Top-left (Green)
		{ 0.8f,  0.5f, 0.0f,   0, 0, 1}  // Top-right (Blue)
	};


	vertex list3[] =
	{
		{ -0.25f, 0.35f, 0.0f,   0, 1, 0}, // POS1 (Bottom-left)
		{-0.25f,  0.75f, 0.0f,   0, 1, 0}, // POS2 (Top-left)
		{ 0.25f,  0.35f, 0.0f,   0, 1, 0}, // POS3 (Bottom-right)
		{ 0.25f,  0.75f, 0.0f,   0, 1, 0}  // POS4 (Top-right)
	};


	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	m_vb2 = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list2 = ARRAYSIZE(list2);

	m_vb3 = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list3 = ARRAYSIZE(list3);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	void* shader_byte_code2 = nullptr;
	size_t size_shader2 = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code2, &size_shader2);

	m_vs2 = GraphicsEngine::get()->createVertexShader(shader_byte_code2, size_shader2);
	m_vb2->load(list2, sizeof(vertex), size_list2, shader_byte_code2, size_shader2);
	GraphicsEngine::get()->releaseCompiledShader();


	void* shader_byte_code3 = nullptr;
	size_t size_shader3 = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code3, &size_shader3);

	m_vs3 = GraphicsEngine::get()->createVertexShader(shader_byte_code3, size_shader3);
	m_vb3->load(list3, sizeof(vertex), size_list3, shader_byte_code3, size_shader3);
	GraphicsEngine::get()->releaseCompiledShader();



	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code2, &size_shader2);
	m_ps2 = GraphicsEngine::get()->createPixelShader(shader_byte_code2, size_shader2);
	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code3, &size_shader3);
	m_ps3 = GraphicsEngine::get()->createPixelShader(shader_byte_code3, size_shader3);
	GraphicsEngine::get()->releaseCompiledShader();




}


void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	

	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount64() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount64();

	m_angle += 1.57f * m_delta_time;
	constant cc;
	cc.m_angle = m_angle;

	//SETUP FOR ANIMATION
	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	// DRAW FIRST SHAPE (Rectangle)
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	// Bind the texture to slot 0
	m_texture->bind(GraphicsEngine::get()->getImmediateDeviceContext()->getContext());

	/*
	// DRAW SECOND SHAPE (Triangle)
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs2);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps2);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb2);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb2->getSizeVertexList(), 0);


	// DRAW THIRD SHAPE (Green Rectangle)
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs3);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps3);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb3);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb3->getSizeVertexList(), 0);
	*/
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_vb2->release();
	m_swap_chain->release();
	m_vs->release();
	m_vs2->release();
	m_ps->release();
	m_ps2->release();
	GraphicsEngine::get()->release();
}

/*
Window::onUpdate();
//CLEAR THE RENDER TARGET 
GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
	0, 0.3f, 0.4f, 1);
//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
RECT rc = this->getClientWindowRect();
GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


//SET THE VERTICES OF THE TRIANGLE TO DRAW
GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb2);

// FINALLY DRAW THE TRIANGLE
GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb2->getSizeVertexList(), 0);
m_swap_chain->present(true);
*/