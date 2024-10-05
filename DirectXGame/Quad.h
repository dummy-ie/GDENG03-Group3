#pragma once
#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vectors.h"
#include "Vertex.h"
#include "Constant.h"

class Quad
{
public:

	explicit Quad(
		Vec2 size = { 0.1f, 0.1f },
		Vec2 pos = { 0.0f, 0.0f },
		Vec2 pos1 = { 0.0f, 0.0f },
		Vec3 color = { 1.0f, 1.0f, 1.0f });

	explicit Quad(Vertex list[], int size_list);

	void release() const;
	void draw(float deltaTime);

private:
	Vec2 size;
	Vec2 pos;
	Vec3 color;
	float angle = 0;
	VertexBuffer* vb;
	ConstantBuffer* cb;
	VertexShader* vs;
	GeometryShader* gs;
	PixelShader* ps;
};
