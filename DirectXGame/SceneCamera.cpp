#include "SceneCamera.h"

#include "EngineTime.h"
#include "InputSystem.h"

namespace mrlol
{
	SceneCamera::SceneCamera(const std::string& name, bool orthographic, const RECT& windowRect) : Camera(name, orthographic, windowRect)
	{
		InputSystem::get()->addListener(this);
	}

	void SceneCamera::setPossessed(bool possessed)
	{
		isPossessed = possessed;
	}

	void SceneCamera::update(const float deltaTime)
	{
		Camera::update(deltaTime);

		//InputSystem::showCursor(!isPossessed);
	}

	void SceneCamera::onKeyDown(const int key)
	{
		if (!isPossessed)
			return;

		Matrix4x4 temp = view;
		temp.inverse();

		switch (key)
		{
		case 'W':
		{
			localPosition += temp.getZDirection() * (movementSpeed * EngineTime::getDeltaTime());
			break;
		}
		case 'S':
		{
			localPosition -= temp.getZDirection() * (movementSpeed * EngineTime::getDeltaTime());
			break;
		}
		case 'A':
		{
			localPosition -= temp.getXDirection() * (movementSpeed * EngineTime::getDeltaTime());
			break;
		}
		case 'D':
		{
			localPosition += temp.getXDirection() * (movementSpeed * EngineTime::getDeltaTime());
			break;
		}
		case 'Q':
		{
			localPosition -= temp.getYDirection() * (movementSpeed * EngineTime::getDeltaTime());
			break;
		}
		case 'E':
		{
			localPosition += temp.getYDirection() * (movementSpeed * EngineTime::getDeltaTime());
			break;
		}
		default:
			break;
		}
	}

	void SceneCamera::onKeyUp(int key)
	{
	}

	void SceneCamera::onMouseMove(const Vector2D& mousePosition)
	{
		if (!isPossessed)
			return;

		const float width = static_cast<float>(windowRect.right - windowRect.left);
		const float height = static_cast<float>(windowRect.bottom - windowRect.top);

		localRotation.x += (mousePosition.y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
		localRotation.y += (mousePosition.x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;

		InputSystem::setCursorPosition(Vector2D(width / 2.0f, height / 2.0f));
	}

	void SceneCamera::onLeftMouseDown(const Vector2D& mousePosition)
	{
	}

	void SceneCamera::onLeftMouseUp(const Vector2D& mousePosition)
	{
	}

	void SceneCamera::onRightMouseDown(const Vector2D& mousePosition)
	{
		isPossessed = true;
		InputSystem::showCursor(false);
	}

	void SceneCamera::onRightMouseUp(const Vector2D& mousePosition)
	{
		isPossessed = false;
		InputSystem::showCursor(true);
		//InputSystem::get()->showCursor(true);
	}
}
