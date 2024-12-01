#pragma once
#include <unordered_map>
#include <string>
#include "Prerequisites.h"
#include "Resource.h"

namespace gdeng03
{
	class ResourceManager
	{
		typedef std::unordered_map<std::wstring, ResourcePtr> ResourceMap;

	public:
		ResourceManager() = default;
		virtual ~ResourceManager() = default;
		ResourceManager(ResourceManager const&) = default;
		ResourceManager& operator=(ResourceManager const&) = default;
		ResourceManager(ResourceManager&& other) noexcept = default;
		ResourceManager& operator=(ResourceManager&& other) noexcept = default;

		ResourcePtr createResourceFromFile(const wchar_t* filePath);

	protected:
		virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath) = 0;

	private:
		ResourceMap resourceMap;

	};
}

