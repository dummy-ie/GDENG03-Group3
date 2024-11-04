#pragma once

#include "GameObject.h"

class Circle : public GameObject
{
public:
	Circle(const std::string& name, const void* shaderByteCode, size_t sizeShader, const float radius);

	// release everything in destructor instead
	//void release() const override;

	void update(float deltaTime) override;
	void draw(
		const VertexShaderPtr& vertexShader,
		const GeometryShaderPtr& geometryShader,
		const PixelShaderPtr& pixelShader,
		RECT clientWindow) override;

private:
	float deltaPos = 0;
	float deltaScale = 0;
};
