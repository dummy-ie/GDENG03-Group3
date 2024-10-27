#include "Plane.h"

Plane::Plane(const std::string& name, void* shaderByteCode, const size_t sizeShader, const Vector3D& color) : GameObject(name)
{
	Vertex vertexListRainbow[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,0.0f),    Vector3D(1,0,0),  Vector3D(1.0f,0,0) },
		{Vector3D(-0.5f,0.5f,0.0f),    Vector3D(1,1,0), Vector3D(0.0f,1.0f,0) },
		{ Vector3D(0.5f,0.5f,0.0f),   Vector3D(1,1,0),  Vector3D(0.0f,0.0f,1.0f) },
		{ Vector3D(0.5f,-0.5f,0.0f),     Vector3D(1,0,0), Vector3D(1.0f,1.f,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.0f),    Vector3D(0,1,0), Vector3D(0,1.f,0) },
		{ Vector3D(0.5f,0.5f,0.0f),    Vector3D(0,1,1), Vector3D(0,1.f,1.0f) },
		{ Vector3D(-0.5f,0.5f,0.0f),   Vector3D(0,1,1),  Vector3D(0,0.f,1.f) },
		{ Vector3D(-0.5f,-0.5f,0.0f),     Vector3D(0,1,0), Vector3D(1.f,0.f,0) }
	};

	Vertex vertexList[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,0.0f),    color,  color},
		{Vector3D(-0.5f,0.5f,0.0f),    color, color},
		{ Vector3D(0.5f,0.5f,0.0f),   color,  color},
		{ Vector3D(0.5f,-0.5f,0.0f),    color, color},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.0f),   color, color},
		{ Vector3D(0.5f,0.5f,0.0f),   color, color},
		{ Vector3D(-0.5f,0.5f,0.0f),  color,  color},
		{ Vector3D(-0.5f,-0.5f,0.0f),    color, color}
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
	if (this->color == Vector3D::zero)
	{
		vertexBuffer->load(
			vertexListRainbow,
			sizeof(Vertex),
			sizeList,
			shaderByteCode,
			static_cast<UINT>(sizeShader));
	}
	else
	{
		vertexBuffer->load(
			vertexList,
			sizeof(Vertex),
			sizeList,
			shaderByteCode,
			static_cast<UINT>(sizeShader));
	}

	Constant constants;
	constants.time = 0;
	//constants.cameraPos = 0.f;

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
	const DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();
	Constant constants;
	Matrix4x4
		translateMatrix,
		scaleMatrix,
		xMatrix,
		yMatrix,
		zMatrix;

	translateMatrix.setTranslation(localPosition);
	scaleMatrix.setScale(localScale);

	zMatrix.setRotationZ(localRotation.z);
	yMatrix.setRotationY(localRotation.y);
	xMatrix.setRotationX(localRotation.x);

	constants.cameraPos = CameraManager::getInstance()->activeCamera->getPosition();
	constants.world.setIdentity();
	Matrix4x4 rotateMatrix = xMatrix * yMatrix * zMatrix;
	constants.world = scaleMatrix * rotateMatrix * translateMatrix;

	constants.view = CameraManager::getInstance()->getView();
	constants.proj = CameraManager::getInstance()->activeCamera->getProjection();
	constants.time = 0;

	constantBuffer->update(deviceContext, &constants);

	deviceContext->setConstantBuffer(constantBuffer);

	deviceContext->setVertexBuffer(vertexBuffer);
	deviceContext->setIndexBuffer(indexBuffer);

	deviceContext->drawIndexedTriangleList(indexBuffer->getSizeIndexList(), 0, 0);
	// deviceContext->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}
