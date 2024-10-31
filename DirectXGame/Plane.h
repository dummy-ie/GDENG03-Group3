#pragma once

#include "GameObject.h"
#include "CameraManager.h"

class Plane final : public GameObject
{
public:

	Plane(const std::string& name, const void* shaderByteCode, size_t sizeShader, const Vector3D& color = Vector3D::zero);

	void update(float deltaTime) override;
	//void draw(VertexShaderPtr vertexShader, GeometryShaderPtr geometryShader, PixelShaderPtr pixelShader, RECT clientWindow) override;

	Vector3D rotationDirection = 0.f;
	float rotationSpeed = 1.0f;
};
