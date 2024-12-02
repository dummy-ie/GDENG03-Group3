#include "Renderer3D.h"

#include <utility>

#include "CameraManager.h"
#include "Constant.h"
#include "Mesh.h"
#include "ShaderLibrary.h"

namespace gdeng03
{
	Renderer3D::Renderer3D(
		GameObject* owner,
		MeshPtr mesh,
		const MaterialPtr& mat,
		const std::wstring& vs,
		const std::wstring& gs) :
		Component(
			std::string("RendererComponent " + owner->getUniqueName()),
			ComponentType::RENDERER,
			owner),
		mesh(std::move(mesh))
	{
		material = mat;
		if (!material)
			material = std::make_shared<Material>(L"PixelShader.hlsl");

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
		// translateMatrix.setTranslation(owner->transform.getLocalPosition());
		// scaleMatrix.setLocalScale(owner->getLocalScale());
		//
		// zMatrix.setRotationZ(owner->transform.getOrientation().x);
		// yMatrix.setRotationY(owner->transform.getOrientation().y);
		// xMatrix.setRotationX(owner->transform.getOrientation().x);
		//
		// //LogUtils::log(this, "Pos: " + CameraManager::getInstance()->activeCamera->getLocalPosition().toString());
		// constants.cameraPos = CameraManager::getInstance()->activeCamera->getLocalPosition();
		// constants.world.setIdentity();
		//
		// const Matrix4x4 rotateMatrix = xMatrix * yMatrix * zMatrix;
		// constants.world = scaleMatrix * rotateMatrix * translateMatrix;

		//owner->updateLocalMatrix();

		//Matrix4x4 newMatrix;
		//newMatrix.setLocalMatrix(owner->getLocalMatrix());

		//Matrix4x4 scaleMatrix;
		//scaleMatrix.setIdentity();
		//scaleMatrix.setLocalScale(owner->getLocalScale());

		//Matrix4x4 transMatrix;
		//transMatrix.setIdentity();
		//transMatrix.setTranslation();

		// transMatrix *= newMatrix;
		// scaleMatrix *= transMatrix;
		constants.world = owner->getLocalMatrix();
		//constants.world = scaleMatrix * transMatrix * newMatrix;

		// constants.view = CameraManager::getInstance()->getActiveSceneCameraView();
		// constants.proj = CameraManager::getInstance()->getActiveSceneCameraProjection();

		constants.time = 0;

		if (material)
		{
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
		}

		constantBuffer->update(deviceContext, &constants);

		deviceContext->setConstantBuffer(constantBuffer);

		this->vertexBuffer = mesh->getVertexBuffer();
		this->indexBuffer = mesh->getIndexBuffer();

		deviceContext->setVertexBuffer(vertexBuffer);
		deviceContext->setIndexBuffer(indexBuffer);

		deviceContext->setVertexShader(vertexShader);
		//deviceContext->setGeometryShader(geometryShader);

		if (material)
		{
			deviceContext->setPixelShader(material->getPixelShader());
			deviceContext->setTexture(*material);
		}
		else
		{
			deviceContext->setPixelShader(ShaderLibrary::get()->getPixelShader(L"PixelShader.hlsl"));
			deviceContext->setDefaultTexture();
		}

		deviceContext->drawIndexedTriangleList(indexBuffer->getSizeIndexList(), 0, 0);
	}

	Material* Renderer3D::getMaterial() const
	{
		return material.get();
	}

	Mesh* Renderer3D::getMesh() const
	{
		return mesh.get();
	}

	void Renderer3D::createMaterial()
	{
		LogUtils::log("creating new material for " + getOwner()->getUniqueName());
		material = std::make_shared<Material>(L"PixelShader.hlsl");
	}

	void Renderer3D::resetMaterial()
	{
		//material.reset(); does the same thing
		material = nullptr;
	}
}
