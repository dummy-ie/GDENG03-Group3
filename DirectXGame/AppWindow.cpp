#include "AppWindow.h"
#include <Windows.h>

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::getInstance()
{
    return sharedInstance;
}

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

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
    EngineTime::initialize();
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

    //m_plane = new Plane(L"MyPlane", this->getClientWindowRect());


    //for (int i = 0; i < 1; i++) {
        //Cube* m_cube = new Cube(L"MyCube" + to_wstring(i), this->getClientWindowRect());
        //std::cout << "Cube has been created" << std::endl;
        //cube_list.push_back(m_cube);
    //}
    
    
    Cube* cube2 = new Cube(-1.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.5f, 2.5f, 2.5f, L"Cube2", this->getClientWindowRect());
    Cube* cube3 = new Cube(-1.5f, 1.0f, -2.75f, -1.0f, 0.0f, 0.0f, 2.5f, 2.5f, 2.5f, L"Cube3", this->getClientWindowRect());
    Cube* cube4 = new Cube(-6.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.5f, 2.5f, 2.5f, L"Cube4", this->getClientWindowRect());
    Cube* cube5 = new Cube(-6.5f, 1.0f, -2.75f, -1.0f, 0.0f, 0.0f, 2.5f, 2.5f, 2.5f, L"Cube5", this->getClientWindowRect());
    Cube* cube6 = new Cube(-11.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.5f, 2.5f, 2.5f, L"Cube6", this->getClientWindowRect());
    Cube* cube7 = new Cube(-11.5f, 1.0f, -2.75f, -1.0f, 0.0f, 0.0f, 2.5f, 2.5f, 2.5f, L"Cube7", this->getClientWindowRect());
    Cube* cube8 = new Cube(-1.5f, 3.2f, -1.90f, 0.0f, 0.0f, 0.0f, 4.55f, 4.55f, 1.55f, L"Cube8", this->getClientWindowRect());
    Cube* cube9 = new Cube(-10.5f, 3.2f, -1.90f, 0.0f, 0.0f, 0.0f, 4.55f, 4.55f, 1.55f, L"Cube9", this->getClientWindowRect());
    Cube* cube10 = new Cube(-3.5f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.5f, 2.5f, 2.5f, L"Cube10", this->getClientWindowRect());
    Cube* cube11 = new Cube(-3.5f, 5.0f, -2.75f, -1.0f, 0.0f, 0.0f, 2.5f, 2.5f, 2.5f, L"Cube11", this->getClientWindowRect());
    Cube* cube12 = new Cube(-8.5f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.5f, 2.5f, 2.5f, L"Cube12", this->getClientWindowRect());
    Cube* cube13 = new Cube(-8.5f, 5.0f, -2.75f, -1.0f, 0.0f, 0.0f, 2.5f, 2.5f, 2.5f, L"Cube13", this->getClientWindowRect());
    Cube* cube14 = new Cube(-6.0f, 7.2f, -1.90f, 0.0f, 0.0f, 0.0f, 4.55f, 4.55f, 1.55f, L"Cube14", this->getClientWindowRect());
    Cube* cube15 = new Cube(-6.5f, 9.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.5f, 2.5f, 2.5f, L"Cube15", this->getClientWindowRect());
    Cube* cube = new Cube(-6.5f, 9.0f, -2.75f, -1.0f, 0.0f, 0.0f, 2.5f, 2.5f, 2.5f, L"Cube", this->getClientWindowRect());
    cube_list.push_back(cube);
    cube_list.push_back(cube15);
    cube_list.push_back(cube14);
    cube_list.push_back(cube13);
    cube_list.push_back(cube12);
    cube_list.push_back(cube11);
    cube_list.push_back(cube10);
    cube_list.push_back(cube9);
    cube_list.push_back(cube8);
    cube_list.push_back(cube7);
    cube_list.push_back(cube6);
    cube_list.push_back(cube5);
    cube_list.push_back(cube4);
    cube_list.push_back(cube3);
    cube_list.push_back(cube3);
    cube_list.push_back(cube2);
    //cube_list.push_back(cube);

    //m_plane = new Plane(L"MyPlane", this->getClientWindowRect());
}


bool AppWindow::isRunning()
{
    return bRunning;
}


void AppWindow::onUpdate() {
    Window::onUpdate();

    InputSystem::getInstance()->update();

    GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->swapChain, 0, 0.3f, 0.4f, 1);

    RECT rc = this->getClientWindowRect();
    GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

    //m_plane->update(EngineTime::getDeltaTime(), this->getClientWindowRect());

    if (!cube_list.empty()) {
        for (Cube* cube : cube_list) {
            cube->update(EngineTime::getDeltaTime(), this->getClientWindowRect());
        }
    }

    SceneCameraHandler::getInstance()->update(EngineTime::getDeltaTime(), this->getClientWindowRect());

    this->swapChain->present(true);

}


void AppWindow::onDestroy() {
    // Stop rendering first
    bRunning = false; // If this flag controls the rendering loop
    Window::onDestroy();
    InputSystem::getInstance()->removeListener(this);
    InputSystem::getInstance()->destroy();

    // Release resources in reverse order of creation
    if (!cube_list.empty()) this->cube_list.clear();

    if (m_plane)m_plane->release();
   
    // Release the swap chain and any other graphics resources
    GraphicsEngine::getInstance()->destroy(); // Ensure this cleans up the DeviceContext, SwapChain, etc.

}

void AppWindow::onKeyDown(int key)
{
    if (key == 'W') {
        std::cout << "Key W pressed down! \n";
    }
}

void AppWindow::onKeyUp(int key)
{
    if (key == 'W'){
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


