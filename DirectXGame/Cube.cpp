#include "Cube.h"

#include <corecrt_math_defines.h>

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"

Cube::Cube(const std::string& name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	Vertex vertexList[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(1.0f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.0f,1.0f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.0f,0.0f,1.0f) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(1.0f,1.f,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,1.f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,1.f,1.0f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.f,1.f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(1.f,0.f,0) }

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

Cube::~Cube()
{
	GameObject::~GameObject();
}

void Cube::update(const float deltaTime)
{
	deltaPos += deltaTime / 10.0f;
	if (deltaPos > 1.0f)
		deltaPos = 0;

	deltaScale += deltaTime / 2.0f;

	localRotation += rotationDirection * rotationSpeed * deltaTime;
}

void Cube::draw(VertexShader* vertexShader, GeometryShader* geometryShader, PixelShader* pixelShader, const RECT clientWindow)
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
	yMatrix.setRotationY(localRotation.y);
	xMatrix.setRotationX(localRotation.x);

	constants.world.setIdentity();
	constants.world *= xMatrix * yMatrix * zMatrix * scaleMatrix * translateMatrix;

	constants.view = CameraManager::getInstance()->activeCamera->getView();

	// constants.proj.setOrthographicProjection(
	// 	windowWidth / 400.f,
	// 	windowHeight / 400.f,
	// 	-4.0f,
	// 	4.0f);

	const float aspectRatio = windowWidth / windowHeight;
	constants.proj.setPerspectiveProjection(aspectRatio, aspectRatio, 0.1f, 1000.0f);

	constants.time = deltaScale;

	constantBuffer->update(deviceContext, &constants);

	deviceContext->setConstantBuffer(constantBuffer);

	deviceContext->setVertexBuffer(vertexBuffer);
	deviceContext->setIndexBuffer(indexBuffer);

	deviceContext->setVertexShader(vertexShader);
	deviceContext->setGeometryShader(geometryShader);
	deviceContext->setPixelShader(pixelShader);

	deviceContext->drawIndexedTriangleList(indexBuffer->getSizeIndexList(), 0, 0);
	// deviceContext->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}
