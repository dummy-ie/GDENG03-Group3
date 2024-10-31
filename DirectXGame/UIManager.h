#pragma once

#include <unordered_map>
#include <vector>

#include "UIScreen.h"
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "Window.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "DeviceContext.h"
#include "Prerequisites.h"

class UIManager
{
public:
	static UIManager* get();

	static void initialize(HWND windowHandle);
	void draw();

	UIManager(UIManager const&) = delete;
	UIManager& operator=(UIManager const&) = delete;
	UIManager(UIManager&& other) noexcept = delete;
	UIManager& operator=(UIManager&& other) noexcept = delete;

	static constexpr int WindowWidth = 1440;
	static constexpr int WindowHeight = 900;
private:
	UIManager(HWND windowHandle);
	~UIManager();
	static UIManager* sharedInstance;

	std::vector<UIScreen*> uiList;
	std::unordered_map < std::string, UIScreen* > uiTable;
};

