#include "AppWindow.h"

#include "GameObjectManager.h"
#include "MeshManager.h"

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::get()
{
	if (!sharedInstance)
		sharedInstance = new AppWindow();

	return sharedInstance;
}

AppWindow::AppWindow()
= default;

AppWindow::~AppWindow()
{
	Window::~Window();
	delete sharedInstance;
}

void AppWindow::onKeyDown(const int key)
{
	if (!CameraManager::getInstance()->activeCamera)
		return;

	switch (key)
	{
	case VK_ESCAPE:
	{
		LogUtils::log(this, "Exiting application");
		this->windowIsRunning = false;
		//exit(0);
		break;
	}
	default:
	{
		break;
	}
	}
}

void AppWindow::onKeyUp(const int key)
{
	switch (key)
	{
		//case 'W':
		//{
		//	LogUtils::log(this, "Pressed W!");
		//	break;
		//}
	case VK_SPACE:
	{
		// float randsize = randrange_float(0.1f, 1.0f);
		// Vec2 size = { randsize, randsize };
		// Vector3D pos = { randrange_float(-0.8f, 0.8f), randrange_float(-0.8f, 0.8f), randrange_float(-0.8f, 0.8f) };
		//
		// std::cout << "position: " << pos << std::endl;
		// circleVector.emplace_back(size, pos);
		//circleVector.emplace_back();
		break;
	}
	default:
	{
		break;
	}
	}
}

void AppWindow::onMouseMove(const Vector2D& mousePosition)
{

}

void AppWindow::onLeftMouseDown(const Vector2D& mousePosition)
{
}

void AppWindow::onLeftMouseUp(const Vector2D& mousePosition)
{
}

void AppWindow::onRightMouseDown(const Vector2D& mousePosition)
{
}

void AppWindow::onRightMouseUp(const Vector2D& mousePosition)
{
}

