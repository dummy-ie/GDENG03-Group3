#include "UIManager.h"

UIManager* UIManager::sharedInstance = nullptr;

UIManager* UIManager::get()
{
	return sharedInstance;
}

void UIManager::initialize(const HWND windowHandle)
{
	if (!sharedInstance)
		sharedInstance = new UIManager(windowHandle);
}

void UIManager::draw()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// for (auto& uiScreen : uiList)
	// {
	// 	uiScreen->draw();
	// }

	ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(const HWND windowHandle)
{
	//initialize IMGUI interface
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	const ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getRenderSystem()->getDevice(), GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->deviceContext);

	// UINames uiNames;
	// ProfilerScreen* profilerScreen = new ProfilerScreen();
	// this->uiTable[uiNames.PROFILER_SCREEN] = profilerScreen;
	// this->uiList.push_back(profilerScreen);
	//
	// MenuScreen* menuScreen = new MenuScreen();
	// this->uiTable[uiNames.MENU_SCREEN] = menuScreen;
	// this->uiList.push_back(menuScreen);
	//
	// InspectorScreen* inspectorScreen = new InspectorScreen();
	// this->uiTable[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
	// this->uiList.push_back(inspectorScreen);
	//
	// HierarchyScreen* hierarchyScreen = new HierarchyScreen();
	// this->uiTable[uiNames.HIERARCHY_SCREEN] = hierarchyScreen;
	// this->uiList.push_back(hierarchyScreen);
}

UIManager::~UIManager()
{
	delete sharedInstance;
}
