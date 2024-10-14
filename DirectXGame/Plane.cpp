#include "Plane.h"

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"

Plane::Plane(const std::string& name, void* shaderByteCode, const size_t sizeShader) : GameObject(name)
{
	Vertex vertexList[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,0.0f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,0.0f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.0f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,0.0f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.0f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.0f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.0f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.0f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

	};

	vertexBuffer = GraphicsEngine::createVertexBuffer();
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

	indexBuffer = GraphicsEngine::createIndexBuffer();
	constexpr UINT sizeIndexList = ARRAYSIZE(indexList);

	indexBuffer->load(indexList, sizeIndexList);
	vertexBuffer->load(
		vertexList,
		sizeof(Vertex),
		sizeList,
		shaderByteCode,
		static_cast<UINT>(sizeShader));

	Constant constants;
	constants.time = 0;

	constantBuffer = GraphicsEngine::createConstantBuffer();
	constantBuffer->load(&constants, sizeof(Constant));
}

Plane::~Plane()
{
	GameObject::~GameObject();
}

void Plane::update(const float deltaTime)
{
	localRotation += rotationDirection * rotationSpeed * deltaTime;
}

void Plane::draw(VertexShader* vertexShader, GeometryShader* geometryShader, PixelShader* pixelShader, RECT clientWindow)
{
	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();
	Constant constants;
	Matrix4x4
		translateMatrix,
		scaleMatrix,
		xMatrix,
		yMatrix,
		zMatrix;

	const float windowWidth = static_cast<float>(clientWindow.right - clientWindow.left);
	const float windowHeight = static_cast<float>(clientWindow.bottom - clientWindow.top);

	translateMatrix.setTranslation(localPosition);
	scaleMatrix.setScale(localScale);

	zMatrix.setRotationZ(localRotation.z);
	xMatrix.setRotationX(localRotation.y);
	yMatrix.setRotationY(localRotation.x);

	constants.world.setIdentity();
	constants.world *= xMatrix * yMatrix * zMatrix * scaleMatrix * translateMatrix;

	constants.view.setIdentity();

	// constants.proj.setOrthographicProjection(
	// 	windowWidth / 400.f,
	// 	windowHeight / 400.f,
	// 	-4.0f,
	// 	4.0f);

	 const float aspectRatio = (windowWidth * 2.f) / (windowHeight * 2.f);
	 constants.proj.setPerspectiveProjection(aspectRatio, aspectRatio, 0.01f, 10000.0f);

	constants.time = 0;

	constantBuffer->update(deviceContext, &constants);

	deviceContext->setConstantBuffer(constantBuffer);

	deviceContext->setVertexBuffer(vertexBuffer);
	deviceContext->setIndexBuffer(indexBuffer);

	deviceContext->drawIndexedTriangleList(indexBuffer->getSizeIndexList(), 0, 0);
	// deviceContext->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}
