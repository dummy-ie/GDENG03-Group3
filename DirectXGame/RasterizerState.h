#pragma once

#include <d3d11.h>
#include "Prerequisites.h"

namespace gdeng03
{
	class RasterizerState
	{
	private:
		RenderSystem* system = nullptr;
		ID3D11RasterizerState* rasterizerState;
		// desc;

	private:
		friend class Viewport;
		friend class DeviceContext;

	public:
		RasterizerState(RenderSystem* system, D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode);
		~RasterizerState();
	};
}