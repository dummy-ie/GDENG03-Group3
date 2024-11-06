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
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),     Vector2D(0,1) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0),  Vector2D(1,1) },
																											

		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0),    Vector2D(1,1) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1),     Vector2D(1,0) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),     Vector2D(0,0)},
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0),  Vector2D(0,1)}
	};

	Vertex vertexList[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    color,    Vector2D(0,1)},
		{Vector3D(-0.5f,0.5f,-0.5f),    color,     Vector2D(0,0)},
		{ Vector3D(0.5f,0.5f,-0.5f),   color,      Vector2D(0,1)},
		{ Vector3D(0.5f,-0.5f,-0.5f),    color,    Vector2D(1,1)},
																						
		{ Vector3D(0.5f,-0.5f,0.5f),   color,      Vector2D(1,1)},
		{ Vector3D(0.5f,0.5f,0.5f),   color,       Vector2D(1,0)},
		{ Vector3D(-0.5f,0.5f,0.5f),  color,       Vector2D(0,0)},
		{ Vector3D(-0.5f,-0.5f,0.5f),    color,    Vector2D(0,1)}
	};

	// LogUtils::log(this, "Vector3D zero: " + Vector3D::zero.toString());
	 //LogUtils::log(this, "Color and float3D zero not the same: " + std::to_string(color != Vector3D::zero));

	constexpr UINT sizeList = ARRAYSIZE(vertexList);

	unsigned int indexList[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
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
