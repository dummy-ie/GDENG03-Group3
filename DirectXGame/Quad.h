#pragma once
#define _USE_MATH_DEFINES // Before including <cmath>
#include <cmath>
#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vectors.h"
#include "Vertex.h"
#include "Constant.h"
#include "GameObject.h"

class Quad : public GameObject
{
public:
	Quad(const std::string& name, void* shaderByteCode, size_t sizeShader);
	~Quad() override;

	// release everything in destructor instead
	//void release() const override;

	void update(float deltaTime) override;
	void draw(VertexShader* vertexShader, GeometryShader* geometryShader, PixelShader* pixelShader, RECT clientWindow) override;

	Vector3D originalPosition = 0.f;
	Vector3D moveDirection = 0.f;
	float movementSpeed = 1.f;
	float acceleration = 0.2f;
	float delta = 0.f;
};
