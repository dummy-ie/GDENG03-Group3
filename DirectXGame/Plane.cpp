#include "Plane.h"

Plane::Plane(const std::string& name, const void* shaderByteCode, const size_t sizeShader, const Vector3D& color) : GameObject(name)
{
	const Vertex vertexListRainbow[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,0.0f),    Vector3D(1,0,0),   Vector2D(0,1)},
		{Vector3D(-0.5f,0.5f,0.0f),    Vector3D(1,1,0),    Vector2D(0,0) },
		{ Vector3D(0.5f,0.5f,0.0f),   Vector3D(1,1,0),     Vector2D(0,1) },
		{ Vector3D(0.5f,-0.5f,0.0f),     Vector3D(1,0,0),  Vector2D(1,1)},
		//BACK FACE																			 			
		{ Vector3D(0.5f,-0.5f,0.0f),    Vector3D(0,1,0),   Vector2D(1,1)},
		{ Vector3D(0.5f,0.5f,0.0f),    Vector3D(0,1,1),    Vector2D(1,0) },
		{ Vector3D(-0.5f,0.5f,0.0f),   Vector3D(0,1,1),    Vector2D(0,0)},
		{ Vector3D(-0.5f,-0.5f,0.0f),     Vector3D(0,1,0), Vector2D(0,1)}
	};

	Vertex vertexList[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,0.0f),    color,  Vector2D(0,1)},
		{Vector3D(-0.5f,0.5f,0.0f),    color,   Vector2D(0,0)},
		{ Vector3D(0.5f,0.5f,0.0f),   color,    Vector2D(0,1)},
		{ Vector3D(0.5f,-0.5f,0.0f),    color,  Vector2D(1,1)},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.0f),   color,  Vector2D(1,1)},
		{ Vector3D(0.5f,0.5f,0.0f),   color,   Vector2D(1,0)},
		{ Vector3D(-0.5f,0.5f,0.0f),  color,   Vector2D(0,0)},
		{ Vector3D(-0.5f,-0.5f,0.0f),    color,Vector2D(0,1)}
	};

	constexpr UINT sizeList = ARRAYSIZE(vertexList);

	unsigned int indexList[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
	};

	constexpr UINT sizeIndexList = ARRAYSIZE(indexList);
	indexBuffer = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(indexList, sizeIndexList);

	if (this->color == Vector3D::zero)
	{
		vertexBuffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(
			vertexListRainbow,
			sizeof(Vertex),
			sizeList,
			shaderByteCode,
			static_cast<UINT>(sizeShader));
	}
	else
	{
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

void Plane::update(const float deltaTime)
{
	localRotation += rotationDirection * rotationSpeed * deltaTime;
}

// void Plane::draw(const VertexShaderPtr& vertexShader, const GeometryShaderPtr& geometryShader, const PixelShaderPtr& pixelShader, RECT clientWindow)
// {
// 	GameObject::draw(vertexShader, geometryShader, pixelShader, clientWindow);
// }
