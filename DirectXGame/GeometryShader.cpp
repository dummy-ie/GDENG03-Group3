#include "GeometryShader.h"
#include "GraphicsEngine.h"
#include "LogUtils.h"

namespace mrlol
{
	GeometryShader::GeometryShader(const void* shaderByteCode, const size_t byteCodeSize, RenderSystem* system) : GraphicsResource(system)
	{
		LogUtils::logHResult(this, system->directXDevice->CreateGeometryShader(shaderByteCode, byteCodeSize, nullptr, &gs));
	}

	GeometryShader::~GeometryShader()
	{
		gs->Release();
	}
}
