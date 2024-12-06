#include "MenuScreen.h"

#include "ActionHistory.h"
#include "AppWindow.h"
#include "BaseComponentSystem.h"
#include "FileUtils.h"
#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "MeshManager.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "Renderer3D.h"
#include "SceneManager.h"
#include "ShaderLibrary.h"
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
		if (ImGui::MenuItem("Load OBJ..."))
		{
			onLoadObjClicked();
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

	cube->attachComponent(new Renderer3D(cube.get(), cubeMesh));
	// PhysicsComponent* staticPhysics = new PhysicsComponent(cube.get(), PrimitiveType::CUBE);
	// staticPhysics->getRigidBody()->setType(reactphysics3d::BodyType::STATIC);
	// cube->attachComponent(staticPhysics);
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

	sphere->attachComponent(new Renderer3D(sphere.get(), sphereMesh));
	PhysicsComponent* staticPhysics = new PhysicsComponent(sphere.get(), PrimitiveType::SPHERE);
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

	capsule->attachComponent(new Renderer3D(capsule.get(), capsuleMesh));
	PhysicsComponent* staticPhysics = new PhysicsComponent(capsule.get(), PrimitiveType::CAPSULE);
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
	//plane->setLocalRotation({90 * (M_PI / 180.f), 0, 0});
	plane->setLocalScale({ 2.f, 1.0f, 2.f });

	plane->attachComponent(new Renderer3D(plane.get(), planeMesh));
	PhysicsComponent* staticPhysics = new PhysicsComponent(plane.get(), PrimitiveType::PLANE);
	staticPhysics->getRigidBody()->setType(reactphysics3d::BodyType::KINEMATIC);
	plane->attachComponent(staticPhysics);
	GameObjectManager::get()->addObject(plane);

	LogUtils::log("Created Plane");
}

void MenuScreen::onCreatePhysicsDemoClicked()
{
	int maxCubes = 100;
	for (int i = 0; i < maxCubes; ++i)
	{
		GameObjectPtr cube = std::make_shared<GameObject>("Cube" + std::to_string(i));
		//MeshPtr cubeMesh = std::make_shared<Mesh>(L"assets/models/cube.obj");
		//MeshPtr cubeMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"assets/models/cube.obj");
		MeshPtr cubeMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromPrimitiveType(PrimitiveType::CUBE);
		MaterialPtr mat = std::make_shared<Material>(ShaderLibrary::get()->getPixelShader(L"PixelShader.hlsl"));
		mat->setAlbedo(GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"assets/images/waffle.jpg"));
		//cube->setLocalScale(0.1f);
		cube->setLocalPosition({ randomRangeFloat(-8, 8), randomRangeFloat(1, 20), randomRangeFloat(-8, 8) });
		cube->setLocalRotation(randomRangeVector3D(0, 360) * (M_PI / 180.f));

		cube->attachComponent(new Renderer3D(cube.get(), cubeMesh, mat));
		PhysicsComponent* cubePhysics = new PhysicsComponent(cube.get(), PrimitiveType::CUBE);
		cube->attachComponent(cubePhysics);
		GameObjectManager::get()->addObject(cube);
	}

	// GameObjectPtr plane1 = std::make_shared<GameObject>("Plane1");
	// //MeshPtr planeMesh = std::make_shared<Mesh>(L"assets/models/cube.obj");
	// //MeshPtr planeMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"assets/models/cube.obj");
	// MeshPtr planeMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromPrimitiveType(PrimitiveType::PLANE);
	//
	// plane1->setLocalPosition({ 0, 5, 10 });
	// plane1->setLocalRotation({ 90 * (M_PI / 180.f), 0, 0 });
	// plane1->setLocalScale({ 2.f, 1.0f, 2.f });
	//
	// plane1->attachComponent(new Renderer3D(plane1.get(), planeMesh));
	// PhysicsComponent* staticPhysics1 = new PhysicsComponent(plane1.get(), PrimitiveType::PLANE);
	// staticPhysics1->getRigidBody()->setType(reactphysics3d::BodyType::KINEMATIC);
	// plane1->attachComponent(staticPhysics1);
	// GameObjectManager::get()->addObject(plane1);
	//
	// GameObjectPtr plane2 = std::make_shared<GameObject>("Plane2");
	//
	// plane2->setLocalPosition({ 0, 5, -10 });
	// plane2->setLocalRotation({ 90 * (M_PI / 180.f), 0, 0 });
	// plane2->setLocalScale({ 2.f, 1.0f, 2.f });
	//
	// plane2->attachComponent(new Renderer3D(plane2.get(), planeMesh));
	// PhysicsComponent* staticPhysics2 = new PhysicsComponent(plane2.get(), PrimitiveType::PLANE);
	// staticPhysics2->getRigidBody()->setType(reactphysics3d::BodyType::KINEMATIC);
	// plane2->attachComponent(staticPhysics2);
	// GameObjectManager::get()->addObject(plane2);
	//
	// GameObjectPtr plane3 = std::make_shared<GameObject>("Plane3");
	//
	// plane3->setLocalPosition({ 10, 5, 0 });
	// plane3->setLocalRotation({ 0, 0, 90 * (M_PI / 180.f) });
	// plane3->setLocalScale({ 2.f, 1.0f, 2.f });
	//
	// plane3->attachComponent(new Renderer3D(plane3.get(), planeMesh));
	// PhysicsComponent* staticPhysics3 = new PhysicsComponent(plane3.get(), PrimitiveType::PLANE);
	// staticPhysics3->getRigidBody()->setType(reactphysics3d::BodyType::KINEMATIC);
	// plane3->attachComponent(staticPhysics3);
	// GameObjectManager::get()->addObject(plane3);
	//
	// GameObjectPtr plane4 = std::make_shared<GameObject>("Plane4");
	//
	// plane4->setLocalPosition({ -10, 5, 0 });
	// plane4->setLocalRotation({ 0, 0, 90 * (M_PI / 180.f) });
	// plane4->setLocalScale({ 2.f, 1.0f, 2.f });
	//
	// plane4->attachComponent(new Renderer3D(plane4.get(), planeMesh));
	// PhysicsComponent* staticPhysics4 = new PhysicsComponent(plane4.get(), PrimitiveType::PLANE);
	// staticPhysics4->getRigidBody()->setType(reactphysics3d::BodyType::KINEMATIC);
	// plane4->attachComponent(staticPhysics4);
	// GameObjectManager::get()->addObject(plane4);

	LogUtils::log("Created " + std::to_string(maxCubes) + " Physics Cubes");
}

void MenuScreen::onLoadObjClicked()
{
	// TODO: LOAD OBJ FROM FILE AND CREATE OBJECT IN SCENE
	// CALL MESH MANAGER EXAMPLE

	string meshFilePath;
	string fileName;

	FileUtils::getFilePath(meshFilePath, fileName);

	if (!meshFilePath.empty()) {
		LogUtils::log("Loading OBJ from path: " + meshFilePath);
	}

	GameObjectPtr mesh = std::make_shared<GameObject>(fileName + " Mesh");

	MeshPtr customMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(std::wstring(meshFilePath.begin(), meshFilePath.end()).c_str());
	mesh->attachComponent(new Renderer3D(mesh.get(), customMesh));
	GameObjectManager::get()->addObject(mesh);
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
