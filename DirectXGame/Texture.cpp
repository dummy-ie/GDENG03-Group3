#include "Texture.h"
#include <DirectXTex.h>
#include "GraphicsEngine.h"

namespace mrlol
{
	Texture::Texture(const wchar_t* fullPath) : Resource(fullPath)
	{
		DirectX::ScratchImage imageData;
		LogUtils::logHResult(
			this,
			DirectX::LoadFromWICFile(fullPath, DirectX::WIC_FLAGS_NONE, nullptr, imageData));

		LogUtils::logHResult(
			this,
			DirectX::CreateTexture(
				GraphicsEngine::get()->getRenderSystem()->getDevice(),
				imageData.GetImages(),
				imageData.GetImageCount(), imageData.GetMetadata(), &texture));

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = imageData.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = static_cast<UINT>(imageData.GetMetadata().mipLevels);
		desc.Texture2D.MostDetailedMip = 0;

		LogUtils::logHResult(
			this,
			GraphicsEngine::get()->getRenderSystem()->getDevice()->CreateShaderResourceView(texture, &desc, &shaderResourceView));
	}

	Texture::~Texture()
	{
		texture->Release();
		shaderResourceView->Release();
	}

	ID3D11Resource* Texture::getResource() const
	{
		if (!texture)
			return nullptr;

		return texture;
	}

	ID3D11ShaderResourceView* Texture::getShaderResourceView() const
	{
		if (!shaderResourceView)
			return nullptr;

		return shaderResourceView;
	}
}
