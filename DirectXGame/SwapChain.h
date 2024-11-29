#pragma once
#include "GraphicsEngine.h"
#include <d3d11.h>

#include "GraphicsResource.h"
#include "Prerequisites.h"

namespace mrlol
{
	class SwapChain : public GraphicsResource
	{
	public:
		SwapChain(HWND windowHandle, UINT width, UINT height, RenderSystem* system);
		~SwapChain() override;
		SwapChain(const SwapChain& obj) = default;
		SwapChain(SwapChain&& other) noexcept = default;
		SwapChain& operator=(const SwapChain& other) = default;
		SwapChain& operator=(SwapChain&& other) noexcept = default;

		void cleanRenderTarget() const;
		void resizeBuffers(UINT bufferCount, UINT width, UINT height) const;
		void createRenderTarget();
		RenderTexturePtr getRenderTexture() const;

		void present(bool vsync) const;

	private:
		RenderSystem* renderSystem;
		IDXGISwapChain* swapChain = nullptr;
		RenderTexturePtr renderTexture;

		friend class DeviceContext;
	};
}

