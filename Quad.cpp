#include "Quad.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"

Quad::Quad(float height, float width)
{
	this->posX = new Vector(0, 0, 0);
	this->posY = new Vector(0, 0, 0);
	this->height = height;
	this->width = width;
}

Quad::~Quad()
{
}

void Quad::RenderQuadOnWindow() 
{

}
