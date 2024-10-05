#pragma once

#include <Windows.h>

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Quad.h"

class AppWindow final : public Window
{
public:
	static AppWindow* get();
	static void initialize();
	static void destroy();

	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

private:
	AppWindow();
	~AppWindow();
	AppWindow(AppWindow const&) {};
	AppWindow& operator=(AppWindow const&) {};
	static AppWindow* sharedInstance;

	Quad* qList[1]; // object manager later

	SwapChain* swapChain;
	VertexBuffer* vb;
	//VertexBuffer* m_vb1;
	//VertexBuffer* m_vb2;
	VertexShader* vs;
	PixelShader* ps;
	ConstantBuffer* cb;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;
};

