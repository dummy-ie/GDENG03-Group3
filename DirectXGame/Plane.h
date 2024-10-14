#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vectors.h"
#include "Vertex.h"
#include "Constant.h"
#include "GameObject.h"

class Plane : public GameObject
{
public:

	Plane(const std::string& name, void* shaderByteCode, size_t sizeShader);
	~Plane() override;

	void update(float deltaTime) override;
	void draw(VertexShader* vertexShader, GeometryShader* geometryShader, PixelShader* pixelShader, RECT clientWindow) override;

	Vector3D rotationDirection = 0.f;
	float rotationSpeed = 1.0f;
};
