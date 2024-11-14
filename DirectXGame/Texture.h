#pragma once
#include "Resource.h"
#include <WICTextureLoader.h>
#include "Prerequisites.h"
#include <d3d11.h>
#include <wrl/client.h>

class Texture final : public Resource
{
public:
	explicit Texture(const wchar_t* fullPath);
	~Texture() override;
	Texture(Texture const&) = default;
	Texture& operator=(Texture const&) = default;
	Texture(Texture&& other) noexcept = default;
	Texture& operator=(Texture&& other) noexcept = default;

	ID3D11Resource* getResource() const;
	ID3D11ShaderResourceView* getShaderResourceView() const;

private:
	ID3D11Resource* texture = nullptr;
	ID3D11ShaderResourceView* shaderResourceView = nullptr;

	friend class DeviceContext;
};

