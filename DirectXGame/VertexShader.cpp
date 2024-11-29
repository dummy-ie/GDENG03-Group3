#include "VertexShader.h"
#include "GraphicsEngine.h"
#include "LogUtils.h"

namespace mrlol
{
	VertexShader::VertexShader(const void* shaderByteCode, const size_t byteCodeSize, RenderSystem* system) : GraphicsResource(system)
	{
		LogUtils::logHResult(this, system->directXDevice->CreateVertexShader(shaderByteCode, byteCodeSize, nullptr, &vs));
	}

	VertexShader::~VertexShader()
	{
		vs->Release();
	}
}
