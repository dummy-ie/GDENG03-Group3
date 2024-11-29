#include "InputSystem.h"

#include "imgui.h"

namespace mrlol
{
	InputSystem* InputSystem::sharedInstance = nullptr;

	InputSystem::InputSystem()
		= default;


	InputSystem::~InputSystem()
	{
		delete sharedInstance;
	}

	void InputSystem::update()
	{
		if (!isEnabled)
			return;

		POINT currentMousePoint;
		::GetCursorPos(&currentMousePoint);
		//LogUtils::log(this, "Getting cursor pos");
		const Vector2D currentMousePosition = currentMousePoint;
		const ImGuiIO& io = ImGui::GetIO();

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
			//LogUtils::log(this, "Getting keyboard state");
			for (unsigned int i = 0; i < 256; i++)
			{
				// KEY IS DOWN
				if (keysState[i] & 0x80)
				{
					//LogUtils::log(this, "key is down");
					std::unordered_set<InputListener*>::iterator it = setListeners.begin();

					while (it != setListeners.end())
					{
						if (i == VK_LBUTTON && !io.WantCaptureMouse)
						{
							if (keysState[i] != oldKeysState[i])
								(*it)->onLeftMouseDown(Vector2D(currentMousePosition.x, currentMousePosition.y));
						}
						else if (i == VK_RBUTTON && !io.WantCaptureMouse)
						{
							if (keysState[i] != oldKeysState[i])
								(*it)->onRightMouseDown(Vector2D(currentMousePosition.x, currentMousePosition.y));
						}
						else if (!io.WantCaptureKeyboard)
							(*it)->onKeyDown(i);

						++it;
					}
				}
				else // KEY IS UP
				{
					if (keysState[i] != oldKeysState[i])
					{
						//LogUtils::log(this, "key is up");
						std::unordered_set<InputListener*>::iterator it = setListeners.begin();

						while (it != setListeners.end())
						{
							if (i == VK_LBUTTON && !io.WantCaptureMouse)
								(*it)->onLeftMouseUp(Vector2D(currentMousePosition.x, currentMousePosition.y));
							else if (i == VK_RBUTTON && !io.WantCaptureMouse)
								(*it)->onRightMouseUp(Vector2D(currentMousePosition.x, currentMousePosition.y));
							else if (!io.WantCaptureKeyboard)
								(*it)->onKeyUp(i);

							++it;
						}
					}

				}

			}

			//LogUtils::log(this, "Copying key state");
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

	void InputSystem::setEnabled(const bool& enabled)
	{
		isEnabled = enabled;
	}

	InputSystem* InputSystem::get()
	{
		if (!sharedInstance)
			sharedInstance = new InputSystem();

		return sharedInstance;
	}
}
