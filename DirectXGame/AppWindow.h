#pragma once

#include <Windows.h>
#include <vector>
#include <iostream>

#include "LogUtils.h"

// #define TINYOBJLOADER_IMPLEMENTATION
// #include "tiny_obj_loader.h"

#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"

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
#include "Cylinder.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Camera.h"
#include "SceneCamera.h"
#include "CameraManager.h"
#include "Quad.h"
#include "Mesh.h"
#include "Circle.h"
#include "Plane.h"
#include "MathUtil.h"
#include "UIManager.h"


class AppWindow final : public Window, public InputListener
{
public:
	static AppWindow* get();

	void onCreate() override;
	void onUpdate() override;
	void onFocus() override;
	void onKillFocus() override;
	void onDestroy() override;

	//static Camera* activeCamera;

	AppWindow(AppWindow const&) = delete;
	AppWindow& operator=(AppWindow const&) = delete;
	AppWindow(AppWindow&& other) noexcept = delete;
	AppWindow& operator=(AppWindow&& other) noexcept = delete;

private:
	AppWindow();
	~AppWindow() override;

	static AppWindow* sharedInstance;

	//Quad* qList[1]; // object manager later
	//Cube* cList[1]; // object manager later
	//std::vector<GameObject*> gameObjectsVector;

	std::shared_ptr<Material> mainMaterial = nullptr;
	SwapChainPtr swapChain;

	VertexShaderPtr vertexShader;
	GeometryShaderPtr geometryShader;
	//GeometryShader* geometryShader1;
	PixelShaderPtr pixelShader;

	float ticks = 0.0f;

	void onKeyDown(int key) override;
	void onKeyUp(int key) override;
	void onMouseMove(const Vector2D& mousePosition) override;

	void onLeftMouseDown(const Vector2D& mousePosition) override;
	void onLeftMouseUp(const Vector2D& mousePosition) override;
	void onRightMouseDown(const Vector2D& mousePosition) override;
	void onRightMouseUp(const Vector2D& mousePosition) override;
};

