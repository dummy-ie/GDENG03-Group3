#pragma once

#include "Vector.h"
#include "SwapChain.h"
#include "VertexBuffer.h"

class SwapChain;
class VertexBuffer;

class Quad
{
public:
	Quad(float height, float width);
	~Quad();
	
public:
	void RenderQuadOnWindow();
	
private:
	Vector* posX;
	Vector* posY;
	float height;
	float width;
};

