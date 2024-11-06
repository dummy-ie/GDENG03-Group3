#include "Quad.h"


Quad::Quad(const std::string& name, const void* shaderByteCode, const size_t sizeShader) : GameObject(name)
{
	constexpr int numVertices = 64;
	Vertex list[] =
	{
		//X - Y - Z
		{Vector3D(-0.5f,-0.5f,0.0f),      Vector3D(0,0,0), Vector2D(0,1)}, // POS1
		{Vector3D(-0.5f,0.5f,0.0f),        Vector3D(1,1,0),Vector2D(0,0) }, // POS2
		{ Vector3D(0.5f,-0.5f,0.0f),      Vector3D(0,0,1), Vector2D(0,1) },// POS2
		{ Vector3D(0.5f,0.5f,0.0f),        Vector3D(1,1,1),Vector2D(1,1) }
	};

	constexpr UINT indexListSize = ARRAYSIZE(list);
	vertexBuffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(list, sizeof(Vertex), indexListSize, shaderByteCode, static_cast<UINT>(sizeShader));

	Constant constants;
	constants.time = 0;

	constantBuffer = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&constants, sizeof(Constant));
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

void Quad::draw(const VertexShaderPtr& vertexShader, const GeometryShaderPtr& geometryShader, const Material& material, const RECT clientWindow)
{
	const DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();
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
	deviceContext->setPixelShader(material);

	deviceContext->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}