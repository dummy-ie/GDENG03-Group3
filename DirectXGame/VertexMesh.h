#pragma once
#include "Vector3D.h"
#include "Vector2D.h"

class VertexMesh
{
public:
	VertexMesh() = default;

	VertexMesh(const Vector3D& position, const Vector2D& texcoord) : position(position), texcoord(texcoord)
	{
	}

	~VertexMesh() = default;
	VertexMesh(VertexMesh const&) = default;
	VertexMesh& operator=(VertexMesh const&) = default;
	VertexMesh(VertexMesh&& other) noexcept = default;
	VertexMesh& operator=(VertexMesh&& other) noexcept = default;

public:
	Vector3D position;
	Vector2D texcoord;
};