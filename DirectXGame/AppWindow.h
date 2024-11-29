#pragma once

#include <Windows.h>
#include <vector>
#include <iostream>

#include "LogUtils.h"

// #define TINYOBJLOADER_IMPLEMENTATION
// #include "tiny_obj_loader.h"

#include <reactphysics3d/reactphysics3d.h>

#include "imgui.h"
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_dx11.h>

#include "Window.h"
#include "EngineTime.h"
#include "InputSystem.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "GameObject.h"
//#include "Cube.h"
//#include "Cylinder.h"
//#include "Circle.h"
//#include "Quad.h"
//#include "Plane.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Camera.h"
#include "SceneCamera.h"
#include "CameraManager.h"
#include "Mesh.h"
#include "MathUtil.h"
#include "UIManager.h"

namespace mrlol
{
	enum EFillMode : int;

	class AppWindow final : public Window, public InputListener
	{

	public:
		static AppWindow* get();

		void onCreate() override;
		void onUpdate() override;
		void onFocus() override;
		void onKillFocus() override;
		void onDestroy() override;

		void draw(int width, int height, EFillMode fillMode)

		SwapChain* getSwapChain() const;

		AppWindow(AppWindow const&) = delete;
		AppWindow& operator=(AppWindow const&) = delete;
		AppWindow(AppWindow&& other) noexcept = delete;
		AppWindow& operator=(AppWindow&& other) noexcept = delete;

	private:
		AppWindow();
		~AppWindow() override;

		static AppWindow* sharedInstance;

		//std::shared_ptr<Material> mainMaterial = nullptr;
		SwapChainPtr swapChain;
		RasterizerStatePtr solidState;

		float ticks = 0.0f;

		void onKeyDown(int key) override;
		void onKeyUp(int key) override;
	};
}

