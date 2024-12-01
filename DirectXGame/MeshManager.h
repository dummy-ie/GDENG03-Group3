#pragma once
#include "ResourceManager.h"
#include "Mesh.h"

namespace gdeng03
{
	class MeshManager final : public ResourceManager
	{
	public:
		MeshPtr createMeshFromFile(const wchar_t* filePath);
		MeshPtr createMeshFromPrimitiveType(PrimitiveType type);

	protected:
		Resource* createResourceFromFileConcrete(const wchar_t* filePath) override;
	};
}

