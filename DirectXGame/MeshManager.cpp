#include "MeshManager.h"

namespace gdeng03
{
	MeshPtr MeshManager::createMeshFromFile(const wchar_t* filePath)
	{
		return std::static_pointer_cast<Mesh>(createResourceFromFile(filePath));
	}

	MeshPtr MeshManager::createMeshFromPrimitiveType(const PrimitiveType type)
	{
		if (const auto it = resourceMap.find(toString(type)); it != resourceMap.end())
			return std::static_pointer_cast<Mesh>(it->second);

		MeshPtr newMesh = std::make_shared<Mesh>(type);
		resourceMap[toString(type)] = newMesh;
		return newMesh;
	}

	Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* filePath)
	{
		Mesh* mesh = nullptr;
		try
		{
			mesh = new Mesh(filePath);
		}
		catch (std::exception& e)
		{
			throw;
		}

		return mesh;
	}
}
