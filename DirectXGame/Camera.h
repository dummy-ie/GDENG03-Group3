#pragma once
#include "GameObject.h"

namespace gdeng03
{
	class Camera : public GameObject
	{
	public:
		Camera(const std::string& name, const bool orthographic, const RECT windowRect)
			: GameObject(name), orthographic(orthographic), windowRect(windowRect)
		{
			const float windowWidth = static_cast<float>(windowRect.right) - static_cast<float>(windowRect.left);
			const float windowHeight = static_cast<float>(windowRect.bottom) - static_cast<float>(windowRect.top);
			height = windowHeight;
			width = windowWidth;
			aspect = windowWidth / windowHeight;
		}

		void update(const float deltaTime) override;

		Matrix4x4 getView();
		Matrix4x4 getProjection() const;
		void setProjectionType(bool isOrthographic);

		void setWidth(float width);
		void setHeight(float height);

	protected:
		bool orthographic = false;

		RECT windowRect;
		int width;
		int height;


		// perspective
		float aspect;
		float fov = 30.f;
		float zNear = 0.00001f;
		float zFar = 100.f;

		// orthographic
		float nearPlane = -10.f;
		float farPlane = 100.f;

		Matrix4x4 view;
	public:
		// temp
		// float xRot;
		// float yRot;
		// float forward = 0.0f;
		// float rightward = 0.0f;
		// float upward = 0.0f;
		//float squidward = 0.0f;
	};
}

