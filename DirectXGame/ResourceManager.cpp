#include "ResourceManager.h"

#if __cplusplus <= 201402L 
// ReSharper disable once CppInconsistentNaming (C++ standard version check)
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#if __cplusplus >= 201703L
#include <filesystem>
#endif

ResourcePtr ResourceManager::createResourceFromFile(const wchar_t* filePath)
{

#if (_MSC_VER >= 1900 && _MSC_VER <= 1916)  || ( _MSC_VER >= 1920 && __cplusplus <= 201402L) 
	const std::wstring fullPath = std::experimental::filesystem::absolute(filePath);
#endif

#if _MSC_VER >= 1920 && __cplusplus > 201402L 
	std::wstring full_path = std::filesystem::absolute(file_path);
#endif

	if (const auto it = resourceMap.find(fullPath); it != resourceMap.end())
		return it->second;

	if (Resource* raw = this->createResourceFromFileConcrete(fullPath.c_str()))
	{
		ResourcePtr res(raw);
		resourceMap[fullPath] = res;
		return res;
	}

	return nullptr;
}
