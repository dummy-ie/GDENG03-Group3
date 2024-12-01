#include "MenuScreen.h"

#include "AppWindow.h"
#include "BaseComponentSystem.h"
#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "Mesh.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "Renderer3D.h"
#include "UIManager.h"
#include "ViewportManager.h"

using namespace gdeng03;

MenuScreen::MenuScreen() : UIScreen("MenuScreen")
{
	LogUtils::logHResult(
		this,
		DirectX::CreateWICTextureFromFile(
			GraphicsEngine::get()->getRenderSystem()->getDevice(),
			L"assets/images/pompom logo.png",
			nullptr,
			creditsTexture.ReleaseAndGetAddressOf()));
}

void MenuScreen::setMaterialEditor(bool* isMaterialEditorOpen)
{
	this->isMaterialEditorOpen = isMaterialEditorOpen;
}

void MenuScreen::draw()
{

	if (!LogUtils::logBool(this, ImGui::BeginMainMenuBar())) return;

	// File header
	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("Open..", "Ctrl+O"))
		{
		}
		if (ImGui::MenuItem("Save", "Ctrl+S"))
		{
		}
		if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
		{
		}

		ImGui::Separator();

		if (ImGui::MenuItem("Quit", "Ctrl+W"))
		{
			AppWindow::get()->onDestroy();
		}
		ImGui::EndMenu();
	}

	// Game Object header
	if (ImGui::BeginMenu("Game Object")) {
		if (ImGui::MenuItem("Create Cube"))
		{
			onCreateCubeClicked();
		}
		if (ImGui::MenuItem("Create Sphere"))
		{
			onCreateSphereClicked();
		}
		if (ImGui::MenuItem("Create Plane"))
		{
			onCreatePlaneClicked();
		}
		if (ImGui::MenuItem("Create Physics Demo"))
		{
			onCreatePhysicsDemoClicked();
		}

		ImGui::Separator();

		if (ImGui::BeginMenu("Light"))
		{
			if (ImGui::MenuItem("Point Light"))
			{
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}

	// About header
	if (ImGui::BeginMenu("About"))
	{
		if (ImGui::MenuItem("Credits", nullptr, isCreditsOpen))
		{
			isCreditsOpen = !isCreditsOpen;
		}
		ImGui::EndMenu();
	}

	// Test header
	if (ImGui::BeginMenu("Windows"))
	{
		if (ImGui::MenuItem("Inspector")) {
			UIManager::get()->setActive("Inspector Screen");
		}
		if (ImGui::MenuItem("Hierarchy")) {
			UIManager::get()->setActive("Hierarchy Screen");
		}
		if (ImGui::MenuItem("Profiler")) {
			UIManager::get()->setActive("Profiler Screen");
		}
		if (ImGui::MenuItem("Debug Console")) {
			UIManager::get()->setActive("Debug Screen");
		}
		if (ImGui::BeginMenu("Viewport"))
		{
			if (ImGui::MenuItem("Create Viewport"))
			{
				ViewportManager::get()->createViewport();
			}
			if (ImGui::MenuItem("Single Viewport"))
			{
				ViewportManager::get()->setNumViewports(1);
			}
			if (ImGui::MenuItem("2 Viewports"))
			{
				ViewportManager::get()->setNumViewports(2);
			}
			if (ImGui::MenuItem("3 Viewports"))
			{
				ViewportManager::get()->setNumViewports(3);
			}
			if (ImGui::MenuItem("4 Viewports"))
			{
				ViewportManager::get()->setNumViewports(4);
			}
			if (ImGui::MenuItem("Delete All Viewports"))
			{
				ViewportManager::get()->deleteAllViewports();
			}
			ImGui::EndMenu();
		}
		if (isMaterialEditorOpen != nullptr)
			if (ImGui::MenuItem("Material Editor", nullptr, *isMaterialEditorOpen))
			{
				*isMaterialEditorOpen = !(*isMaterialEditorOpen);
			}

		if (ImGui::MenuItem("Color Picker", nullptr, isColorPickerOpen))
		{
			isColorPickerOpen = !isColorPickerOpen;
		}

		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();

	if (isCreditsOpen)
		showCreditsWindow();

	if (isColorPickerOpen)
		showColorPickerWindow();
}

void MenuScreen::onCreateCubeClicked()
{

	LogUtils::log("Created Cube");
}

void MenuScreen::onCreateSphereClicked()
{
	LogUtils::log("Created Sphere");
}

void MenuScreen::onCreatePlaneClicked()
{
	GameObjectPtr plane = std::make_shared<GameObject>("Plane");
	MeshPtr planeMesh = std::make_shared<Mesh>(L"assets/models/cube.obj", "planeMesh");
	plane->setLocalPosition({ 0, -5, 20 });
	plane->setLocalScale({ 10, 0.1, 10 });

	plane->attachComponent(new Renderer3D("planeRenderer", plane.get(), planeMesh, UIManager::get()->mainMaterial));
	PhysicsComponent* staticPhysics = new PhysicsComponent("planePhysics", plane.get());
	staticPhysics->getRigidBody()->setType(reactphysics3d::BodyType::STATIC);
	plane->attachComponent(staticPhysics);
	GameObjectManager::get()->addObject(plane);

	LogUtils::log("Created Plane");
}

void MenuScreen::onCreatePhysicsDemoClicked()
{
	for (int i = 0; i < 10; ++i)
	{
		GameObjectPtr cube = std::make_shared<GameObject>("Cube" + std::to_string(i));
		MeshPtr cubeMesh = std::make_shared<Mesh>(L"assets/models/cube.obj", "cubeMesh" + std::to_string(i));
		cube->setLocalScale(1.f);
		cube->setLocalPosition({ 0, 10, 20 });

		cube->attachComponent(new Renderer3D("cubeRenderer" + std::to_string(i), cube.get(), cubeMesh, UIManager::get()->mainMaterial));
		PhysicsComponent* cubePhysics = new PhysicsComponent("cubePhysics" + std::to_string(i), cube.get());
		cube->attachComponent(cubePhysics);
		GameObjectManager::get()->addObject(cube);
	}

	LogUtils::log("Created 10 Physics Cubes");
}

void MenuScreen::showCreditsWindow()
{
	if (ImGui::Begin("Credits", &isCreditsOpen))
	{
		constexpr ImVec2 imageSize = { 200, 200 };
		ImGui::Image(static_cast<ImTextureID>(reinterpret_cast<intptr_t>(creditsTexture.Get())), imageSize);
		ImGui::TextColored(ImVec4(0.3f, 0.4f, 1.0f, 1.0f), "MRLOL.engine v0.01 \n");

		ImGui::NewLine();
		ImGui::Text(
			"About: \n"
			"Developed by Marcus Rene Levin Oliva-Leocario \n"
			"In partial fulfillment of the requirements for GDENG03"
		);

		ImGui::NewLine();
		ImGui::Text(
			"Acknowledgements: \n"
			"Dr. Neil Del Gallego's GDENG03 Course \n"
			"PardCode Game Engine Tutorial \n"
			"Joachim Arguelles \n"
			"James Ursua \n"
			"Uriel Pascual \n"
			"Rimuru Tempest \n"
		);
		ImGui::NewLine();

		ImGui::Separator();

		ImGui::Text("Dear ImGui Version: %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);

		if (ImGui::Button("OK"))
			isCreditsOpen = false;
	}
	ImGui::End();
}

void MenuScreen::showColorPickerWindow()
{
	if (ImGui::Begin("Color Picker", &isColorPickerOpen))
	{
		static ImVec4 color(1.0f, 0.0f, 1.0f, 0.5f);
		ImGui::SameLine();
		ImGui::ColorPicker4("MyColor##4", reinterpret_cast<float*>(&color), 0);
	}
	ImGui::End();
}
