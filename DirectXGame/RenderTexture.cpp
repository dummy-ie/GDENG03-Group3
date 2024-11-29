#include "RenderTexture.h"

#include "GraphicsEngine.h"
#include "LogUtils.h"

namespace mrlol
{
	RenderTexture::RenderTexture() : width(0), height(0)
	{
		this->renderTarget = nullptr;
		resizeResources(width, height);
	}

	RenderTexture::~RenderTexture()
	{
		renderTargetView->Release();
		depthStencilView->Release();
		shaderResourceView->Release();
		renderTarget->Release();
	}

	void RenderTexture::resizeResources(const size_t newWidth, const size_t newHeight)
	{
		ID3D11Device* device = GraphicsEngine::get()->getRenderSystem()->getDevice();
		if (newWidth == this->width && newHeight == this->height || newWidth == 0 || newHeight == 0)
			return;

		if (this->width > UINT32_MAX || this->height > UINT32_MAX)
		{
			LogUtils::error("Invalid width/height");
		}

		if (!device)
			return;

		CD3D11_TEXTURE2D_DESC renderTargetDesc = {};
		renderTargetDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		renderTargetDesc.Width = static_cast<UINT>(newWidth);
		renderTargetDesc.Height = static_cast<UINT>(newHeight);
		renderTargetDesc.ArraySize = 1; // The render target view has only one texture.
		renderTargetDesc.MipLevels = 1; // Use a single mipmap level.
		renderTargetDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		renderTargetDesc.Usage = D3D11_USAGE_DEFAULT;
		renderTargetDesc.CPUAccessFlags = 0;
		renderTargetDesc.SampleDesc.Count = 1;

		LogUtils::logHResult(this, device->CreateTexture2D(&renderTargetDesc, nullptr, &this->renderTarget));

		LogUtils::logHResult(this, device->CreateRenderTargetView(renderTarget, nullptr, &this->renderTargetView));

		LogUtils::logHResult(this, device->CreateShaderResourceView(renderTarget, nullptr, &this->shaderResourceView));

		D3D11_TEXTURE2D_DESC texDesc = {};
		texDesc.Width = newWidth;
		texDesc.Height = newHeight;
		texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		texDesc.MipLevels = 1;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.MiscFlags = 0;
		texDesc.ArraySize = 1;
		texDesc.CPUAccessFlags = 0;

		ID3D11Texture2D* buffer = nullptr;

		LogUtils::logHResult(this, device->CreateTexture2D(&texDesc, nullptr, &buffer));

		LogUtils::logHResult(this, device->CreateDepthStencilView(buffer, nullptr, &depthStencilView));

		this->width = newWidth;
		this->height = newHeight;
	}

	ID3D11Texture2D* RenderTexture::getRenderTarget() const
	{
		return this->renderTarget;
	}

	ID3D11RenderTargetView* RenderTexture::getRenderTargetView() const
	{
		return this->renderTargetView;
	}

	ID3D11ShaderResourceView* RenderTexture::getShaderResourceView() const
	{
		return this->shaderResourceView;
	}
}
