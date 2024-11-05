#include "Cylinder.h"

Cylinder::Cylinder(const std::string& name, void* shaderByteCode, size_t sizeShader, const Vector3D& color) : GameObject(name)
{


	std::vector<Vertex> vertexList;

	//CREATING THE CIRCLES
	Vertex topCenter = { Vector3D(0,0.5f,0), color, color };
	Vertex bottomCenter = { Vector3D(0,-0.5f,0), color, color };
	vertexList.push_back(bottomCenter);
	vertexList.push_back(topCenter);
	

	int segments = 50;
	float radius = 0.4f;
	for (int i = 0; i <= segments; ++i)
	{
		float theta = (2.0f * 3.14159f * i) / segments;

		vertexList.push_back({Vector3D(radius * sinf(theta), -0.5f,  radius * cosf(theta)), color, color });
		vertexList.push_back({ Vector3D(radius * sinf(theta),  0.5f,  radius * cosf(theta)), color, color });
	}


	//Vertex vertexList[] =
	//{
	//	//X - Y - Z
	//	//FRONT FACE
	//	{Vector3D(-0.5f,-0.5f,-0.5f),    color,  color},
	//	{Vector3D(-0.5f,0.5f,-0.5f),    color, color},
	//	{Vector3D(0.5f,0.5f,-0.5f),   color,  color},
	//	{Vector3D(0.5f,-0.5f,-0.5f),    color, color},

	//	//BACK FACE
	//	{Vector3D(0.5f,-0.5f,0.5f),   color, color},
	//	{Vector3D(0.5f,0.5f,0.5f),   color, color},
	//	{Vector3D(-0.5f,0.5f,0.5f),  color,  color},
	//	{Vector3D(-0.5f,-0.5f,0.5f),    color, color}
	//};

	//// LogUtils::log(this, "Vector3D zero: " + Vector3D::zero.toString());
	// //LogUtils::log(this, "Color and Vec3D zero not the same: " + std::to_string(color != Vector3D::zero));

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

	
    

	//unsigned int indexList[] =
	//{
	//	//FRONT SIDE
	//	0,1,2,  //FIRST TRIANGLE
	//	2,3,0,  //SECOND TRIANGLE
	//	//BACK SIDE
	//	4,5,6,
	//	6,7,4,
	//	//TOP SIDE
	//	1,6,5,
	//	5,2,1,
	//	//BOTTOM SIDE
	//	7,0,3,
	//	3,4,7,
	//	//RIGHT SIDE
	//	3,2,5,
	//	5,4,3,
	//	//LEFT SIDE
	//	7,6,1,
	//	1,0,7
	//};

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