#include "InputSystem.h"

InputSystem::InputSystem()
= default;


InputSystem::~InputSystem()
= default;

void InputSystem::update()
{
	POINT currentMousePoint;
	::GetCursorPos(&currentMousePoint);
	Vector2D currentMousePosition = currentMousePoint;

	if (firstMouseMove)
	{
		oldMousePosition = currentMousePosition;
		firstMouseMove = false;
	}

	if (currentMousePosition != oldMousePosition)
	{
		std::unordered_set<InputListener*>::iterator it = setListeners.begin();

		while (it != setListeners.end())
		{
			(*it)->onMouseMove(currentMousePosition);
			++it;
		}
	}
	oldMousePosition = currentMousePosition;

	if (::GetKeyboardState(keysState))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			// KEY IS DOWN
			if (keysState[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = setListeners.begin();

				while (it != setListeners.end())
				{
					if (i == VK_LBUTTON)
					{
						if (keysState[i] != oldKeysState[i])
							(*it)->onLeftMouseDown(Vector2D(currentMousePosition.x, currentMousePosition.y));
					}
					else if (i == VK_RBUTTON)
					{
						if (keysState[i] != oldKeysState[i])
							(*it)->onRightMouseDown(Vector2D(currentMousePosition.x, currentMousePosition.y));
					}
					else
						(*it)->onKeyDown(i);

					++it;
				}
			}
			else // KEY IS UP
			{
				if (keysState[i] != oldKeysState[i])
				{
					std::unordered_set<InputListener*>::iterator it = setListeners.begin();

					while (it != setListeners.end())
					{
						if (i == VK_LBUTTON)
							(*it)->onLeftMouseUp(Vector2D(currentMousePosition.x, currentMousePosition.y));
						else if (i == VK_RBUTTON)
							(*it)->onRightMouseUp(Vector2D(currentMousePosition.x, currentMousePosition.y));
						else
							(*it)->onKeyUp(i);

						++it;
					}
				}

			}

		}
		// store current keys state to old keys state buffer
		::memcpy(oldKeysState, keysState, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	setListeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	setListeners.erase(listener);
}

void InputSystem::setCursorPosition(const Vector2D& pos)
{
	::SetCursorPos(static_cast<int>(pos.x), static_cast<int>(pos.y));
}

void InputSystem::showCursor(const bool& show)
{
	::ShowCursor(show);
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}