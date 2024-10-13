#pragma once
#include "Window.h"
#include "Cube.h"
#include "list"
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
	void handleUserInput();

private:
	SwapChain* swapChain;
	Cube* m_cube;

	bool bRunning = false;

};
