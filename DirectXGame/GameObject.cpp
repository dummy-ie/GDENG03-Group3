#include "GameObject.h"

#include <iostream>

#include "CameraManager.h"
#include "ConstantBuffer.h"

// void GameObject::draw(VertexShader* vs, GeometryShader* gs, PixelShader* ps, RECT clientWindow)
// {
// 	std::cout << "GameObject draw: " << vs << " " << gs << " " << ps << std::endl;
//
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vs, constantBuffer);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(gs, constantBuffer);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(ps, constantBuffer);
//
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setGeometryShader(gs);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);
//
// 	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);
// 	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
// }

void GameObject::draw(const VertexShaderPtr& vertexShader, const GeometryShaderPtr& geometryShader, const Material& material,
                      RECT clientWindow)
{
	const DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();
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

	//LogUtils::log(this, "Pos: " + CameraManager::getInstance()->activeCamera->getPosition().toString());
	constants.cameraPos = CameraManager::getInstance()->activeCamera->getPosition();
	constants.world.setIdentity();

	const Matrix4x4 rotateMatrix = xMatrix * yMatrix * zMatrix;
	constants.world = scaleMatrix * rotateMatrix * translateMatrix;

	constants.view = CameraManager::getInstance()->activeCamera->getView();
	constants.proj = CameraManager::getInstance()->activeCamera->getProjection();

	constants.time = 0;

	constants.color = Vector3D(material.color.x, material.color.y, material.color.z);
	constants.metallic = material.metallic;
	constants.smoothness = material.smoothness;
	constants.flatness = material.flatness;
	constants.tiling = material.tiling;
	constants.offset = material.offset;

	constantBuffer->update(deviceContext, &constants);

	deviceContext->setConstantBuffer(constantBuffer);

	deviceContext->setVertexBuffer(vertexBuffer);
	deviceContext->setIndexBuffer(indexBuffer);

	deviceContext->setVertexShader(vertexShader);
	deviceContext->setGeometryShader(geometryShader);
	deviceContext->setPixelShader(material.getPixelShader());

	deviceContext->setTexture(material);

	deviceContext->drawIndexedTriangleList(indexBuffer->getSizeIndexList(), 0, 0);
}
