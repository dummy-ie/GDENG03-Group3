#pragma once

#include "Vector4D.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "GameObject.h"

namespace gdeng03
{
	class EditorAction
	{
	public:
		EditorAction(GameObject* gameObject);
		~EditorAction();

		std::string getOwnerName();
		Vector3D getStoredPosition();
		Vector3D getStoredScale();
		Vector4D getStoredOrientation();
		Matrix4x4 getStoredMatrix();

	private:
		std::string name;
		Vector3D localPosition;
		Vector3D localScale;
		Vector4D orientation;
		Matrix4x4 localMatrix;
	};
}
