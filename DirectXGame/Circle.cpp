#include "Circle.h"

#include "ConstantBuffer.h"
#include "PixelShader.h"

Circle::Circle(const std::string& name, const void* shaderByteCode, const size_t sizeShader, const float radius) : GameObject(name)
{
	constexpr int numVertices = 64;
	std::vector<Vertex> list;

	for (int i = 0; i <= numVertices; i += 2) {
		const float angle = static_cast<float>(i) * static_cast<float>(2.0f * M_PI / numVertices);
		float x = radius * cos(angle);
		float y = radius * sin(angle);

		list.push_back({ { x, y, 0.0f }, color, {1,1} });
		list.push_back({ {0.0f, 0.0f, 0.0f}, color, {0,0} });
	}

	const UINT sizeList = static_cast<UINT>(list.size());
	vertexBuffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(
		list.data(),
		sizeof(Vertex),
		sizeList,
		shaderByteCode,
		static_cast<UINT>(sizeShader));

	Constant constants;
	constants.time = 0;

	constantBuffer = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&constants,sizeof(Constant));
}

void Circle::update(const float deltaTime)
{

	deltaPos += deltaTime / 10.0f;
	if (deltaPos > 1.0f)
		deltaPos = 0;

	deltaScale += deltaTime / 0.15f;
}

void Circle::draw(const VertexShaderPtr& vertexShader, const GeometryShaderPtr& geometryShader, const Material& material, const RECT clientWindow)
{
	const DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();
	Constant constants;
	Matrix4x4 tempMatrix;
	const float windowWidth = (clientWindow.right - clientWindow.left) / 400.f;
	const float windowHeight = (clientWindow.bottom - clientWindow.top) / 400.f;

	constants.world.setIdentity();
	constants.view.setIdentity();
	constants.proj.setOrthographicProjection(
		windowWidth,
		windowHeight,
		-4.0f,
		4.0f);
	constants.time = 0;

	constantBuffer->update(deviceContext, &constants);

	deviceContext->setConstantBuffer(constantBuffer);

	deviceContext->setVertexBuffer(vertexBuffer);
	deviceContext->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}
