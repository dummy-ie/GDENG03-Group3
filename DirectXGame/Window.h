#pragma once
#include <Windows.h>

class Window
{
public:
	virtual ~Window() = default;
	Window() = default;

	bool init();
	bool broadcast();
	bool release();
	bool isRunning();

	RECT getClientWindowRect();
	void setHwnd(HWND hwnd);

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

protected:
	// ReSharper disable once IdentifierTypo
	HWND m_Hwnd;
	bool m_IsRunning;
};

