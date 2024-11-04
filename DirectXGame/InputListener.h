#pragma once
#include "Vector2D.h"

class InputListener
{
public:
	InputListener()
	= default;

	virtual ~InputListener()
	= default;

	//KEYBOARD pure virtual callback functions 
	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;

	virtual void onMouseMove(const Vector2D& mousePosition) = 0;

	virtual void onLeftMouseDown(const Vector2D& mousePosition) = 0;
	virtual void onLeftMouseUp(const Vector2D& mousePosition) = 0;

	virtual void onRightMouseDown(const Vector2D& mousePosition) = 0;
	virtual void onRightMouseUp(const Vector2D& mousePosition) = 0;

};
