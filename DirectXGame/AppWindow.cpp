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
	switch (key)
	{
	default:
		break;
	}
}

void AppWindow::onKeyUp(const int key)
{
	switch (key)
	{
	case 'W':
	{
		pressedW = true;
		LogUtils::log(this, "Pressed W!");
		break;
	}
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
		break;
	}
}

void AppWindow::onCreate()
{
	Window::onCreate();

	//GraphicsEngine::get()->init();
	GraphicsEngine::initialize();
	swapChain = GraphicsEngine::createSwapChain();

	const RECT rc = this->getClientWindowRect();
	swapChain->init(this->m_Hwnd, rc.right - rc.left, rc.bottom - rc.top);

	InputSystem::get()->addListener(this);

	void* shaderByteCode = nullptr;
	size_t byteCodeSize = 0;

	LogUtils::log(this, "Vertex shader compilation");
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "main", &shaderByteCode, &byteCodeSize);
	vertexShader = GraphicsEngine::createVertexShader(shaderByteCode, byteCodeSize);

	// Insert all GameObjects here
	// Circle* circle = new Circle("circle1", shaderByteCode, byteCodeSize, 0.5f);
	// gameObjectsVector.push_back(circle);

	for (int i = 0; i < 100; ++i)
	{
		Cube* cube = new Cube("cube" + std::to_string(i), shaderByteCode, byteCodeSize);
		cube->setPosition(randomRangeVector3D(-0.8f, 0.8f));
		cube->rotationDirection = randomRangeVector3D(-1.f, 1.f);
		cube->rotationSpeed = randomRangeFloat(1.f, 2.f);

		gameObjectsVector.push_back(cube);
	}

	GraphicsEngine::get()->releaseCompiledShader();

	LogUtils::log(this, "Geometry shader compilation");
	GraphicsEngine::get()->compileGeometryShader(L"GeometryShader.hlsl", "main", &shaderByteCode, &byteCodeSize);
	geometryShader = GraphicsEngine::createGeometryShader(shaderByteCode, byteCodeSize);
	GraphicsEngine::get()->releaseCompiledShader();

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

	const RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setGeometryShader(geometryShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	//LogUtils::log(this, "update and draw circles");
	for (GameObject* gameObject : gameObjectsVector)
	{
		if (pressedW)
			gameObject->update(static_cast<float>(EngineTime::getDeltaTime()));

		gameObject->draw(vertexShader, geometryShader, pixelShader, getClientWindowRect());
	}

	swapChain->present(true);
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
