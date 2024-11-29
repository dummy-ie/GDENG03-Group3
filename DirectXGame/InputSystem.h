#pragma once
#include <unordered_set>
#include <Windows.h>
#include "InputListener.h"
#include "LogUtils.h"
#include "Vector2D.h"

namespace mrlol
{
	class InputSystem
	{
	public:
		static InputSystem* get();

		void update();
		void addListener(InputListener* listener);
		void removeListener(InputListener* listener);
		static void setCursorPosition(const Vector2D& pos);
		static void showCursor(const bool& show);
		void setEnabled(const bool& enabled);
		Vector2D getDeltaMousePosition();
		Vector2D getMousePosition();
		Vector2D getOldMousePosition();

		InputSystem(InputSystem const&) = delete;
		InputSystem& operator=(InputSystem const&) = delete;
		InputSystem(InputSystem&& other) noexcept = delete;
		InputSystem& operator=(InputSystem&& other) noexcept = delete;

	private:
		InputSystem();
		~InputSystem();
		static InputSystem* sharedInstance;

		std::unordered_set<InputListener*> setListeners;
		unsigned char keysState[256] = {};
		unsigned char oldKeysState[256] = {};

		Vector2D oldMousePosition;
		Vector2D deltaMousePosition;

		bool firstMouseMove = true;

		bool isEnabled = true;
	};
}