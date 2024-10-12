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

    //this->m_quad->render(EngineTime::getDeltaTime());
    //this->m_circle->render(EngineTime::getDeltaTime());

    static bool spacePressed = false;
    static bool backspacePressed = false;
    static bool deletePressed = false;
    static bool escapePressed = false;

    // Handle SPACE key release
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) == 0 && spacePressed) {
        // SPACE key released
        Circle* circle = new Circle(0.85f, 0.85f, 0.0f);
        circle->init(GraphicsEngine::getInstance()->getD3DDevice());
        this->m_circle_list.push_back(circle);
        spacePressed = false; // Reset the flag
    }
    else if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        spacePressed = true; // Key is being pressed
    }

    // Handle BACKSPACE key release
    if ((GetAsyncKeyState(VK_BACK) & 0x8000) == 0 && backspacePressed) {
        // BACKSPACE key released
        if (!m_circle_list.empty())
            m_circle_list.pop_back();
        backspacePressed = false; // Reset the flag
    }
    else if (GetAsyncKeyState(VK_BACK) & 0x8000) {
        backspacePressed = true; // Key is being pressed
    }

    // Handle DELETE key release
    if ((GetAsyncKeyState(VK_DELETE) & 0x8000) == 0 && deletePressed) {
        // DELETE key released
        if (!m_circle_list.empty())
            m_circle_list.clear();
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

    // Render dynamic circles
    if (!m_circle_list.empty()) {
        for (Circle* circle : this->m_circle_list) {
            circle->updateMovement(EngineTime::getDeltaTime(),rc); // Use fixed boundaries inside circle
            circle->render(EngineTime::getDeltaTime());
        }
    }

    this->swapChain->present(true);
}

void AppWindow::onDestroy() {
    // Stop rendering first
    bRunning = false; // If this flag controls the rendering loop

    // Release resources in reverse order of creation
    if (!m_circle_list.empty()) this->m_circle_list.clear();
    //if (m_quad2) m_quad2->release();
    if (m_quad3) m_quad3->release();

    // Release the swap chain and any other graphics resources
    GraphicsEngine::getInstance()->destroy(); // Ensure this cleans up the DeviceContext, SwapChain, etc.

    // Optionally set pointers to null after release

    m_quad2 = nullptr;
    m_quad3 = nullptr;
}


