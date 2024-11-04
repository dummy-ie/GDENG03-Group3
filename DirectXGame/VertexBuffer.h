#pragma once
#include <d3d11.h>

#include "GraphicsResource.h"
#include "Prerequisites.h"

class VertexBuffer : public GraphicsResource
{
public:
	VertexBuffer(
		const void* listVertices,
		UINT sizeVertex,
		UINT sizeList,
		const void* shaderByteCode,
		UINT sizeByteShader,
		RenderSystem* system);
	~VertexBuffer();
	VertexBuffer(const VertexBuffer& obj) = default;
	VertexBuffer(VertexBuffer&& other) noexcept = default;
	VertexBuffer& operator=(const VertexBuffer& other) = default;
	VertexBuffer& operator=(VertexBuffer&& other) noexcept = default;

	UINT getSizeVertexList() const;

private:
	UINT sizeVertex;
	UINT sizeList;

	ID3D11Buffer* buffer;
	ID3D11InputLayout* layout;

	friend class DeviceContext;
};

