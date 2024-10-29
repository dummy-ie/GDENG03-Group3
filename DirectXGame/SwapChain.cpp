#include "SwapChain.h"

#include "LogUtils.h"
#include "RenderSystem.h"

SwapChain::SwapChain(
	const HWND windowHandle,
	const UINT width,
	const UINT height,
	RenderSystem* system) : GraphicsResource(system)
{
	ID3D11Device* device = system->directXDevice;
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = windowHandle;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	LogUtils::log(this, system->dxgiFactory->CreateSwapChain(device, &desc, &swapChain));

	ID3D11Texture2D* buffer = nullptr;
	LogUtils::log(this, swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buffer)));

	LogUtils::log(this, device->CreateRenderTargetView(buffer, nullptr, &renderTargetView));
	buffer->Release();

	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texDesc.MipLevels = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.MiscFlags = 0;
	texDesc.ArraySize = 1;
	texDesc.CPUAccessFlags = 0;

	LogUtils::log(this, system->directXDevice->CreateTexture2D(&texDesc, nullptr, &buffer));

	LogUtils::log(this, system->directXDevice->CreateDepthStencilView(buffer, nullptr, &depthStencilView));
	buffer->Release();
}

SwapChain::~SwapChain()
{
	swapChain->Release();
}

bool SwapChain::present(const bool vsync) const
{
	LogUtils::log(this, swapChain->Present(vsync, NULL));
	return true;
}
