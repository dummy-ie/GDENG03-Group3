#include "Renderer3D.h"

#include <utility>

#include "CameraManager.h"
#include "Constant.h"
#include "Mesh.h"
#include "ShaderLibrary.h"

Renderer3D::Renderer3D(
	std::string name,
	GameObject* owner,
	const MeshPtr& mesh,
	const MaterialPtr& mat,
	const std::wstring& vs,
	const std::wstring& gs) :
	Component(
		std::move(name),
		ComponentType::RENDERER,
		owner),
	material(mat),
	mesh(mesh)
{
	vertexShader = ShaderLibrary::get()->getVertexShader(vs);
	//geometryShader = ShaderLibrary::get()->getGeometryShader(gs);
	Constant constants;
	constantBuffer = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&constants, sizeof(Constant));
}

void Renderer3D::update()
{
	const DeviceContextPtr deviceContext = GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext();
	Constant constants;
	GameObject* owner = getOwner();
	//  Matrix4x4
	//  	translateMatrix,
	//  	scaleMatrix,
	//  	xMatrix,
	//  	yMatrix,
	//  	zMatrix;
	//
	// translateMatrix.setTranslation(owner->transform.getPosition());
	// scaleMatrix.setScale(owner->getScale());
	//
	// zMatrix.setRotationZ(owner->transform.getOrientation().x);
	// yMatrix.setRotationY(owner->transform.getOrientation().y);
	// xMatrix.setRotationX(owner->transform.getOrientation().x);
	//
	// //LogUtils::log(this, "Pos: " + CameraManager::getInstance()->activeCamera->getPosition().toString());
	// constants.cameraPos = CameraManager::getInstance()->activeCamera->getPosition();
	// constants.world.setIdentity();
	//
	// const Matrix4x4 rotateMatrix = xMatrix * yMatrix * zMatrix;
	// constants.world = scaleMatrix * rotateMatrix * translateMatrix;

	//owner->updateLocalMatrix();

	//Matrix4x4 newMatrix;
	//newMatrix.setMatrix(owner->getMatrix());

	//Matrix4x4 scaleMatrix;
	//scaleMatrix.setIdentity();
	//scaleMatrix.setScale(owner->getScale());

	//Matrix4x4 transMatrix;
	//transMatrix.setIdentity();
	//transMatrix.setTranslation();

	// transMatrix *= newMatrix;
	// scaleMatrix *= transMatrix;
	constants.world = owner->getMatrix();
	//constants.world = scaleMatrix * transMatrix * newMatrix;

	constants.view = CameraManager::getInstance()->activeCamera->getView();
	constants.proj = CameraManager::getInstance()->activeCamera->getProjection();

	constants.time = 0;

	constants.color = Vector3D(material->color.x, material->color.y, material->color.z);
	constants.metallic = material->metallic;
	constants.smoothness = material->smoothness;
	constants.flatness = material->flatness;
	constants.tiling = material->tiling;
	constants.offset = material->offset;

	constants.hasAlbedoMap = material->albedoTexture != nullptr;
	constants.hasMetallicMap = material->metallicTexture != nullptr;
	constants.hasSmoothnessMap = material->smoothnessTexture != nullptr;
	constants.hasNormalMap = material->normalTexture != nullptr;

	constantBuffer->update(deviceContext, &constants);

	deviceContext->setConstantBuffer(constantBuffer);

	this->vertexBuffer = mesh->getVertexBuffer();
	this->indexBuffer = mesh->getIndexBuffer();

	deviceContext->setVertexBuffer(vertexBuffer);
	deviceContext->setIndexBuffer(indexBuffer);

	deviceContext->setVertexShader(vertexShader);
	//deviceContext->setGeometryShader(geometryShader);
	deviceContext->setPixelShader(material->getPixelShader());

	deviceContext->setTexture(*material);
	deviceContext->drawIndexedTriangleList(indexBuffer->getSizeIndexList(), 0, 0);
}
