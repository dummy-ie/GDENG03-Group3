#include "Camera.h"

void Camera::update(const float deltaTime)
{
}

void Camera::draw(
	const VertexShaderPtr& vertexShader,
	const GeometryShaderPtr& geometryShader,
	const PixelShaderPtr& pixelShader,
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
	translationMatrix.setTranslation(localPosition);

	tempView.setIdentity();
	tempView = xMatrix * yMatrix * zMatrix * translationMatrix;
	//tempView *= translationMatrix;

	// Vector3D newPos = view.getTranslation() + tempView.getZDirection() * (forward * 0.1f);
	//
	// newPos += tempView.getXDirection() * (rightward * 0.1f);




	tempView.inverse();
	view = tempView;

	return view;
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
			nearPlane,
			farPlane);
	}
	else
	{
		proj.setPerspectiveProjection(fov, aspect, zNear, zFar);
	}

	return proj;
}
