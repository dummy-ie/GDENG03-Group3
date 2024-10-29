#pragma once
#include <unordered_set>
#include <Windows.h>
#include "InputListener.h"
#include "LogUtils.h"
#include "Vector2D.h"

class InputSystem
{
public:
	InputSystem();
	~InputSystem();
	InputSystem(const InputSystem& obj) = default;
	InputSystem(InputSystem&& other) noexcept = default;
	InputSystem& operator=(const InputSystem& other) = default;
	InputSystem& operator=(InputSystem&& other) noexcept = default;

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
	static void setCursorPosition(const Vector2D& pos);
	static void showCursor(const bool& show);
	void setEnabled(const bool& enabled);

public:
	static InputSystem* get();

private:
	std::unordered_set<InputListener*> setListeners;
	unsigned char keysState[256] = {};
	unsigned char oldKeysState[256] = {};
	Vector2D oldMousePosition;
	bool firstMouseMove = true;

	bool isEnabled;
};