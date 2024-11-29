#pragma once

#include "Prerequisites.h"
#include "Resource.h"
#include "ResourceManager.h"

namespace mrlol
{
	class TextureManager final : public ResourceManager
	{
	public:
		TexturePtr createTextureFromFile(const wchar_t* filePath);

	protected:
		Resource* createResourceFromFileConcrete(const wchar_t* filePath) override;
	};
}
