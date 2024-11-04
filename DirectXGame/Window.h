#pragma once
#include <Windows.h>
#include "EngineTime.h"

class Window
{
public:
	Window();
	virtual ~Window();
	Window(const Window& obj) = default;
	Window(Window&& other) noexcept = default;
	Window& operator=(const Window& other) = default;
	Window& operator=(Window&& other) noexcept = default;

	bool isRunning();
	bool isFocused() const;

	RECT getClientWindowRect() const;

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

protected:
	HWND windowHandle;
	bool windowIsInitialized = false;
	bool windowIsFocused;
	bool windowIsRunning;

	bool broadcast();
};

