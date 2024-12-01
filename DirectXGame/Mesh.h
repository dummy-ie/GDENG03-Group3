#pragma once

#include "Resource.h"
#include "GameObject.h"
#include "Prerequisites.h"
#include "PrimitiveType.h"
#include "VertexMesh.h"

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
		void createCubeMesh(std::vector<VertexMesh>& listVertices, std::vector<unsigned int>& listIndices);
		void createPlaneMesh(std::vector<VertexMesh>& listVertices, std::vector<unsigned int>& listIndices);
		void createSphereMesh(std::vector<VertexMesh>& listVertices, std::vector<unsigned int>& listIndices);
		void createCapsuleMesh(std::vector<VertexMesh>& listVertices, std::vector<unsigned int>& listIndices);

		VertexBufferPtr vertexBuffer;
		IndexBufferPtr indexBuffer;
		ConstantBufferPtr constantBuffer;

		friend class DeviceContext;
	};
}

