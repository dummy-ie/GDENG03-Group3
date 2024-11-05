#pragma once

#include "GameObject.h"
#include "CameraManager.h"

class Cylinder : public GameObject
{

	public:

	Cylinder(const std::string& name, void* shaderByteCode, size_t sizeShader, const Vector3D& color = Vector3D::zero);

	void update(float deltaTime) override;
	//void draw(const VertexShaderPtr& vertexShader, const GeometryShaderPtr& geometryShader, const PixelShaderPtr& pixelShader, RECT clientWindow) override;

	Vector3D rotationDirection = 0.f;
	float rotationSpeed = 1.0f;

	//Vector3D translationDirection = 0.f;
	float translationSpeed = 1.0f;
	float scaleSpeed = 1.0f;

	bool interpolatePosition = false;
	bool interpolateScale = false;

	Vector3D position1;
	Vector3D position2;

	Vector3D scale1;
	Vector3D scale2;

	private:
	float deltaPos = 0.0f;
	float deltaScale = 0.0f;

};

