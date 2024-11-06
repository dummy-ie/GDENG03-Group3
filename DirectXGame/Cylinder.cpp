#include "Cylinder.h"

Cylinder::Cylinder(const std::string& name, void* shaderByteCode, size_t sizeShader, const Vector3D& color) : GameObject(name)
{


	std::vector<Vertex> vertexList;

	//CREATING THE CIRCLES
	Vertex topCenter = { Vector3D(0,0.5f,0), color, Vector2D(0,0)};
	Vertex bottomCenter = { Vector3D(0,-0.5f,0), color, Vector2D(1,1)};
	vertexList.push_back(topCenter);
	vertexList.push_back(bottomCenter);
	

	int segments = 50;
	float radius = 0.4f;
	for (int i = 0; i <= segments; ++i)
	{
		float theta = (2.0f * 3.14159f * i) / segments;

		vertexList.push_back({Vector3D(radius * sinf(theta), -0.5f,  radius * cosf(theta)), color, Vector2D((float)i / segments,1) });
		vertexList.push_back({ Vector3D(radius * sinf(theta),  0.5f,  radius * cosf(theta)), color, Vector2D((float)i / segments,0) });
	}

	UINT sizeList = vertexList.size();

	std::vector<UINT> indexList;

	for (int i = 2; i < segments * 2 + 2; i += 2)
	{
		indexList.push_back(i);
		indexList.push_back(i + 3);
		indexList.push_back(i + 1);

		indexList.push_back(i);
		indexList.push_back(i + 2);
		indexList.push_back(i + 3);
	}

	for (int i = 3; i < segments * 2 + 3; i += 2)
	{
		indexList.push_back(0);
		indexList.push_back(i);
		indexList.push_back(i + 2);
	}

    for (int i = 2; i < segments * 2 + 2; i += 2)
    {
        indexList.push_back(1);
		indexList.push_back(i + 2);
		indexList.push_back(i);
    }

	UINT sizeIndexList = indexList.size();


	indexBuffer = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(indexList.data(), sizeIndexList);

	//LogUtils::log(this, "using colored vertices");
	vertexBuffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(
	vertexList.data(),
	sizeof(Vertex),
	sizeList,
	shaderByteCode,
	static_cast<UINT>(sizeShader));

	Constant constants;
	constants.time = 0;
	//constants.cameraPos = 0.f;

	constantBuffer = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&constants, sizeof(Constant));
}

void Cylinder::update(const float deltaTime)
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