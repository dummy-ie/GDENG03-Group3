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
    Window::init();

}



void AppWindow::initializeEngine() {
    GraphicsEngine::initialize();
    EngineTime::initialize();
    GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
    RECT rc = this->getClientWindowRect();

    this->swapChain = GraphicsEngine::getInstance()->getSwapChain();
    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;

    this->swapChain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

    // Initialize three distinct quads with different colors
    //m_quad = new Quad(0.0f, 0.0f, 0.0f); 
    //m_quad->init(GraphicsEngine::getInstance()->getD3DDevice());

    //m_circle = new Circle(0.5f, 0.5f, 0.0f);
    //m_circle->init(GraphicsEngine::getInstance()->getD3DDevice());

    //Initialize a cube:
    m_cube = new Cube(L"MyCube");

}


bool AppWindow::isRunning()
{
    return bRunning;
}


void AppWindow::onUpdate() {
    Window::onUpdate();
    GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->swapChain, 0, 0.3f, 0.4f, 1);

    RECT rc = this->getClientWindowRect();
    GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

    this->m_cube->update(EngineTime::getDeltaTime(), this->getClientWindowRect());

    //this->m_quad->render(EngineTime::getDeltaTime());
    //this->m_circle->render(EngineTime::getDeltaTime());

    handleUserInput();

    this->swapChain->present(true);

}

void AppWindow::handleUserInput() {

    static bool spacePressed = false;
    static bool backspacePressed = false;
    static bool deletePressed = false;
    static bool escapePressed = false;
    // Handle SPACE key release
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) == 0 && spacePressed) {
        // SPACE key released
     
        spacePressed = false; // Reset the flag
    }
    else if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        spacePressed = true; // Key is being pressed
    }

    // Handle BACKSPACE key release
    if ((GetAsyncKeyState(VK_BACK) & 0x8000) == 0 && backspacePressed) {
        // BACKSPACE key released
       
        backspacePressed = false; // Reset the flag
    }
    else if (GetAsyncKeyState(VK_BACK) & 0x8000) {
        backspacePressed = true; // Key is being pressed
    }

    // Handle DELETE key release
    if ((GetAsyncKeyState(VK_DELETE) & 0x8000) == 0 && deletePressed) {
        // DELETE key released

        deletePressed = false; // Reset the flag
    }
    else if (GetAsyncKeyState(VK_DELETE) & 0x8000) {
        deletePressed = true; // Key is being pressed
    }

    // Handle SPACE key release
    if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) == 0 && escapePressed) {

        this->release();
        escapePressed = false; // Reset the flag
    }
    else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        escapePressed = true; // Key is being pressed
    }
}

void AppWindow::onDestroy() {
    // Stop rendering first
    bRunning = false; // If this flag controls the rendering loop

    // Release resources in reverse order of creation
    //if (!m_circle_list.empty()) this->m_circle_list.clear();
    
    if (m_cube) m_cube->release();

    // Release the swap chain and any other graphics resources
    GraphicsEngine::getInstance()->destroy(); // Ensure this cleans up the DeviceContext, SwapChain, etc.

    // Optionally set pointers to null after release
    m_cube = nullptr;

}


