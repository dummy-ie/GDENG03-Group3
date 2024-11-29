#include "SwapChain.h"

#include "LogUtils.h"
#include "RenderSystem.h"
#include "RenderTexture.h"

namespace mrlol
{
	SwapChain::SwapChain(
		const HWND windowHandle,
		const UINT width,
		const UINT height,
		RenderSystem* system) : GraphicsResource(system)
	{
		ID3D11Device* device = system->directXDevice;
		renderSystem = system;
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

		LogUtils::logHResult(this, system->dxgiFactory->CreateSwapChain(device, &desc, &swapChain));

		try
		{
			renderTexture = std::make_shared<RenderTexture>();
		}
		catch (...)
		{
			renderTexture = nullptr;
			LogUtils::error("Failed to create render texture!");
		}
	}

	SwapChain::~SwapChain()
	{
		swapChain->Release();
	}

	void SwapChain::cleanRenderTarget() const
	{
		if (renderTexture->renderTargetView)
		{
			renderTexture->renderTargetView->Release();
			renderTexture->renderTargetView = nullptr;
		}
	}

	void SwapChain::resizeBuffers(UINT bufferCount, const UINT width, const UINT height) const
	{
		renderTexture->resizeResources(width, height);
		LogUtils::logHResult(this, swapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0));
	}

	void SwapChain::createRenderTarget()
	{
		ID3D11Texture2D* buffer = nullptr;
		LogUtils::logHResult(this, swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buffer)));

		LogUtils::logHResult(this, renderSystem->getDevice()->CreateRenderTargetView(buffer, nullptr, &renderTexture->renderTargetView));

		buffer->Release();
	}

	RenderTexturePtr SwapChain::getRenderTexture() const
	{
		return renderTexture;
	}

	void SwapChain::present(const bool vsync) const
	{
		LogUtils::logHResult(this, swapChain->Present(vsync, NULL));
	}
}
