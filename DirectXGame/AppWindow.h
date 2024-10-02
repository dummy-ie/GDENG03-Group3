#pragma once
#include "Window.h"
#include "Quad.h"
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
	static AppWindow* getInstance();
	static void initialize();
	static void destroy();

private:
	AppWindow();
	~AppWindow();
	AppWindow(AppWindow const&) {};
	AppWindow& operator =(AppWindow const&) {};

	static AppWindow* sharedInstance;
	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

public:
	void initializeEngine();
	bool isRunning();

private:
	SwapChain* swapChain;

	VertexShader* m_vs;
	PixelShader* m_ps;

	Quad* m_quad;
	Quad* m_quad2;
	Quad* m_quad3;	

	bool bRunning = false;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;

};
