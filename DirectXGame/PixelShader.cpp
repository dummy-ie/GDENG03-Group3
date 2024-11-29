#include "PixelShader.h"

namespace mrlol
{
	PixelShader::PixelShader(const void* shaderByteCode, const size_t byteCodeSize, RenderSystem* system) : GraphicsResource(system)
	{
		LogUtils::logHResult(this, system->directXDevice->CreatePixelShader(shaderByteCode, byteCodeSize, nullptr, &ps));
	}

	PixelShader::~PixelShader()
	{
		ps->Release();
	}
}