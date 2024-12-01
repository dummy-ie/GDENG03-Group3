#include "RasterizerState.h"

#include <exception>

#include "RenderSystem.h"
#include "LogUtils.h"

namespace gdeng03
{
	RasterizerState::RasterizerState(RenderSystem* system, D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode) : system(system)
	{
		D3D11_RASTERIZER_DESC desc = {};
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FillMode = fillMode;
		desc.CullMode = cullMode;

		LogUtils::logHResult(this, this->system->getDevice()->CreateRasterizerState(&desc, &rasterizerState));
	}

	RasterizerState::~RasterizerState()
	{
		rasterizerState->Release();
	}
}
