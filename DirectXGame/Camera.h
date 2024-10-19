#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera(const std::string& name, const bool orthographic, const RECT windowRect, const float fov, const float zNear, const float zFar)
		: GameObject(name), orthographic(orthographic), windowRect(windowRect), fov(fov), zNear(zNear), zFar(zFar)
	{
		const float windowWidth = static_cast<float>(windowRect.right) - static_cast<float>(windowRect.left);
		const float windowHeight = static_cast<float>(windowRect.bottom) - static_cast<float>(windowRect.top);
		aspect = windowWidth / windowHeight;
	}

	void update(const float deltaTime) override;
	void draw(VertexShader* vertexShader, GeometryShader* geometryShader, PixelShader* pixelShader,
		RECT clientWindow) override;

	Matrix4x4 getView();

private:
	bool orthographic = false;

	RECT windowRect;
	float aspect;

	float fov = 90.f;
	float zNear = 0.1f;
	float zFar = 1000.f;


public:
	// temp
	Matrix4x4 view;
	float xRot;
	float yRot;
	float forward = 0.0f;
	float rightward = 0.0f;
	//float squidward = 0.0f;
};

