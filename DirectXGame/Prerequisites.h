#pragma once

#include <memory>
#include "LogUtils.h"

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
class RenderSystem;
class GraphicsEngine;

typedef std::shared_ptr<SwapChain> SwapChainPtr;
typedef std::shared_ptr<DeviceContext> DeviceContextPtr;
typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;
typedef std::shared_ptr<IndexBuffer> IndexBufferPtr;
typedef std::shared_ptr<ConstantBuffer> ConstantBufferPtr;
typedef std::shared_ptr<VertexShader> VertexShaderPtr;
typedef std::shared_ptr<GeometryShader> GeometryShaderPtr;
typedef std::shared_ptr<PixelShader> PixelShaderPtr;
typedef std::shared_ptr<SamplerState> SamplerStatePtr;
