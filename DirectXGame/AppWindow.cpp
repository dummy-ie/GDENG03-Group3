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
		CameraManager::getInstance()->activeCamera->forward = 1.0f;
		break;
	case 'S':
		CameraManager::getInstance()->activeCamera->forward = -1.0f;
		break;
	case 'A':
		CameraManager::getInstance()->activeCamera->rightward = -1.0f;
		break;
	case 'D':
		CameraManager::getInstance()->activeCamera->rightward = 1.0f;
		break;
	default:
		break;
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
	case VK_ESCAPE:
		exit(0);
		break;
		// case VK_DELETE:
		// 	circleVector.clear();
		// 	break;
		// case VK_BACK:
		// {
		// 	if (!circleVector.empty())
		// 		circleVector.pop_back();
		// 	break;
		// }
	default:
	{
		if (!CameraManager::getInstance()->activeCamera)
			break;

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

	const Vector3D currentRotation = CameraManager::getInstance()->activeCamera->getRotation();

	float xRotation = currentRotation.x;
	float yRotation = currentRotation.y;

	xRotation += (mousePosition.y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	yRotation += (mousePosition.x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;

	CameraManager::getInstance()->activeCamera->setRotation({ xRotation, yRotation });

	if (this->isFocused())
		InputSystem::get()->setCursorPosition(Vector2D(width / 2.0f, height / 2.0f));
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

	CameraManager::getInstance()->activeCamera = new Camera("Camera", false, rc, 90, 0.1f, 100.0f);
	CameraManager::getInstance()->activeCamera->view.setTranslation({ 0.0f, 0.0f, -2.0f });

	void* shaderByteCode = nullptr;
	size_t byteCodeSize = 0;

	LogUtils::log(this, "Vertex shader compilation");
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "main", &shaderByteCode, &byteCodeSize);
	vertexShader = GraphicsEngine::createVertexShader(shaderByteCode, byteCodeSize);

	// Insert all GameObjects here
	// Circle* circle = new Circle("circle1", shaderByteCode, byteCodeSize, 0.5f);
	// gameObjectsVector.push_back(circle);

	gameObjectsVector.reserve(5);

	Plane* plane = new Plane("plane", shaderByteCode, byteCodeSize);
	plane->setRotation({ 0.f, 45.f });
	plane->setScale(2.f);
	plane->setPosition({ 0.0f, 0.0f, 2.0f });
	plane->rotationSpeed = randomRangeFloat(1.f, 2.f);
	plane->rotationDirection = randomRangeVector3D(-1.f, 1.f);
	gameObjectsVector.push_back(plane);

	Cube* cube = new Cube("cube", shaderByteCode, byteCodeSize);
	// cube->rotationDirection = randomRangeVector3D(-1.f, 1.f);
	// cube->rotationSpeed = randomRangeFloat(1.f, 2.f);
	cube->setPosition({ 0.f, 0.f, 2.f });
	gameObjectsVector.push_back(cube);

	// Quad* quad = new Quad("quad", shaderByteCode, byteCodeSize);
	// quad->setPosition({ 0.f, 0.f, 1.f });
	// quad->originalPosition = {0.f, 0.f, 1.f};
	// quad->moveDirection = {0.f, -1.f, 0.f};
	// quad->setScale(0.1f);
	// gameObjectsVector.push_back(quad);

	// for (int i = 0; i < 100; ++i)
	// {
	// 	Cube* cube = new Cube("cube", shaderByteCode, byteCodeSize);
	// 	cube->setPosition({ randomRangeFloat(-5.0f, 5.0f) , randomRangeFloat(-5.0f, 5.0f) , randomRangeFloat(1.0f, 10.0f) });
	// 	cube->rotationDirection = randomRangeVector3D(-1.f, 1.f);
	// 	cube->rotationSpeed = randomRangeFloat(1.f, 2.f);
	// 	//cube->setScale({0.1f, 0.01f, 0.1f});
	// 	gameObjectsVector.push_back(cube);
	// }

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

	//LogUtils::log(this, "update and draw circles");
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
