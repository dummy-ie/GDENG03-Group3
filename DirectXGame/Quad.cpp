#include "Quad.h"

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "ConstantBuffer.h"
#include "LogUtils.h"
#include "MathUtil.h"
#include "PixelShader.h"
#include "VertexShader.h"

Quad::Quad(const std::string& name, void* shaderByteCode, const size_t sizeShader) : GameObject(name)
{
	constexpr int numVertices = 64;
	Vertex list[] =
	{
		//X - Y - Z
		{Vector3D(-0.5f,-0.5f,0.0f),      Vector3D(0,0,0), Vector3D(0,1,0) }, // POS1
		{Vector3D(-0.5f,0.5f,0.0f),        Vector3D(1,1,0), Vector3D(0,1,1) }, // POS2
		{ Vector3D(0.5f,-0.5f,0.0f),      Vector3D(0,0,1),  Vector3D(1,0,0) },// POS2
		{ Vector3D(0.5f,0.5f,0.0f),        Vector3D(1,1,1), Vector3D(0,0,1) }
	};

	vertexBuffer = GraphicsEngine::createVertexBuffer();
	constexpr UINT indexListSize = ARRAYSIZE(list);

	vertexBuffer->load(list, sizeof(Vertex), indexListSize, shaderByteCode, static_cast<UINT>(sizeShader));

	Constant constants;
	constants.time = 0;

	constantBuffer = GraphicsEngine::createConstantBuffer();
	constantBuffer->load(&constants, sizeof(Constant));
}

Quad::~Quad()
{
	GameObject::~GameObject();
}

void Quad::update(const float deltaTime)
{

	movementSpeed += acceleration;
	localPosition += moveDirection * movementSpeed * deltaTime;
	if (localPosition.y <= -5.f)
	{
		localPosition = originalPosition;
		moveDirection.x = randomRangeFloat(-1.f, 1.f);
		movementSpeed = 1.f;
	}

	delta += deltaTime;
	//LogUtils::log(this, "localPosition = " + localPosition.toString());
}

void Quad::draw(VertexShader* vertexShader, GeometryShader* geometryShader, PixelShader* pixelShader, const RECT clientWindow)
{
	const DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();
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

	constants.view.setIdentity();

	// constants.proj.setOrthographicProjection(
	// 	windowWidth / 400.f,
	// 	windowHeight / 400.f,
	// 	-4.0f,
	// 	4.0f);

	const float aspectRatio = (windowWidth * 2.f) / (windowHeight * 2.f);
	constants.proj.setPerspectiveProjection(aspectRatio, aspectRatio, 0.01f, 10000.0f);

	constants.time = (sin(delta + 1.0f) / 2.0f);

	constantBuffer->update(deviceContext, &constants);

	deviceContext->setConstantBuffer(constantBuffer);

	deviceContext->setVertexBuffer(vertexBuffer);
	//deviceContext->setIndexBuffer(indexBuffer);

	deviceContext->setVertexShader(vertexShader);
	deviceContext->setGeometryShader(geometryShader);
	deviceContext->setPixelShader(pixelShader);

	deviceContext->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}