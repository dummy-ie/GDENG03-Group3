#include "PixelShader.h"

PixelShader::PixelShader(const void* shaderByteCode, const size_t byteCodeSize, RenderSystem* system) : GraphicsResource(system)
{
	LogUtils::log(this, system->directXDevice->CreatePixelShader(shaderByteCode, byteCodeSize, nullptr, &ps));
}

PixelShader::~PixelShader()
{
	ps->Release();
}