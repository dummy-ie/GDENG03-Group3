#include "AppWindow.h"
#include <Windows.h>

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

AppWindow::AppWindow() = default;


AppWindow::~AppWindow() = default;

void AppWindow::initialize() {
	sharedInstance = new AppWindow();
	sharedInstance->onCreate();

}

void AppWindow::destroy() {
	if (sharedInstance != NULL) {
		sharedInstance->onDestroy();
		delete sharedInstance;
	}
}

void AppWindow::onCreate()
{
	bRunning = true;
	InputSystem::initialize();
	Window::init();

}


void AppWindow::initializeEngine() {
	GraphicsEngine::initialize();
	StateManager::initialize();
	EngineTime::initialize();
	BaseComponentSystem::initialize();
	UIManager::initialize(this->m_hwnd);
	SceneCameraHandler::initialize();
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
	RECT rc = this->getClientWindowRect();

	this->swapChain = GraphicsEngine::getInstance()->getSwapChain();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	this->swapChain->init(this->m_hwnd, width, height);

	// Initialize three distinct quads with different colors
	//m_quad = new Quad(0.0f, 0.0f, 0.0f); 
	//m_quad->init(GraphicsEngine::getInstance()->getD3DDevice());

	//m_circle = new Circle(0.5f, 0.5f, 0.0f);
	//m_circle->init(GraphicsEngine::getInstance()->getD3DDevice());

	//Initialize a cube:

	//m_camera = new Camera(L"MyCamera");

	//m_plane = new Plane("MyPlane", this->getClientWindowRect());


	for (int i = 0; i < 15; i++) {
		//Cube* m_cube = new Cube(0.0f, 3.5f, -1.f, "MyCube" + i, this->getClientWindowRect());
		//std::cout << "Cube has been created" << std::endl;
		//cube_list.push_back(m_cube);
	}


	//m_plane = new Plane("MyPlane", this->getClientWindowRect());
}


bool AppWindow::isRunning()
{
	return bRunning;
}


void AppWindow::onUpdate() {

	std::vector<Cube*> cube_list;
	cube_list = CubeManager::GetInstance().GetCubeList();

	Window::onUpdate();

	InputSystem::getInstance()->update();

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->swapChain, 0, 0.3f, 0.4f, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//m_plane->update(EngineTime::getDeltaTime(), this->getClientWindowRect());
	if (StateManager::getInstance()->getStateType() == StateManager::StateType::PLAY)
		BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();

	if (!cube_list.empty()) {
		for (Cube* cube : cube_list) {
			cube->update(EngineTime::getDeltaTime(), this->getClientWindowRect());
		}
	}

	if (m_plane != nullptr)
		m_plane->update(EngineTime::getDeltaTime(), this->getClientWindowRect());



	SceneCameraHandler::getInstance()->update(EngineTime::getDeltaTime(), this->getClientWindowRect());
	UIManager::get()->draw();

	this->swapChain->present(true);

}


void AppWindow::onDestroy() {

	// Stop rendering first
	bRunning = false; // If this flag controls the rendering loop
	Window::onDestroy();
	InputSystem::getInstance()->removeListener(this);
	InputSystem::getInstance()->destroy();

	if (m_plane)m_plane->release();

	// Release the swap chain and any other graphics resources
	GraphicsEngine::getInstance()->destroy(); // Ensure this cleans up the DeviceContext, SwapChain, etc.

}

void AppWindow::spawnCube(int nCubeAmount) {
	for (int i = 0; i < 1; i++) {
		std::stringstream ss;
		ss << "Cube_" << CubeManager::GetInstance().GetCubeList().size() + 1;
		std::string UID = ss.str();

		Cube* m_cube = new Cube(0.0f, 8.5f, 0.0f, UID, this->getClientWindowRect());
		//std::cout << "Cube has been created" << std::endl;
		CubeManager::GetInstance().AddCube(m_cube);
	}
}

void AppWindow::spawnCubeWithPhysics(int nCubeAmount)
{
	for (int i = 0; i < 1; i++) {
		std::stringstream ss;
		ss << "Cube_" << CubeManager::GetInstance().GetCubeList().size() + 1;
		std::string UID = ss.str();

		Cube* m_cube = new Cube(0.0f, 8.5f, 0.0f, UID, this->getClientWindowRect());
		//std::cout << "Cube with physics has been created" << std::endl;
		m_cube->attachRigidbody();
		CubeManager::GetInstance().AddCube(m_cube);
	}
}

void AppWindow::spawnPlane() {
	Cube* plane = new Cube(0.0f, -1, 0.0f, 100.0f, 0.1f, 100.0f, "Plane", this->getClientWindowRect());
	this->m_plane = plane;
	this->m_plane->attachRigidbody();

}


void AppWindow::onKeyDown(int key)
{
	if (key == 'W') {
		std::cout << "Key W pressed down! \n";
	}
}

void AppWindow::onKeyUp(int key)
{
	if (key == 'W') {
		std::cout << "Key W pressed up! \n";
	}
}

void AppWindow::onMouseMove(const Point mouse_pos)
{
}

void AppWindow::onLeftMouseDown(const Point mouse_pos)
{
	std::cout << "Left mouse pressed down! \n";
}

void AppWindow::onLeftMouseUp(const Point mouse_pos)
{
	std::cout << "Left mouse pressed up! \n";
}

void AppWindow::onRightMouseDown(const Point mouse_pos)
{
	std::cout << "Right mouse pressed down! \n";
	this->shouldRotate = true;
}

void AppWindow::onRightMouseUp(const Point mouse_pos)
{
	std::cout << "Right mouse pressed up! \n";
	this->shouldRotate = false;
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onDefocus()
{
	InputSystem::getInstance()->removeListener(this);
}