void AppWindow::onCreate()
{
	Window::onCreate();

	//GraphicsEngine::get()->getRenderSystem()->init();
	//GraphicsEngine::get()->initialize();
	UIManager::initialize(this->windowHandle);
	CameraManager::initialize();

	const RECT rc = this->getClientWindowRect();
	swapChain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->windowHandle, rc.right - rc.left, rc.bottom - rc.top);

	InputSystem::get()->addListener(this);

	// camera
	CameraManager::getInstance()->activeCamera = new SceneCamera("Camera", false, rc);

	CameraManager::getInstance()->activeCamera->setPosition({ 0.0f, 0.0f, -1.0f });

	void* shaderByteCode = nullptr;
	size_t byteCodeSize = 0;

	LogUtils::log(this, "Vertex shader compilation");
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "main", &shaderByteCode, &byteCodeSize);
	vertexShader = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shaderByteCode, byteCodeSize);

	// Insert all GameObjects here

	//const std::shared_ptr<Mesh> bunny = std::make_shared<Mesh>(L"assets/models/bunny.obj", "bunny");
	//const std::shared_ptr<Mesh> bunny = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"assets/models/bunny.obj");
	//GameObjectManager::get()->addObject(bunny);
	//bunny->setPosition({ -1, 0, 0 });
	//bunny->setScale(5.f);
	// bunny->interpolateScale = true;
	// bunny->scale1 = 5.f;
	// bunny->scale2 = 7.f;


	// const std::shared_ptr<Mesh> teapot = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"assets/models/teapot.obj");
	// GameObjectManager::get()->addObject(teapot);
	// teapot->setPosition({ 1, 0, 0 });

	const std::shared_ptr<Mesh> armadillo = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"assets/models/armadillo.obj");
	GameObjectManager::get()->addObject(armadillo);
	armadillo->setScale(0.5f);
	// armadillo->setPosition({ 0, 0, 2 });


	// const std::shared_ptr<Plane> floor = std::make_shared<Plane>("floor", shaderByteCode, byteCodeSize, Vector3D(0.3f, 0.4f, 0.1f));
	// floor->setRotation({ 1.57f, 0.f });
	// floor->setScale({ 100.f, 100.f, 100.f });
	// floor->setPosition({ 0.0f, -1.0f, 0.0f });
	// GameObjectManager::get()->addObject(floor);
	//
	// const std::shared_ptr<Plane> ceiling = std::make_shared<Plane>("ceiling", shaderByteCode, byteCodeSize, Vector3D(0.15f, 0.2f, 0.60f));
	// ceiling->setRotation({ 1.57f, 0.f });
	// ceiling->setScale({ 100.f, 100.f, 100.f });
	// ceiling->setPosition({ 0.0f, 50.0f, 0.0f });
	// GameObjectManager::get()->addObject(ceiling);
	//
	// const std::shared_ptr<Plane> wall1 = std::make_shared<Plane>("wall1", shaderByteCode, byteCodeSize, Vector3D(0.15f, 0.2f, 0.60f));
	// wall1->setRotation({ 0.f, 0.f });
	// wall1->setScale({ 100.f, 100.f, 100.f });
	// wall1->setPosition({ 0.0f, 49.0f, 50.0f });
	// GameObjectManager::get()->addObject(wall1);
	//
	// const std::shared_ptr<Plane> wall2 = std::make_shared<Plane>("wall2", shaderByteCode, byteCodeSize, Vector3D(0.15f, 0.2f, 0.60f));
	// wall2->setRotation({ 0.f, 0.f });
	// wall2->setScale({ 100.f, 100.f, 100.f });
	// wall2->setPosition({ 0.0f, 49.0f, -50.0f });
	// GameObjectManager::get()->addObject(wall2);
	//
	// const std::shared_ptr<Plane> wall3 = std::make_shared<Plane>("wall3", shaderByteCode, byteCodeSize, Vector3D(0.15f, 0.2f, 0.60f));
	// wall3->setRotation({ 0.f, 1.57f });
	// wall3->setScale({ 100.f, 100.f, 100.f });
	// wall3->setPosition({ 50.0f, 49.0f, 0.0f });
	// GameObjectManager::get()->addObject(wall3);
	//
	// const std::shared_ptr<Plane> wall4 = std::make_shared<Plane>("wall4", shaderByteCode, byteCodeSize, Vector3D(0.15f, 0.2f, 0.60f));
	// wall4->setRotation({ 0.f, 1.57f });
	// wall4->setScale({ 100.f, 100.f, 100.f });
	// wall4->setPosition({ -50.0f, 49.0f, 0.0f });
	// GameObjectManager::get()->addObject(wall4);
	//
	// const std::shared_ptr<Plane> plane = std::make_shared<Plane>("plane", shaderByteCode, byteCodeSize);
	// plane->setRotation({ 1.57f, 0.f });
	// plane->setScale(2.f);
	// plane->rotationSpeed = randomRangeFloat(1.f, 2.f);
	// plane->rotationDirection = randomRangeVector3D(-1.f, 1.f);
	//GameObjectManager::get()->addObject(plane);

	// 1. Rainbow cube
	// Cube* cube = new Cube("cube", shaderByteCode, byteCodeSize);
	// cube->setPosition({ 0.f, 0.f, 0.f });
	// gameObjectsVector.push_back(cube);

	// 2. Rotating white cube
	// const std::shared_ptr<Cube> cube = std::make_shared<Cube>("cube", shaderByteCode, byteCodeSize, 1.f);
	// cube->setPosition({ -1.f, 0.f, 0.f });
	// cube->rotationDirection = randomRangeVector3D(-1.f, 1.f);
	// cube->rotationSpeed = randomRangeFloat(1.f, 2.f);
	//GameObjectManager::get()->addObject(cube);

	// const std::shared_ptr<Cylinder> cylinder = std::make_shared<Cylinder>("cylinder", shaderByteCode, byteCodeSize, 1.f);
	// cylinder->setPosition({ 1.f, 0.f, 0.f });
	// cylinder->rotationDirection = randomRangeVector3D(-1.f, 1.f);
	// cylinder->rotationSpeed = randomRangeFloat(1.f, 2.f);
	// GameObjectManager::get()->addObject(cylinder);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	LogUtils::log(this, "Geometry shader compilation");
	GraphicsEngine::get()->getRenderSystem()->compileGeometryShader(L"GeometryShader.hlsl", "main", &shaderByteCode, &byteCodeSize);
	geometryShader = GraphicsEngine::get()->getRenderSystem()->createGeometryShader(shaderByteCode, byteCodeSize);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	LogUtils::log(this, "Pixel shader compilation");
	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "main", &shaderByteCode, &byteCodeSize);
	pixelShader = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shaderByteCode, byteCodeSize);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	mainMaterial = std::make_shared<Material>(pixelShader);
	mainMaterial->samplerState = GraphicsEngine::get()->getRenderSystem()->createSamplerState();
	UIManager::get()->mainMaterial = mainMaterial;
}

void AppWindow::onUpdate()
{
	//LogUtils::log(this, "Updating window");
	Window::onUpdate();
	//LogUtils::log(this, "Updating input system");
	InputSystem::get()->update();

	ticks += EngineTime::getDeltaTime() * 1.0f;

	//LogUtils::log(this, "Setting shaders");
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setGeometryShader(geometryShader);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	//LogUtils::log(this, "Clear render target");
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(
		this->swapChain,
		0.3f,
		0.3f,
		0.3f,
		1.f);

	const auto& [left, top, right, bottom] = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(right - left, bottom - top);

	//GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	//GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setGeometryShader(geometryShader1);
	//GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	GameObjectManager::get()->updateAll(EngineTime::getDeltaTime());
	GameObjectManager::get()->drawAll(vertexShader, geometryShader, *mainMaterial, getClientWindowRect());

	UIManager::get()->draw();

	swapChain->present(true);
}

void AppWindow::onFocus()
{
	Window::onFocus();
	InputSystem::get()->setEnabled(true);
}

void AppWindow::onKillFocus()
{
	Window::onKillFocus();
	InputSystem::get()->setEnabled(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	//vertexBuffer->release();
	// swapChain->release();
	// vertexShader->release();
	// pixelShader->release();


	//GraphicsEngine::get()->getRenderSystem()->release();
}
