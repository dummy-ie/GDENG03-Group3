#include "Cube.h"

#include "Vector2D.h"


Cube::Cube(const std::string& name, void* shaderByteCode, size_t sizeShader, const Vector3D& color) : GameObject(name)
{
	Vertex vertexListRainbow[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),   Vector2D(0,1) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0),    Vector2D(0,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),     Vector2D(1,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0),  Vector2D(1,1) },
																											

		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0),    Vector2D(0,1) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1),     Vector2D(0,0) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),     Vector2D(1,0)},
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0),  Vector2D(1,1)}
	};

	Vertex vertexList[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    color,    Vector2D(0,1)},
		{Vector3D(-0.5f,0.5f,-0.5f),    color,     Vector2D(0,0)},
		{ Vector3D(0.5f,0.5f,-0.5f),   color,      Vector2D(1,0)},
		{ Vector3D(0.5f,-0.5f,-0.5f),    color,    Vector2D(1,1)},
			
		//TOP FACE
		{ Vector3D(0.5f,0.5f,-0.5f),   color,      Vector2D(1,1)},
		{ Vector3D(0.5f,0.5f,0.5f),   color,       Vector2D(1,0)},
		{ Vector3D(-0.5f,0.5f,0.5f),  color,       Vector2D(0,0)},
		{ Vector3D(-0.5f,0.5f,-0.5f),    color,    Vector2D(0,1)},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),   color,      Vector2D(0,1)},
		{ Vector3D(0.5f,0.5f,0.5f),   color,       Vector2D(0,0)},
		{ Vector3D(-0.5f,0.5f,0.5f),  color,       Vector2D(1,0)},
		{ Vector3D(-0.5f,-0.5f,0.5f),    color,    Vector2D(1,1)},
			
		//BOTTOM FACE
		{ Vector3D(0.5f, -0.5f,-0.5f),   color,      Vector2D(0,1)},
		{ Vector3D(0.5f, -0.5f,0.5f),   color,       Vector2D(0,0)},
		{ Vector3D(-0.5f,-0.5f,0.5f),  color,       Vector2D(1,0)},
		{ Vector3D(-0.5f,-0.5f,-0.5f),    color,    Vector2D(1,1)},

		//This vertex needs to be here or one of the bottom triangles is f*cked
		{ Vector3D(0,0,0),    Vector3D(0,0,0),    Vector2D(0,0)},
	};

	// LogUtils::log(this, "Vector3D zero: " + Vector3D::zero.toString());
	 //LogUtils::log(this, "Color and float3D zero not the same: " + std::to_string(color != Vector3D::zero));

	constexpr UINT sizeList = ARRAYSIZE(vertexList);

	unsigned int indexList[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//TOP SIDE
		4,7,6,
		6,5,4,
		//BACK SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		2,9,8,
		8,3,2,
		//LEFT SIDE
		1,0,11,
		11,10,1
		

	};

	constexpr UINT sizeIndexList = ARRAYSIZE(indexList);
	indexBuffer = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(indexList, sizeIndexList);

	if (color != Vector3D::zero)
	{
		//LogUtils::log(this, "using rainbow vertices");
		vertexBuffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(
			vertexListRainbow,
			sizeof(Vertex),
			sizeList,
			shaderByteCode,
			static_cast<UINT>(sizeShader));
	}
	else
	{
		//LogUtils::log(this, "using colored vertices");
		vertexBuffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(
			vertexList,
			sizeof(Vertex),
			sizeList,
			shaderByteCode,
			static_cast<UINT>(sizeShader));
	}

	Constant constants;
	constants.time = 0;
	//constants.cameraPos = 0.f;

	constantBuffer = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&constants, sizeof(Constant));
}

void Cube::update(const float deltaTime)
{
	elapsedTime += deltaTime;

	deltaPos = (sin(elapsedTime) + 1.0f) * translationSpeed;
	deltaScale = (sin(elapsedTime) + 1.0f) * scaleSpeed;

	if (interpolatePosition)
		localPosition = Vector3D::linearInterpolate(position1, position2, deltaPos);

	if (interpolateScale)
		localScale = Vector3D::linearInterpolate(scale1, scale2, deltaScale);

	localRotation += rotationDirection * rotationSpeed * deltaTime;
}

// void Cube::draw(const VertexShaderPtr& vertexShader, const GeometryShaderPtr& geometryShader, const PixelShaderPtr& pixelShader, const RECT clientWindow)
// {
// 	GameObject::draw(vertexShader, geometryShader, pixelShader, clientWindow);
// 	// deviceContext->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
// }
