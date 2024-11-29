#pragma once
#include "Vector2D.h"
#include "Vector3D.h"

namespace mrlol
{
	struct Vertex
	{
		Vector3D position;
		Vector3D color;
		Vector2D texcoord;
	};
}
