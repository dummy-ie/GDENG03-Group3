#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* m_swap_chain;

	VertexBuffer* m_vb;
	VertexBuffer* m_vb2;
	VertexBuffer* m_vb3;
	ConstantBuffer* m_cb;

	VertexShader* m_vs;
	VertexShader* m_vs2;
	VertexShader* m_vs3;

	PixelShader* m_ps;
	PixelShader* m_ps2;
	PixelShader* m_ps3;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;
};
