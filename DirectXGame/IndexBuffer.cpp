#include "IndexBuffer.h"

#include "LogUtils.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"

IndexBuffer::IndexBuffer(const void* listIndices, const UINT sizeList, RenderSystem* system) : GraphicsResource(system), indexBuffer(nullptr)
{
	D3D11_BUFFER_DESC buffDesc = {};
	buffDesc.Usage = D3D11_USAGE_DEFAULT;
	buffDesc.ByteWidth = 4 * sizeList;
	buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = listIndices;

	indexListSize = sizeList;

	LogUtils::logHResult(this, system->directXDevice->CreateBuffer(&buffDesc, &initData, &indexBuffer));
}

IndexBuffer::~IndexBuffer()
{
	indexBuffer->Release();
}

UINT IndexBuffer::getSizeIndexList() const
{
	return this->indexListSize;
}
