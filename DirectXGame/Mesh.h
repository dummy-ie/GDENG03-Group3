#pragma once

#include "Resource.h"
#include "GameObject.h"
#include "Prerequisites.h"
#include "PrimitiveType.h"

namespace gdeng03
{
	class Mesh : public Resource
	{
	public:
		explicit Mesh(const wchar_t* fullPath);
		explicit Mesh(PrimitiveType type);

		const VertexBufferPtr& getVertexBuffer();
		const IndexBufferPtr& getIndexBuffer();

	private:
		void createCubeMesh();
		void createPlaneMesh();
		void createSphereMesh();
		void createCapsuleMesh();

		VertexBufferPtr vertexBuffer;
		IndexBufferPtr indexBuffer;
		ConstantBufferPtr constantBuffer;

		friend class DeviceContext;
	};
}

