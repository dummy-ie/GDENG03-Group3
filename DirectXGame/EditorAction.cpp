#include "EditorAction.h"

namespace gdeng03
{
	EditorAction::EditorAction(GameObject* gameObject)
	{
		name = gameObject->getUniqueName();
		localPosition = gameObject->getLocalPosition();
		localScale = gameObject->getLocalScale();
		orientation = gameObject->getOrientation();
		localMatrix.setMatrix(gameObject->getLocalMatrix());
		//LogUtils::log(gameObject->getUniqueName() + "saved scale: " + getStoredScale().toString());
	}

	EditorAction::~EditorAction()
	= default;

	std::string EditorAction::getOwnerName()
	{
		return name;
	}

	Vector3D EditorAction::getStoredPosition()
	{
		return localPosition;
	}

	Vector3D EditorAction::getStoredScale()
	{
		return localScale;
	}

	Vector4D EditorAction::getStoredOrientation()
	{
		return orientation;
	}

	Matrix4x4 EditorAction::getStoredMatrix()
	{
		return localMatrix;
	}
}