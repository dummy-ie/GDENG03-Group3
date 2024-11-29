#include "GraphicsEngine.h"

#include "MeshManager.h"

namespace mrlol
{
	GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;

	GraphicsEngine::GraphicsEngine()
	{
		try { renderSystem = new RenderSystem(); }
		catch (...) { renderSystem = nullptr; }

		try { textureManager = new TextureManager(); }
		catch (...) { textureManager = nullptr; }

		try { meshManager = new MeshManager(); }
		catch (...) { meshManager = nullptr; }

		void* shaderByteCode = nullptr;
		size_t sizeShader = 0;
		renderSystem->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "main", &shaderByteCode, &sizeShader);
		::memcpy(meshLayoutByteCode, shaderByteCode, sizeShader);
		meshLayoutSize = sizeShader;
		renderSystem->releaseCompiledShader();
	}

	GraphicsEngine::~GraphicsEngine()
	{
		delete renderSystem;
		delete textureManager;
		delete meshManager;
		delete sharedInstance;
	}

	GraphicsEngine* GraphicsEngine::get()
	{
		if (!sharedInstance)
			sharedInstance = new GraphicsEngine();

		return sharedInstance;
	}

	RenderSystem* GraphicsEngine::getRenderSystem() const
	{
		return renderSystem;
	}

	TextureManager* GraphicsEngine::getTextureManager() const
	{
		return textureManager;
	}

	MeshManager* GraphicsEngine::getMeshManager() const
	{
		return meshManager;
	}

	void GraphicsEngine::getVertexMeshLayoutShaderByteCodeAndSize(void** shaderByteCode, size_t* sizeShader)
	{
		*shaderByteCode = meshLayoutByteCode;
		*sizeShader = meshLayoutSize;
	}
}
