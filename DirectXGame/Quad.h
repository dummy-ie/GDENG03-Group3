#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
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
		Vector3D pos = { 0.0f, 0.0f, 0.0f },
		Vector3D pos1 = { 0.0f, 0.0f, 0.0f },
		Vector3D color = Vector3D( 1.0f, 1.0f, 1.0f ));

	explicit Quad(Vertex list[4]);

	void release() const;
	void draw(float deltaTime, RECT clientWindow);

private:

	void initialize(Vertex list[], int size_list);

	float m_delta_pos = 0;
	float m_delta_scale = 0;
	Vec2 size;
	Vector3D pos;
	Vector3D pos1;
	Vector3D color;

	float speed = 1.f;
	float acceleration = 0.025f;
	float angle = 0.f;

	VertexBuffer* vb;
	IndexBuffer* ib;
	ConstantBuffer* cb;

	VertexShader* vs;
	GeometryShader* gs;
	PixelShader* ps;
};
