#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GameObject.h"

#include "MathUtil.h"


class Quad : public GameObject
{
public:
	Quad(const std::string& name, const void* shaderByteCode, size_t sizeShader);

	void update(float deltaTime) override;
	void draw(const VertexShaderPtr& vertexShader, const GeometryShaderPtr& geometryShader, const Material& material, RECT clientWindow) override;

	Vector3D originalPosition = 0.f;
	Vector3D moveDirection = 0.f;
	float movementSpeed = 1.f;
	float acceleration = 0.2f;
	float delta = 0.f;
};
