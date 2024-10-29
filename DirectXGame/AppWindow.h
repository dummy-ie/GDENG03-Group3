#pragma once

#include <Windows.h>
#include <vector>
#include <iostream>

#include "LogUtils.h"

#include "Window.h"
#include "EngineTime.h"
#include "InputSystem.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "GameObject.h"
#include "Cube.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Camera.h"
#include "SceneCamera.h"
#include "CameraManager.h"
#include "Quad.h"
#include "Circle.h"
#include "Plane.h"
#include "MathUtil.h"


class AppWindow final : public Window, public InputListener
{
public:
	static AppWindow* get();
	static void initialize();
	static void destroy();

	void onCreate() override;
	void onUpdate() override;
	void onFocus() override;
	void onKillFocus() override;
	void onDestroy() override;

	//static Camera* activeCamera;

private:
	AppWindow();
	~AppWindow() override;
	AppWindow(AppWindow const&) :
		swapChain(nullptr),
		vertexShader(nullptr),
		geometryShader(nullptr),
		pixelShader(nullptr)
	{
	}
	AppWindow& operator=(AppWindow const&) {}
	static AppWindow* sharedInstance;

	//Quad* qList[1]; // object manager later
	//Cube* cList[1]; // object manager later
	std::vector<GameObject*> gameObjectsVector;


	SwapChain* swapChain;

	VertexShader* vertexShader;
	GeometryShader* geometryShader;
	//GeometryShader* geometryShader1;
	PixelShader* pixelShader;

	float ticks = 0.0f;

	void onKeyDown(int key) override;
	void onKeyUp(int key) override;
	void onMouseMove(const Vector2D& mousePosition) override;

	void onLeftMouseDown(const Vector2D& mousePosition) override;
	void onLeftMouseUp(const Vector2D& mousePosition) override;
	void onRightMouseDown(const Vector2D& mousePosition) override;
	void onRightMouseUp(const Vector2D& mousePosition) override;
};

