#include "ConstantBuffer.h"

#include "DeviceContext.h"
#include "GraphicsEngine.h"
#include "LogUtils.h"
#include "RenderSystem.h"

ConstantBuffer::ConstantBuffer(const void* buffer, const UINT sizeBuffer, RenderSystem* system) : GraphicsResource(system)
{
	D3D11_BUFFER_DESC buffDesc = {};
	buffDesc.Usage = D3D11_USAGE_DEFAULT;
	buffDesc.ByteWidth = sizeBuffer;
	buffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = buffer;

	LogUtils::log(this, system->directXDevice->CreateBuffer(&buffDesc, &initData, &constantBuffer));
}

ConstantBuffer::~ConstantBuffer()
{
	if (constantBuffer)
		constantBuffer->Release();
}

void ConstantBuffer::update(const DeviceContextPtr& context, const void* buffer) const
{
	context->deviceContext->UpdateSubresource(this->constantBuffer, NULL, nullptr, buffer, NULL, NULL);
}
