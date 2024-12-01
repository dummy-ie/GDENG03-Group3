#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "LogUtils.h"
#include "RenderSystem.h"

namespace gdeng03
{
	VertexBuffer::VertexBuffer(
		const void* listVertices,
		const UINT sizeVertex,
		const UINT sizeList,
		const void* shaderByteCode,
		const UINT sizeByteShader,
		RenderSystem* system) : GraphicsResource(system)
	{
		D3D11_BUFFER_DESC buffDesc = {};
		buffDesc.Usage = D3D11_USAGE_DEFAULT;
		buffDesc.ByteWidth = sizeVertex * sizeList;
		buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		buffDesc.CPUAccessFlags = 0;
		buffDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA init_data = {};
		init_data.pSysMem = listVertices;

		this->sizeVertex = sizeVertex;
		this->sizeList = sizeList;

		LogUtils::logHResult(this, system->directXDevice->CreateBuffer(&buffDesc, &init_data, &buffer));

		D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
		{
			{
				"POSITION",
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,
				0,
				0,
				D3D11_INPUT_PER_VERTEX_DATA,
				0
			},
			{
				"TEXCOORD",
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,
				0,
				12,
				D3D11_INPUT_PER_VERTEX_DATA,
				0
			},
			{
				"COLOR",
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,
				0,
				24,
				D3D11_INPUT_PER_VERTEX_DATA,
				0
			}
		};

		constexpr UINT sizeLayout = ARRAYSIZE(layoutDesc);

		LogUtils::logHResult(this, system->directXDevice->CreateInputLayout(layoutDesc, sizeLayout, shaderByteCode, sizeByteShader, &layout));
	}

	VertexBuffer::~VertexBuffer()
	{
		layout->Release();
		buffer->Release();
	}

	UINT VertexBuffer::getSizeVertexList() const
	{
		return this->sizeList;
	}
}
