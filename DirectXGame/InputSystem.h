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

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

public:
	static InputSystem* get();

private:
	std::unordered_set<InputListener*> setListeners;
	unsigned char keysState[256] = {};
	unsigned char oldKeysState[256] = {};
	Vector2D oldMousePosition;
	bool firstMouseMove = true;
};