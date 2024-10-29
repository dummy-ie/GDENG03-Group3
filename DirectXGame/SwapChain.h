#pragma once
#include "GraphicsEngine.h"
#include <d3d11.h>

#include "GraphicsResource.h"
#include "Prerequisites.h"

class SwapChain : public GraphicsResource
{
public:
	SwapChain(const HWND windowHandle, const UINT width, const UINT height, RenderSystem* system);
	~SwapChain();
	SwapChain(const SwapChain& obj) = default;
	SwapChain(SwapChain&& other) noexcept = default;
	SwapChain& operator=(const SwapChain& other) = default;
	SwapChain& operator=(SwapChain&& other) noexcept = default;

	bool present(bool vsync) const;

private:
	//ID3D11Device* directXDevice = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;

	friend class DeviceContext;
};

