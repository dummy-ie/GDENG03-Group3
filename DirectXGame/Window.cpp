#include "Window.h"

#include "LogUtils.h"

//Window* window = nullptr;

LRESULT CALLBACK windowProc(const HWND windowHandle, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		break;
	}
	case WM_SETFOCUS:
	{
		// Event fired when the window get focus
		Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));
		if (window)
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

Window::Window()
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

	LogUtils::log(this, ::RegisterClassEx(&wc));

	windowHandle = ::CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		"MyWindowClass",
		"[LEOCARIO] DirectX Application",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GetSystemMetrics(SM_CXFULLSCREEN),
		GetSystemMetrics(SM_CYFULLSCREEN),
		nullptr,
		nullptr,
		nullptr,
		nullptr);

	LogUtils::log(this, static_cast<bool>(windowHandle));

	::ShowWindow(windowHandle, SW_SHOW);
	::UpdateWindow(windowHandle);

	EngineTime::initialize();

	windowIsRunning = true;
}

Window::~Window()
{
	LogUtils::log(this, ::DestroyWindow(windowHandle));
}

bool Window::broadcast()
{
	MSG msg;

	if (!windowIsInitialized)
	{
		SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
		onCreate();
		windowIsInitialized = true;
	}

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

bool Window::isRunning()
{
	if (windowIsRunning)
		broadcast();

	return windowIsRunning;
}

bool Window::isFocused() const
{
	return windowIsFocused;
}

RECT Window::getClientWindowRect() const
{
	RECT rc;
	::GetClientRect(this->windowHandle, &rc);
	return rc;
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
	windowIsFocused = true;
}

void Window::onKillFocus()
{
	windowIsFocused = false;
}
