#pragma once
#include "Texture.h"
#include <wrl/client.h>
#include <d3d11.h>

class TextureLoader
{
public:
    static bool loadTexture(ID3D11Device* device, const wchar_t* file_path, Texture& texture);
};