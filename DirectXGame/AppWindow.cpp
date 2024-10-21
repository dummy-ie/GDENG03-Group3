#include "AppWindow.h"

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::get()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
}

void AppWindow::destroy()
{
	if (sharedInstance != nullptr)
		sharedInstance->release();

	delete sharedInstance;
}

AppWindow::AppWindow()
= default;

AppWindow::~AppWindow()
= default;

void AppWindow::onKeyDown(const int key)
{
	if (!CameraManager::getInstance()->activeCamera)
		return;

	switch (key)
	{
	case 'W':
		CameraManager::getInstance()->activeCamera->forward = .5f;
		break;
	case 'S':
		CameraManager::getInstance()->activeCamera->forward = -.5f;
		break;
	case 'A':
		CameraManager::getInstance()->activeCamera->rightward = -.5f;
		break;
	case 'D':
		CameraManager::getInstance()->activeCamera->rightward = .5f;
		break;
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
		if (!CameraManager::getInstance()->activeCamera)
		{
			LogUtils::error(this, "No activeCamera!");
			break;
		}

		//LogUtils::log(this, "Camera reset forward and rightward");
		CameraManager::getInstance()->activeCamera->forward = 0.0f;
		CameraManager::getInstance()->activeCamera->rightward = 0.0f;
		break;
	}
	}
}

