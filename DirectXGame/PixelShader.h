#pragma once
#include <d3d11.h>

#include "GraphicsResource.h"
#include "LogUtils.h"

class PixelShader : public GraphicsResource
{
public:
	PixelShader(const void* shaderByteCode, const size_t byteCodeSize, RenderSystem* system);
	~PixelShader();
	PixelShader(const PixelShader& obj) = default;
	PixelShader(PixelShader&& other) noexcept = default;
	PixelShader& operator=(const PixelShader& other) = default;
	PixelShader& operator=(PixelShader&& other) noexcept = default;

private:
	ID3D11PixelShader* ps;

	friend class RenderSystem;
	friend class DeviceContext;
};

