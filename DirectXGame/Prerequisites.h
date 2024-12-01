#pragma once

#include <memory>
#include "LogUtils.h"

namespace gdeng03
{
	class SamplerState;
	class GraphicsResource;
	class ConstantBuffer;
	class SwapChain;
	class DeviceContext;
	class VertexBuffer;
	class IndexBuffer;
	class VertexShader;
	class GeometryShader;
	class PixelShader;
	class RasterizerState;
	class RenderSystem;
	class Viewport;
	class GraphicsEngine;
	class Resource;
	class ResourceManager;
	class Texture;
	class RenderTexture;
	class TextureManager;
	class Mesh;
	class MeshManager;
	class GameObject;
	class Material;
	class Camera;
	class SceneCamera;

	typedef std::shared_ptr<SwapChain> SwapChainPtr;
	typedef std::shared_ptr<DeviceContext> DeviceContextPtr;
	typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;
	typedef std::shared_ptr<IndexBuffer> IndexBufferPtr;
	typedef std::shared_ptr<ConstantBuffer> ConstantBufferPtr;
	typedef std::shared_ptr<VertexShader> VertexShaderPtr;
	typedef std::shared_ptr<GeometryShader> GeometryShaderPtr;
	typedef std::shared_ptr<PixelShader> PixelShaderPtr;
	typedef std::shared_ptr<RasterizerState> RasterizerStatePtr;
	typedef std::shared_ptr<Viewport> ViewportPtr;
	typedef std::shared_ptr<SamplerState> SamplerStatePtr;
	typedef std::shared_ptr<Resource> ResourcePtr;
	typedef std::shared_ptr<Texture> TexturePtr;
	typedef std::shared_ptr<RenderTexture> RenderTexturePtr;
	typedef std::shared_ptr<Mesh> MeshPtr;
	typedef std::shared_ptr<GameObject> GameObjectPtr;
	typedef std::shared_ptr<Material> MaterialPtr;
	typedef std::shared_ptr<Camera> CameraPtr;
	typedef std::shared_ptr<SceneCamera> SceneCameraPtr;
}
