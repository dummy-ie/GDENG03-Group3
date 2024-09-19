#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb0;
	VertexBuffer* m_vb1;
	VertexBuffer* m_vb2;
	VertexShader* m_vs;
	PixelShader* m_ps;
};

