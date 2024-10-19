#pragma once

#include "GameObject.h"
#include "CameraManager.h"

class Cube : public GameObject
{
public:

	Cube(const std::string& name, void* shaderByteCode, size_t sizeShader);
	~Cube() override;

	void update(float deltaTime) override;
	void draw(VertexShader* vertexShader, GeometryShader* geometryShader, PixelShader* pixelShader, RECT clientWindow) override;

	Vector3D rotationDirection = 0.f;
	float rotationSpeed = 1.0f;

private:
	float deltaPos = 0.0f;
	float deltaScale = 0.0f;

};
