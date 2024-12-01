#include "MenuScreen.h"

#include "ActionHistory.h"
#include "AppWindow.h"
#include "BaseComponentSystem.h"
#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "MeshManager.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "Renderer3D.h"
#include "SceneManager.h"
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

// void MenuScreen::setMaterialEditor(bool* isMaterialEditorOpen)
// {
// 	this->isMaterialEditorOpen = isMaterialEditorOpen;
// }

void MenuScreen::draw()
{

	if (!LogUtils::logBool(this, ImGui::BeginMainMenuBar())) return;

	// File header
	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("Undo", "Ctrl+Z"))
		{
			GameObjectManager::get()->applyAction(ActionHistory::get()->undoAction());
		}
		if (ImGui::MenuItem("Redo", "Ctrl+Y"))
		{
			GameObjectManager::get()->applyAction(ActionHistory::get()->redoAction());
		}
		if (ImGui::MenuItem("Open..", "Ctrl+O"))
		{
			SceneManager::getInstance()->readFile();
		}
		if (ImGui::MenuItem("Save", "Ctrl+S"))
		{
			SceneManager::getInstance()->writeFile();
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
		if (ImGui::MenuItem("Create Capsule"))
		{
			onCreateCapsuleClicked();
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
		if (ImGui::MenuItem("Inspector", nullptr, UIManager::get()->getActive("InspectorScreen"))) {
			UIManager::get()->setActive("InspectorScreen");
		}
		if (ImGui::MenuItem("Hierarchy", nullptr, UIManager::get()->getActive("HierarchyScreen"))) {
			UIManager::get()->setActive("HierarchyScreen");
		}
		if (ImGui::MenuItem("Profiler", nullptr, UIManager::get()->getActive("ProfilerScreen"))) {
			UIManager::get()->setActive("ProfilerScreen");
		}
		if (ImGui::MenuItem("Debug Console", nullptr, UIManager::get()->getActive("DebugScreen"))) {
			UIManager::get()->setActive("DebugScreen");
		}
		if (ImGui::MenuItem("Playback Options", nullptr, UIManager::get()->getActive("PlaybackScreen"))) {
			UIManager::get()->setActive("PlaybackScreen");
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
		if (ImGui::MenuItem("Material Editor", nullptr, UIManager::get()->getActive("MaterialEditor")))
		{
			UIManager::get()->setActive("MaterialEditor");
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
	GameObjectPtr cube = std::make_shared<GameObject>("Cube");
	//MeshPtr planeMesh = std::make_shared<Mesh>(L"assets/models/cube.obj");
	MeshPtr cubeMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromPrimitiveType(PrimitiveType::CUBE);

	//cube->setLocalPosition({ 0, -5, 20 });
	//cube->setLocalScale({ 10, 0.1, 10 });

	cube->attachComponent(new Renderer3D("RendererComponent " + cube->getUniqueName(), cube.get(), cubeMesh));
	PhysicsComponent* staticPhysics = new PhysicsComponent("PhysicsComponent " + cube->getUniqueName(), cube.get(), PrimitiveType::CUBE);
	staticPhysics->getRigidBody()->setType(reactphysics3d::BodyType::STATIC);
	cube->attachComponent(staticPhysics);
	GameObjectManager::get()->addObject(cube);
	LogUtils::log("Created " + cube->getUniqueName());
}

void MenuScreen::onCreateSphereClicked()
{
	GameObjectPtr sphere = std::make_shared<GameObject>("Sphere");
	//MeshPtr planeMesh = std::make_shared<Mesh>(L"assets/models/cube.obj");
	MeshPtr sphereMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromPrimitiveType(PrimitiveType::SPHERE);

	//sphere->setLocalPosition({ 0, -5, 20 });
	//sphere->setLocalScale({ 10, 0.1, 10 });

	sphere->attachComponent(new Renderer3D("RendererComponent " + sphere->getUniqueName(), sphere.get(), sphereMesh));
	PhysicsComponent* staticPhysics = new PhysicsComponent("PhysicsComponent " + sphere->getUniqueName(), sphere.get(), PrimitiveType::SPHERE);
	staticPhysics->getRigidBody()->setType(reactphysics3d::BodyType::STATIC);
	sphere->attachComponent(staticPhysics);
	GameObjectManager::get()->addObject(sphere);
	LogUtils::log("Created Sphere");
}

void MenuScreen::onCreateCapsuleClicked()
{
	GameObjectPtr capsule = std::make_shared<GameObject>("Capsule");
	//MeshPtr planeMesh = std::make_shared<Mesh>(L"assets/models/cube.obj");
	MeshPtr capsuleMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromPrimitiveType(PrimitiveType::CAPSULE);

	// capsule->setLocalPosition({ 0, -5, 20 });
	// capsule->setLocalScale({ 10, 0.1, 10 });

	capsule->attachComponent(new Renderer3D("RendererComponent " + capsule->getUniqueName(), capsule.get(), capsuleMesh));
	PhysicsComponent* staticPhysics = new PhysicsComponent("PhysicsComponent " + capsule->getUniqueName(), capsule.get(), PrimitiveType::CAPSULE);
	staticPhysics->getRigidBody()->setType(reactphysics3d::BodyType::STATIC);
	capsule->attachComponent(staticPhysics);
	GameObjectManager::get()->addObject(capsule);
	LogUtils::log("Created Capsule");
}

void MenuScreen::onCreatePlaneClicked()
{
	GameObjectPtr plane = std::make_shared<GameObject>("Plane");
	//MeshPtr planeMesh = std::make_shared<Mesh>(L"assets/models/cube.obj");
	//MeshPtr planeMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"assets/models/cube.obj");
	MeshPtr planeMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromPrimitiveType(PrimitiveType::PLANE);

	//plane->setLocalPosition({ 0, -5, 0 });
	plane->setLocalScale({ 20.f, 1.0f, 20.f });

	plane->attachComponent(new Renderer3D("RendererComponent " + plane->getUniqueName(), plane.get(), planeMesh));
	PhysicsComponent* staticPhysics = new PhysicsComponent("PhysicsComponent " + plane->getUniqueName(), plane.get(), PrimitiveType::PLANE);
	staticPhysics->getRigidBody()->setType(reactphysics3d::BodyType::KINEMATIC);
	plane->attachComponent(staticPhysics);
	GameObjectManager::get()->addObject(plane);

	LogUtils::log("Created Plane");
}

void MenuScreen::onCreatePhysicsDemoClicked()
{
	for (int i = 0; i < 10; ++i)
	{
		GameObjectPtr cube = std::make_shared<GameObject>("Cube" + std::to_string(i));
		//MeshPtr cubeMesh = std::make_shared<Mesh>(L"assets/models/cube.obj");
		//MeshPtr cubeMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"assets/models/cube.obj");
		MeshPtr cubeMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromPrimitiveType(PrimitiveType::CUBE);

		//cube->setLocalScale(0.1f);
		cube->setLocalPosition({ 0, 10, 0 });

		cube->attachComponent(new Renderer3D("RendererComponent " + cube->getUniqueName() + std::to_string(i), cube.get(), cubeMesh));
		PhysicsComponent* cubePhysics = new PhysicsComponent("PhysicsComponent " + cube->getUniqueName() + std::to_string(i), cube.get(), PrimitiveType::CUBE);
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
