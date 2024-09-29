#include "TextureLoader.h"

bool TextureLoader::loadTexture(ID3D11Device* device, const wchar_t* file_path, Texture& texture)
{
    return texture.init(device, file_path);
}