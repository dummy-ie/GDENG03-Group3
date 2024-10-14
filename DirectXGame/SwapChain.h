#pragma once
#include "GraphicsEngine.h"
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain(ID3D11Device* directXDevice);
	~SwapChain();
	void initialize(HWND windowHandle, UINT width, UINT height);
	bool release() const;
	bool present(bool vsync) const;

private:
	ID3D11Device* directXDevice = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;

	friend class DeviceContext;
};

