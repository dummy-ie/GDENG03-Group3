#include "Window.h"

//Window* window = nullptr;

LRESULT CALLBACK windowProc(const HWND windowHandle, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		// Event fired when window is created
		// collected here...
		Window* window = static_cast<Window*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
		// ...and then stored for later lookup
		SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		window->setWindowHandle(windowHandle);
		window->onCreate();
		break;
	}
	case WM_SETFOCUS:
	{
		// Event fired when the window get focus
		Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));
		window->onFocus();
		break;
	}
	case WM_KILLFOCUS:
	{
		// Event fired when the window lost focus
		Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));
		window->onKillFocus();
		break;
	}
	case WM_DESTROY:
	{
		// Event fired when window is destroyed
		Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}
	default:
		return ::DefWindowProc(windowHandle, message, wParam, lParam);
	}

	return NULL;
}

bool Window::init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = nullptr;
	wc.lpszClassName = "MyWindowClass";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &windowProc;

	if (!::RegisterClassEx(&wc))
		return false;

	windowHandle = ::CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		"MyWindowClass",
		"[LEOCARIO] DirectX Application",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1024,
		768,
		nullptr,
		nullptr,
		nullptr,
		this);

	if (!windowHandle)
		return false;

	::ShowWindow(windowHandle, SW_SHOW);
	::UpdateWindow(windowHandle);

	EngineTime::initialize();

	windowIsRunning = true;

	return true;
}

bool Window::broadcast()
{
	MSG msg;

	EngineTime::logFrameStart();
	this->onUpdate();

	while (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);
	EngineTime::logFrameEnd();

	return true;
}

bool Window::release() const
{
	if (!::DestroyWindow(windowHandle))
		return false;

	return true;
}

bool Window::isRunning() const
{
	return windowIsRunning;
}

RECT Window::getClientWindowRect() const
{
	RECT rc;
	::GetClientRect(this->windowHandle, &rc);
	return rc;
}

void Window::setWindowHandle(HWND windowHandle)
{
	this->windowHandle = windowHandle;
}

void Window::onCreate()
{

}

void Window::onUpdate()
{

}

void Window::onDestroy()
{
	windowIsRunning = false;
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}
