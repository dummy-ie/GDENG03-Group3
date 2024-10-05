#pragma once
#include "Matrix4x4.h"

__declspec(align(16))
struct Constant
{
	Matrix4x4 world;
	Matrix4x4 view;
	Matrix4x4 proj;
	float time;
};
