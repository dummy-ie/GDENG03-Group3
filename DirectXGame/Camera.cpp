#include "Camera.h"

#include <corecrt_math_defines.h>

void Camera::update(const float deltaTime)
{
}

void Camera::draw(VertexShader* vertexShader, GeometryShader* geometryShader, PixelShader* pixelShader,
	RECT clientWindow)
{
}

Matrix4x4 Camera::getView()
{
	Matrix4x4
		tempView,
		translationMatrix,
		xMatrix,
		yMatrix,
		zMatrix;

	zMatrix.setRotationZ(localRotation.z);
	yMatrix.setRotationY(localRotation.y);
	xMatrix.setRotationX(localRotation.x);

	tempView.setIdentity();
	tempView *= xMatrix * yMatrix * zMatrix;

	Vector3D newPos = view.getTranslation() + tempView.getZDirection() * (forward * 0.1f);

	newPos += tempView.getXDirection() * (rightward * 0.1f);

	translationMatrix.setTranslation(newPos);

	tempView *= translationMatrix;

	view = tempView;

	tempView.inverse();

	return tempView;
}
