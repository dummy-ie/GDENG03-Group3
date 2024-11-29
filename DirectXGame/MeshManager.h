#pragma once
#include "ResourceManager.h"
#include "Mesh.h"

namespace mrlol
{
	class MeshManager final : public ResourceManager
	{
	public:
		MeshPtr createMeshFromFile(const wchar_t* filePath);

	protected:
		Resource* createResourceFromFileConcrete(const wchar_t* filePath) override;
	};
}

