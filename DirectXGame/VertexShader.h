#pragma once
#include <d3d11.h>

#include "GraphicsResource.h"

namespace gdeng03
{
	class VertexShader : public GraphicsResource
	{
	public:
		VertexShader(const void* shaderByteCode, const size_t byteCodeSize, RenderSystem* system);
		~VertexShader() override;
		VertexShader(const VertexShader& obj) = default;
		VertexShader(VertexShader&& other) noexcept = default;
		VertexShader& operator=(const VertexShader& other) = default;
		VertexShader& operator=(VertexShader&& other) noexcept = default;

	private:
		ID3D11VertexShader* vs;

		friend class RenderSystem;
		friend class DeviceContext;
	};
}

