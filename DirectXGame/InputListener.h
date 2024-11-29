#pragma once
#include "Vector2D.h"

namespace mrlol
{
	class InputListener
	{
	public:
		InputListener()
			= default;

		virtual ~InputListener()
			= default;

		//KEYBOARD pure virtual callback functions 
		virtual void onKeyDown(int key) {};
		virtual void onKeyUp(int key) {};

		virtual void onMouseMove(const Vector2D& mousePosition) {};

		virtual void onLeftMouseDown(const Vector2D& mousePosition) {};
		virtual void onLeftMouseUp(const Vector2D& mousePosition) {};

		virtual void onRightMouseDown(const Vector2D& mousePosition) {};
		virtual void onRightMouseUp(const Vector2D& mousePosition) {};

	};
}
