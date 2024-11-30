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
#include "Material.h"
#include "Prerequisites.h"

#include "MenuScreen.h"
#include "MaterialEditor.h"

namespace mrlol
{
	class UIManager
	{
		typedef std::shared_ptr<UIScreen> UIScreenPtr;
		typedef std::vector<UIScreenPtr> UIList;
		typedef std::unordered_map<std::string, UIScreenPtr> UIMap;

	public:
		static UIManager* get();

		static void initialize(HWND windowHandle);
		void setActive(std::string name);
		void draw() const;

		UIScreenPtr getScreen(std::string name);

		UIManager(UIManager const&) = delete;
		UIManager& operator=(UIManager const&) = delete;
		UIManager(UIManager&& other) noexcept = delete;
		UIManager& operator=(UIManager&& other) noexcept = delete;


		static constexpr int WindowWidth = 1440;
		static constexpr int WindowHeight = 900;

		static int resizeWidth;
		static int resizeHeight;

		std::shared_ptr<Material> mainMaterial = nullptr;

	private:
		explicit UIManager(HWND windowHandle);
		~UIManager();
		static UIManager* sharedInstance;

		void addViewport(UIScreenPtr viewport);
		static void setupImGuiStyle();

		mutable bool firstTime = true;
		UIList uiList;
		UIMap uiMap;
	};
}

