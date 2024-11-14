#include "TextureManager.h"

#include "Texture.h"

TexturePtr TextureManager::createTextureFromFile(const wchar_t* filePath)
{
	return std::static_pointer_cast<Texture>(createResourceFromFile(filePath));
}

Resource* TextureManager::createResourceFromFileConcrete(const wchar_t* filePath)
{
	Texture* tex = nullptr;
	try
	{
		tex = new Texture(filePath);
	}
	catch (...)
	{
		throw std::exception("Failed to create texture!");
	}

	return tex;
}