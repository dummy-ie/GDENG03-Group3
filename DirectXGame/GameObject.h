#pragma once

#include <vector>
#include <corecrt_math_defines.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vectors.h"
#include "Vertex.h"
#include "Constant.h"
#include "ConstantBuffer.h"
#include "LogUtils.h"

class GameObject
{
public:
	explicit GameObject(std::string name) : name(std::move(name))
	{
	}

	// virtual ~GameObject() 
	// {
	// 	delete vertexBuffer;
	// 	delete indexBuffer;
	// 	delete constantBuffer;
	// }

	virtual void update(float deltaTime) = 0;
	virtual void draw(
		const VertexShaderPtr& vertexShader,
		const GeometryShaderPtr& geometryShader,
		const PixelShaderPtr& pixelShader,
		RECT clientWindow);

	void setPosition(const Vector3D& position) { localPosition = position; }
	void translate(const Vector3D& translation) { localPosition += translation; }

	void setScale(const Vector3D& scale) { localScale = scale; }
	void scale(const Vector3D& scale) { localScale += scale; }

	void setRotation(const Vector3D& rotation) { localRotation = rotation; }
	void rotate(const Vector3D& rotation) { localRotation += rotation; }


	void setColor(const Vector3D& newColor)
	{
		LogUtils::log("Setting color " + color.toString() + " to: " + newColor.toString());
		color = newColor;
		LogUtils::log("color: " + color.toString());
	}

	std::string getName() { return name; }
	Vector3D getPosition() { return localPosition; }
	Vector3D getScale() { return localScale; }
	Vector3D getRotation() { return localRotation; }
	Vector3D getColor() { return color; }

protected:
	float elapsedTime = 0.f;

	std::string name;

	Vector3D localScale = 1.f;
	Vector3D localPosition = 0.f;
	Vector3D localRotation = 0.f;
	//Matrix4x4 localMatrix;

	Vector3D color;

	VertexBufferPtr vertexBuffer = nullptr;
	IndexBufferPtr indexBuffer = nullptr;
	ConstantBufferPtr constantBuffer = nullptr;
};
