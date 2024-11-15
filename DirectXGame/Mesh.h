#pragma once

#include "Resource.h"
#include "GameObject.h"
#include "Prerequisites.h"

class Mesh final : public Resource
{
public:
	explicit Mesh(const wchar_t* fullPath, const std::string& name);
	
	const VertexBufferPtr& getVertexBuffer();
	const IndexBufferPtr& getIndexBuffer();

private:
	VertexBufferPtr vertexBuffer;
	IndexBufferPtr indexBuffer;
	ConstantBufferPtr constantBuffer;

	friend class DeviceContext;
};

