#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera(const std::string& name, const bool orthographic, const RECT windowRect)
		: GameObject(name), orthographic(orthographic), windowRect(windowRect)
	{
		const float windowWidth = static_cast<float>(windowRect.right) - static_cast<float>(windowRect.left);
		const float windowHeight = static_cast<float>(windowRect.bottom) - static_cast<float>(windowRect.top);
		aspect = windowWidth / windowHeight;
	}

	// probably going to be empty or can render the gizmos through here
	void update(const float deltaTime) override;
	void draw(const VertexShaderPtr& vertexShader, const GeometryShaderPtr& geometryShader, const PixelShaderPtr& pixelShader,
		RECT clientWindow) override;

	Matrix4x4 getView();
	Matrix4x4 getProjection() const;

protected:
	bool orthographic = false;

	RECT windowRect;

	// perspective
	float aspect;
	float fov = 90.f;
	float zNear = 0.1f;
	float zFar = 1000.f;

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

