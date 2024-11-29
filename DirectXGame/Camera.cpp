#include "Camera.h"
namespace mrlol
{
	void Camera::update(const float deltaTime)
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

	void Camera::setProjectionType(bool isOrthographic)
	{
		orthographic = isOrthographic;
	}

	void Camera::setWidth(float width)
	{
		this->width = width;
	}

	void Camera::setHeight(float height)
	{
		this->height = height;
	}
}
