#include "MeshManager.h"

namespace gdeng03
{
	MeshPtr MeshManager::createMeshFromFile(const wchar_t* filePath)
	{
		return std::static_pointer_cast<Mesh>(createResourceFromFile(filePath));
	}

	MeshPtr MeshManager::createMeshFromPrimitiveType(const PrimitiveType type)
	{
		ResourcePtr returnResource = nullptr;
		if (const auto it = resourceMap.find(toString(type)); it != resourceMap.end())
			returnResource = it->second;

		if (Resource* raw = this->createResourceFromFileConcrete(toString(type)))
		{
			const ResourcePtr res(raw);
			resourceMap[toString(type)] = res;
			returnResource = res;
		}

		if (!returnResource)
			LogUtils::error(this, "Mesh resource is null!");

		return std::static_pointer_cast<Mesh>(returnResource);
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
