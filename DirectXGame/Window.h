#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>
#include "EngineTime.h"

namespace mrlol
{
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
		int getWindowWidth() const;
		int getWindowHeight() const;

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
}

