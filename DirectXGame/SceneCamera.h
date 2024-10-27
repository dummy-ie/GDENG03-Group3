#pragma once
#include "Camera.h"
#include "InputListener.h"

class SceneCamera :
	public Camera, public InputListener
{
public:
	SceneCamera(const std::string& name, bool orthographic, const RECT& windowRect);

	void onKeyDown(int key) override;
	void onKeyUp(int key) override;
	void onMouseMove(const Vector2D& mousePosition) override;
	void onLeftMouseDown(const Vector2D& mousePosition) override;
	void onLeftMouseUp(const Vector2D& mousePosition) override;
	void onRightMouseDown(const Vector2D& mousePosition) override;
	void onRightMouseUp(const Vector2D& mousePosition) override;

private:
	float movementSpeed = 5.f;
};

