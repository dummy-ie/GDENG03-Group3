#include "DeviceContext.h"

#include "PixelShader.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "GeometryShader.h"
#include "IndexBuffer.h"
#include "PixelShader.h"
#include "RasterizerState.h"
#include "RenderTexture.h"
#include "SamplerState.h"
#include "Texture.h"

namespace gdeng03
{
	DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext, RenderSystem* system) : GraphicsResource(system), deviceContext(deviceContext)
	{
	}

	DeviceContext::~DeviceContext()
	{
		deviceContext->Release();
	}

	// ID3D11DeviceContext* DeviceContext::getContext() const
	// {
	// 	return this->deviceContext;
	// }

	void DeviceContext::clearRenderTargetColor(const SwapChainPtr& swapChain, const float red, const float green, const float blue, const float alpha) const
	{
		const FLOAT clearColor[] = { red, green, blue, alpha };
		deviceContext->ClearRenderTargetView(swapChain->getRenderTexture()->renderTargetView, clearColor);
		deviceContext->ClearDepthStencilView(swapChain->getRenderTexture()->depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
		deviceContext->OMSetRenderTargets(1, &swapChain->getRenderTexture()->renderTargetView, swapChain->getRenderTexture()->depthStencilView);
	}

	void DeviceContext::clearRenderTargetColor(const RenderTexturePtr& renderTexture, const float red, const float green, const float blue, const float alpha) const
	{
		const FLOAT clearColor[] = { red, green, blue, alpha };
		deviceContext->ClearRenderTargetView(renderTexture->renderTargetView, clearColor);
		deviceContext->ClearDepthStencilView(renderTexture->depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
		deviceContext->OMSetRenderTargets(1, &renderTexture->renderTargetView, renderTexture->depthStencilView);
	}

	void DeviceContext::setRenderTarget(const RenderTexturePtr& renderTexture) const
	{
		deviceContext->OMSetRenderTargets(1, &renderTexture->renderTargetView, renderTexture->depthStencilView);
	}

	void DeviceContext::setVertexBuffer(const VertexBufferPtr& vertexBuffer) const
	{
		const UINT stride = vertexBuffer->sizeVertex;
		constexpr UINT offset = 0;

		deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer->buffer, &stride, &offset);
		deviceContext->IASetInputLayout(vertexBuffer->layout);
	}

	void DeviceContext::setIndexBuffer(const IndexBufferPtr& indexBuffer) const
	{
		deviceContext->IASetIndexBuffer(indexBuffer->indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	void DeviceContext::drawTriangleList(const UINT vertexCount, const UINT startVertexIndex) const
	{
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		deviceContext->Draw(vertexCount, startVertexIndex);
	}

	void DeviceContext::drawIndexedTriangleList(const UINT indexCount, const UINT startVertexIndex, const UINT startIndexLocation) const
	{
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		deviceContext->DrawIndexed(indexCount, startIndexLocation, static_cast<INT>(startVertexIndex));
	}

	void DeviceContext::drawTriangleStrip(const UINT vertexCount, const UINT startVertexIndex) const
	{
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		deviceContext->Draw(vertexCount, startVertexIndex);
	}

	void DeviceContext::drawLineStrip(const UINT vertexCount, const UINT startVertexIndex) const
	{
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		deviceContext->Draw(vertexCount, startVertexIndex);
	}

	void DeviceContext::setViewportSize(const UINT width, const UINT height) const
	{
		D3D11_VIEWPORT vp = {};
		vp.Width = static_cast<float>(width);
		vp.Height = static_cast<float>(height);
		vp.MinDepth = 0.f;
		vp.MaxDepth = 1.f;


		deviceContext->RSSetViewports(1, &vp);
	}

	void DeviceContext::setViewport(const ViewportPtr& vp) const
	{
		deviceContext->RSSetViewports(1, &vp->viewport);
	}

	void DeviceContext::setRasterizerState(const RasterizerStatePtr& rasterizerState) const
	{
		deviceContext->RSSetState(rasterizerState->rasterizerState);
	}

	void DeviceContext::setVertexShader(const VertexShaderPtr& vertexShader) const
	{
		deviceContext->VSSetShader(vertexShader->vs, nullptr, 0);
	}

	void DeviceContext::setGeometryShader(const GeometryShaderPtr& geometryShader) const
	{
		deviceContext->GSSetShader(geometryShader->gs, nullptr, 0);
	}

	void DeviceContext::setPixelShader(const PixelShaderPtr& pixelShader) const
	{
		deviceContext->PSSetShader(pixelShader->ps, nullptr, 0);
	}

	void DeviceContext::setTexture(const Material& material) const
	{
		if (material.albedoTexture)
		{
			deviceContext->VSSetShaderResources(0, 1, &material.albedoTexture->shaderResourceView);
			deviceContext->PSSetShaderResources(0, 1, &material.albedoTexture->shaderResourceView);
		}

		if (material.normalTexture)
		{
			deviceContext->VSSetShaderResources(1, 1, &material.normalTexture->shaderResourceView);
			deviceContext->PSSetShaderResources(1, 1, &material.normalTexture->shaderResourceView);
		}

		if (material.metallicTexture)
		{
			deviceContext->VSSetShaderResources(2, 1, &material.metallicTexture->shaderResourceView);
			deviceContext->PSSetShaderResources(2, 1, &material.metallicTexture->shaderResourceView);
		}

		if (material.smoothnessTexture)
		{
			deviceContext->VSSetShaderResources(3, 1, &material.smoothnessTexture->shaderResourceView);
			deviceContext->PSSetShaderResources(3, 1, &material.smoothnessTexture->shaderResourceView);
		}

		if (material.samplerState)
		{
			deviceContext->VSSetSamplers(0, 1, &material.samplerState->samplerState);
			deviceContext->PSSetSamplers(0, 1, &material.samplerState->samplerState);
		}
	}

	void DeviceContext::setDefaultTexture() const
	{
		deviceContext->VSSetShaderResources(0, 1, &GraphicsEngine::get()->getTextureManager()->getBlankTexture()->shaderResourceView);
		deviceContext->PSSetShaderResources(0, 1, &GraphicsEngine::get()->getTextureManager()->getBlankTexture()->shaderResourceView);
	}

	void DeviceContext::setConstantBuffer(const ConstantBufferPtr& constantBuffer) const
	{
		deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer->constantBuffer);
		deviceContext->GSSetConstantBuffers(0, 1, &constantBuffer->constantBuffer);
		deviceContext->PSSetConstantBuffers(0, 1, &constantBuffer->constantBuffer);

	}

	bool DeviceContext::copyResource(ID3D11Resource* destResource, ID3D11Resource* srcResource) const
	{
		if (!deviceContext || !destResource || !srcResource) return false;
		deviceContext->CopyResource(destResource, srcResource);
		return true;
	}

	bool DeviceContext::mapResource(ID3D11Resource* resource, D3D11_MAPPED_SUBRESOURCE& mappedData, const UINT subresource,
		const D3D11_MAP mapType, const UINT mapFlags) const
	{
		if (!deviceContext || !resource) return false;
		const HRESULT hr = deviceContext->Map(resource, subresource, mapType, mapFlags, &mappedData);
		return SUCCEEDED(hr);
	}

	void DeviceContext::unmapResource(ID3D11Resource* resource, const UINT subresource) const
	{
		if (deviceContext && resource) deviceContext->Unmap(resource, subresource);
	}
}
