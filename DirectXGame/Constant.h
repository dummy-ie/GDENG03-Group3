#pragma once
#include "Matrix4x4.h"

namespace gdeng03
{
	__declspec(align(16))
		struct Constant
	{
		Matrix4x4 world;
		// Matrix4x4 view;
		// Matrix4x4 proj;
		Vector3D cameraPos;
		float time;

		Vector3D color;
		float metallic;
		float smoothness;
		float flatness;
		Vector2D tiling;
		Vector2D offset;

		float hasAlbedoMap;
		float hasNormalMap;
		float hasMetallicMap;
		float hasSmoothnessMap;
	};

	__declspec(align(16))
		struct CameraBuffer
	{
		Matrix4x4 view;
		Matrix4x4 proj;
		Vector3D cameraPosition;
	};
}