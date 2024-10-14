#pragma once
#include <d3d11.h>

class ConstantBuffer;
class SwapChain;
class VertexBuffer;
class IndexBuffer;
class VertexShader;
class GeometryShader;
class PixelShader;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	~DeviceContext();

	void clearRenderTargetColor(const SwapChain* swapChain, float red, float green, float blue, float alpha) const;
	void setVertexBuffer(const VertexBuffer* vertexBuffer) const;
	void setIndexBuffer(const IndexBuffer* indexBuffer) const;
	void drawTriangleList(UINT vertexCount, UINT startVertexIndex) const;
	void drawIndexedTriangleList(UINT indexCount, UINT startVertexIndex, UINT startIndexLocation) const;
	void drawTriangleStrip(UINT vertexCount, UINT startVertexIndex) const;
	void drawLineStrip(UINT vertexCount, UINT startVertexIndex) const;

	void setViewportSize(UINT width, UINT height) const;
	void setVertexShader(const VertexShader* vertexShader) const;
	void setGeometryShader(const GeometryShader* geometryShader) const;
	void setPixelShader(const PixelShader* pixelShader) const;

	void setConstantBuffer(const ConstantBuffer* constantBuffer) const;

	bool release();

private:
	ID3D11DeviceContext* deviceContext;

	friend class ConstantBuffer;
};
