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

Matrix4x4 Camera::getProjection() const
{
	Matrix4x4 proj;
	const float windowWidth = static_cast<float>(windowRect.right - windowRect.left);
	const float windowHeight = static_cast<float>(windowRect.bottom - windowRect.top);

	if (orthographic)
	{
		// constants.proj.setOrthographicProjection(
		// 	windowWidth / 400.f,
		// 	windowHeight / 400.f,
		// 	-4.0f,
		// 	4.0f);
		proj.setOrthographicProjection(
			windowWidth / 200.f,
			windowHeight / 200.f,
			zNear,
			zFar);
	}
	else
	{
		proj.setPerspectiveProjection(fov, aspect, zNear, zFar);
	}

	return proj;
}
