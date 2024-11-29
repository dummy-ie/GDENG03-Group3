#pragma once
#include <d3d11.h>

#include "GraphicsResource.h"

namespace mrlol
{
	class GeometryShader : public GraphicsResource
	{
	public:
		GeometryShader(const void* shaderByteCode, const size_t byteCodeSize, RenderSystem* system);
		~GeometryShader();
		GeometryShader(const GeometryShader& obj) = default;
		GeometryShader(GeometryShader&& other) noexcept = default;
		GeometryShader& operator=(const GeometryShader& other) = default;
		GeometryShader& operator=(GeometryShader&& other) noexcept = default;

	private:
		ID3D11GeometryShader* gs;

		friend class RenderSystem;
		friend class DeviceContext;
	};
}

