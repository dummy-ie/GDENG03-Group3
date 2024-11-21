#include "Window.h"

#include "LogUtils.h"
#include "imgui.h"

// ReSharper disable once CppInconsistentNaming
// for ImGui input forwarding
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowProc(const HWND windowHandle, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(windowHandle, message, wParam, lParam))
		return true;

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
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &windowProc;
	
	LogUtils::logBool(this, static_cast<bool>(::RegisterClassEx(&wc)));

	windowHandle = ::CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		L"MyWindowClass",
		L"MRLOL.engine",
		WS_THICKFRAME | WS_MAXIMIZE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GetSystemMetrics(SM_CXFULLSCREEN),
		GetSystemMetrics(SM_CYFULLSCREEN),
		nullptr,
		nullptr,
		nullptr,
		nullptr);

	LogUtils::logBool(this, static_cast<bool>(windowHandle));

	::ShowWindow(windowHandle, SW_SHOW);
	::UpdateWindow(windowHandle);

	EngineTime::initialize();

	windowIsRunning = true;
}

Window::~Window()
{
	LogUtils::logBool(this, static_cast<bool>(::DestroyWindow(windowHandle)));
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

int Window::getWindowWidth() const
{
	return getClientWindowRect().right - getClientWindowRect().left;
}

int Window::getWindowHeight() const
{
	return getClientWindowRect().bottom - getClientWindowRect().top;
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
