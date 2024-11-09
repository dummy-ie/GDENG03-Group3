#pragma once
#include <d3d11.h>

#include "GraphicsResource.h"
#include "Material.h"
#include "Prerequisites.h"

class DeviceContext : public GraphicsResource
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext, RenderSystem* system);
	~DeviceContext();
	DeviceContext(const DeviceContext& obj) = default;
	DeviceContext(DeviceContext&& other) noexcept = default;
	DeviceContext& operator=(const DeviceContext& other) = default;
	DeviceContext& operator=(DeviceContext&& other) noexcept = default;

	//ID3D11DeviceContext* getContext() const;

	void clearRenderTargetColor(const SwapChainPtr& swapChain, float red, float green, float blue, float alpha) const;
	void setVertexBuffer(const VertexBufferPtr& vertexBuffer) const;
	void setIndexBuffer(const IndexBufferPtr& indexBuffer) const;
	void drawTriangleList(UINT vertexCount, UINT startVertexIndex) const;
	void drawIndexedTriangleList(UINT indexCount, UINT startVertexIndex, UINT startIndexLocation) const;
	void drawTriangleStrip(UINT vertexCount, UINT startVertexIndex) const;
	void drawLineStrip(UINT vertexCount, UINT startVertexIndex) const;

	void setViewportSize(UINT width, UINT height) const;
	void setVertexShader(const VertexShaderPtr& vertexShader) const;
	void setGeometryShader(const GeometryShaderPtr& geometryShader) const;
	void setPixelShader(const PixelShaderPtr& pixelShader) const;
	void setTexture(const Material& material);

	void setConstantBuffer(const ConstantBufferPtr& constantBuffer) const;

	bool copyResource(ID3D11Resource* destResource, ID3D11Resource* srcResource) const;
	bool mapResource(ID3D11Resource* resource, D3D11_MAPPED_SUBRESOURCE& mappedData, UINT subresource, D3D11_MAP mapType, UINT mapFlags) const;
	void unmapResource(ID3D11Resource* resource, UINT subresource) const;

private:
	ID3D11DeviceContext* deviceContext;

	friend class ConstantBuffer;
	friend class UIManager;
};
