#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	~Window();

	bool init();
	bool broadcast();
	bool release();
	bool isRun();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

protected:
	// ReSharper disable once IdentifierTypo
	HWND m_Hwnd;
	bool m_IsRun;
};

