#pragma once
#include <d3d11.h>

#include "GraphicsResource.h"
#include "Prerequisites.h"

namespace gdeng03
{
	class IndexBuffer : public GraphicsResource
	{
	public:
		IndexBuffer(const void* listIndices, UINT sizeList, RenderSystem* system);
		~IndexBuffer();
		IndexBuffer(const IndexBuffer& obj) = default;
		IndexBuffer(IndexBuffer&& other) noexcept = default;
		IndexBuffer& operator=(const IndexBuffer& other) = default;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept = default;

		UINT getSizeIndexList() const;

	private:
		UINT indexListSize;

		ID3D11Buffer* indexBuffer;

		friend class DeviceContext;
	};
}