void AppWindow::onMouseMove(const Vector2D& mousePosition)
{
	const float width = static_cast<float>(this->getClientWindowRect().right - this->getClientWindowRect().left);
	const float height = static_cast<float>(this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	if (!CameraManager::getInstance()->activeCamera)
		return;

	if (!this->isFocused())
		return;

	const Vector3D currentRotation = CameraManager::getInstance()->activeCamera->getRotation();

	float xRotation = currentRotation.x;
	float yRotation = currentRotation.y;

	xRotation += (mousePosition.y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	yRotation += (mousePosition.x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;

	CameraManager::getInstance()->activeCamera->setRotation({ xRotation, yRotation });

	InputSystem::get()->setCursorPosition(Vector2D(width / 2.0f, height / 2.0f));
	InputSystem::get()->showCursor(false);
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

	//GraphicsEngine::get()->init();
	GraphicsEngine::initialize();
	CameraManager::initialize();

	swapChain = GraphicsEngine::get()->createSwapChain();

	const RECT rc = this->getClientWindowRect();
	swapChain->initialize(this->windowHandle, rc.right - rc.left, rc.bottom - rc.top);

	InputSystem::get()->addListener(this);
	//InputSystem::get()->showCursor(false);

	// perspective
	//CameraManager::getInstance()->activeCamera = new Camera("Camera", false, rc, 90, 0.1f, 100.0f);

	// orthographic
	CameraManager::getInstance()->activeCamera = new Camera("Camera", true, rc, 90, -10.0f, 100.0f);

	CameraManager::getInstance()->activeCamera->view.setTranslation({ 0.0f, 0.0f, .0f });

	void* shaderByteCode = nullptr;
	size_t byteCodeSize = 0;

	LogUtils::log(this, "Vertex shader compilation");
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "main", &shaderByteCode, &byteCodeSize);
	vertexShader = GraphicsEngine::createVertexShader(shaderByteCode, byteCodeSize);

	// Insert all GameObjects here

	gameObjectsVector.reserve(50);

	// Plane* plane = new Plane("plane", shaderByteCode, byteCodeSize);
	// plane->setRotation({ 0.f, 45.f });
	// plane->setScale(2.f);
	// plane->setPosition({ 0.0f, 0.0f, 0.0f });
	// plane->rotationSpeed = randomRangeFloat(1.f, 2.f);
	// plane->rotationDirection = randomRangeVector3D(-1.f, 1.f);
	// gameObjectsVector.push_back(plane);

	// 1. Rainbow cube
	// Cube* cube = new Cube("cube", shaderByteCode, byteCodeSize);
	// cube->setPosition({ 0.f, 0.f, 0.f });
	// gameObjectsVector.push_back(cube);

	// 2. Rotating white cube
	// Cube* cube = new Cube("cube", shaderByteCode, byteCodeSize, 1.f);
	// cube->setPosition({ 0.f, 0.f, 0.f });
	// gameObjectsVector.push_back(cube);
	// cube->rotationDirection = randomRangeVector3D(-1.f, 1.f);
	// cube->rotationSpeed = randomRangeFloat(1.f, 2.f);

	// 3. Translating and scaling rainbow cube
	// Cube* cube = new Cube("cube", shaderByteCode, byteCodeSize);
	// cube->setPosition({ 0.f, 0.f, 0.f });
	// cube->interpolatePosition = true;
	// cube->position1 = { -1.f, -1.f, 0.f };
	// cube->position2 = { 1.f, 1.f, 0.f };
	// cube->interpolateScale = true;
	// cube->scale1 = 0.25f;
	// cube->scale2 = 1.f;
	// gameObjectsVector.push_back(cube);

	// 4. 50 cubes randomly
	// for (int i = 0; i < 50; ++i)
	// {
	// 	Cube* cube = new Cube("cube" + std::to_string(i), shaderByteCode, byteCodeSize);
	// 	cube->setPosition({ randomRangeFloat(-20.0f, 20.0f) , randomRangeFloat(-20.0f, 20.0f) , randomRangeFloat(0.0f, 10.0f) });
	// 	cube->rotationDirection = randomRangeVector3D(-1.f, 1.f);
	// 	cube->rotationSpeed = randomRangeFloat(1.f, 2.f);
	// 	//cube->setScale({0.1f, 0.01f, 0.1f});
	// 	gameObjectsVector.push_back(cube);
	// }

	// 5. Scaling cube into plane
	// Cube* cube = new Cube("cube", shaderByteCode, byteCodeSize);
	// cube->setPosition({ 0.f, 0.f, 2.f });
	// cube->interpolateScale = true;
	// cube->scale1 = 1.f;
	// cube->scale2 = {2.0f, 0.5f, 2.f};
	// gameObjectsVector.push_back(cube);

	// 6. Cubes and plane scene
	// Cube* cube1 = new Cube("cube1", shaderByteCode, byteCodeSize, 1.f);
	// cube1->setPosition({ 0.f, 0.9f, 0.f });
	// gameObjectsVector.push_back(cube1);
	// Cube* cube2 = new Cube("cube2", shaderByteCode, byteCodeSize, 1.f);
	// cube2->setPosition({ -1.5f, 2.0f, 0.f });
	// gameObjectsVector.push_back(cube2);
	// Cube* cube3 = new Cube("cube3", shaderByteCode, byteCodeSize, 1.f);
	// cube3->setPosition({ -1.5f, 3.0f, -2.f });
	// gameObjectsVector.push_back(cube3);
	// Plane* plane = new Plane("plane", shaderByteCode, byteCodeSize, 1.f);
	// plane->setRotation({ -80.1f,0.f, 0.f });
	// plane->setScale(10.f);
	// plane->setPosition({ 0.0f, -0.5f, 0.0f });
	// gameObjectsVector.push_back(plane);

	// 7. Card stacking
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < i + 1; ++j)
		{
			Plane* card1 = new Plane("card1", shaderByteCode, byteCodeSize);
			card1->setRotation({ 0.5f,0.f, 0.f });
			card1->setScale({ 0.5f, 1.f, .7f });
			card1->setPosition({ 0.0f, -static_cast<float>(i) * 0.9f, 0.f + (j * 0.67f) - (i * 0.33f) });
			gameObjectsVector.push_back(card1);
			Plane* card2 = new Plane("card2", shaderByteCode, byteCodeSize);
			card2->setRotation({ -0.5f,0.f, 0.f });
			card2->setScale({ 0.5f, 1.f, .7f });
			card2->setPosition({ 0.0f, -static_cast<float>(i) * 0.9f, 0.33f + (j * 0.67f) - (i * 0.33f) });
			gameObjectsVector.push_back(card2);
		}
	}
	Plane* card3 = new Plane("card3", shaderByteCode, byteCodeSize);
	card3->setRotation({ 1.57f,0.0f, 0.f });
	card3->setScale({ 0.5f, 1.f, 1.0f });
	card3->setPosition({ 0.0f, -0.45f, 0.165f });
	gameObjectsVector.push_back(card3);

	Plane* card4 = new Plane("card4", shaderByteCode, byteCodeSize);
	card4->setRotation({ 1.57f,0.f, 0.f });
	card4->setScale({ 0.5f, 1.f, 1.0f });
	card4->setPosition({ 0.0f, -1.35f, 0.5f });
	gameObjectsVector.push_back(card4);

	Plane* card5 = new Plane("card5", shaderByteCode, byteCodeSize);
	card5->setRotation({ 1.57f,0.f, 0.f });
	card5->setScale({ 0.5f, 1.f, 1.0f });
	card5->setPosition({ 0.0f, -1.35f, -0.165f });
	gameObjectsVector.push_back(card5);

	GraphicsEngine::get()->releaseCompiledShader();

	LogUtils::log(this, "Geometry shader compilation");
	GraphicsEngine::get()->compileGeometryShader(L"GeometryShader.hlsl", "main", &shaderByteCode, &byteCodeSize);
	geometryShader = GraphicsEngine::createGeometryShader(shaderByteCode, byteCodeSize);
	GraphicsEngine::get()->releaseCompiledShader();

	// LogUtils::log(this, "Geometry shader 1 compilation");
	// GraphicsEngine::get()->compileGeometryShader(L"GeometryShader1.hlsl", "main", &shaderByteCode, &byteCodeSize);
	// geometryShader1 = GraphicsEngine::createGeometryShader(shaderByteCode, byteCodeSize);
	// GraphicsEngine::get()->releaseCompiledShader();

	LogUtils::log(this, "Pixel shader compilation");
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "main", &shaderByteCode, &byteCodeSize);
	pixelShader = GraphicsEngine::createPixelShader(shaderByteCode, byteCodeSize);
	GraphicsEngine::get()->releaseCompiledShader();
}

void AppWindow::onUpdate()
{
	//LogUtils::log(this, "Updating window");
	Window::onUpdate();
	//LogUtils::log(this, "Updating input system");
	InputSystem::get()->update();

	ticks += static_cast<float>(EngineTime::getDeltaTime()) * 1.0f;

	//LogUtils::log(this, "Setting shaders");
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setGeometryShader(geometryShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	//LogUtils::log(this, "Clear render target");
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(
		this->swapChain,
		0.15f,
		0.2f,
		0.60f,
		1.f);

	const RECT& rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setGeometryShader(geometryShader1);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	//LogUtils::log(this, "update and draw GOs");
	for (GameObject* gameObject : gameObjectsVector)
	{
		gameObject->update(static_cast<float>(EngineTime::getDeltaTime()));
		gameObject->draw(vertexShader, geometryShader, pixelShader, getClientWindowRect());
	}

	swapChain->present(true);
}

void AppWindow::onFocus()
{
	Window::onFocus();
}

void AppWindow::onKillFocus()
{
	Window::onKillFocus();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	//vertexBuffer->release();
	swapChain->release();
	vertexShader->release();
	pixelShader->release();

	//GraphicsEngine::get()->release();
	GraphicsEngine::destroy();
}
