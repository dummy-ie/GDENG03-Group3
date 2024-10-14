#pragma once
#include <Windows.h>
#include "EngineTime.h"

class Window
{
public:
	virtual ~Window() = default;
	Window() = default;

	bool init();
	bool broadcast();
	bool release() const;
	bool isRunning() const;

	RECT getClientWindowRect() const;
	void setWindowHandle(HWND windowHandle);

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

protected:
	HWND windowHandle;
	bool windowIsRunning;
};

