#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include "Prerequisites.h"
#include "RenderSystem.h"
#include "TextureManager.h"
//#include "MeshManager.h"

namespace mrlol
{
	class GraphicsEngine
	{
	public:
		static GraphicsEngine* get();
		// void initialize();
		// void destroy();

		RenderSystem* getRenderSystem() const;
		TextureManager* getTextureManager() const;
		MeshManager* getMeshManager() const;

		void getVertexMeshLayoutShaderByteCodeAndSize(void** shaderByteCode, size_t* sizeShader);

		GraphicsEngine(GraphicsEngine const&) = delete;
		GraphicsEngine& operator=(GraphicsEngine const&) = delete;
		GraphicsEngine(GraphicsEngine&& other) noexcept = delete;
		GraphicsEngine& operator=(GraphicsEngine&& other) noexcept = delete;

	private:
		GraphicsEngine();
		~GraphicsEngine();

		static GraphicsEngine* sharedInstance;
		RenderSystem* renderSystem = nullptr;
		TextureManager* textureManager = nullptr;
		MeshManager* meshManager = nullptr;

		unsigned char meshLayoutByteCode[1024];
		size_t meshLayoutSize = 0;
	};
}

