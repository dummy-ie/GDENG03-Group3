#pragma once

#include <d3d11.h>
#include "Prerequisites.h"
#include "Vector2D.h"
#include "Vector3D.h"

class Material
{
	typedef std::shared_ptr<ID3D11Texture2D> TexturePtr;

public:
	Material(PixelShaderPtr pixelShader);

	/**
	 * Passing a string will build the shader specified.
	 * @param pixelShaderName The filename of the shader.
	 */
	Material(const std::string& pixelShaderName);

	PixelShaderPtr getPixelShader();

private:
	PixelShaderPtr pixelShader = nullptr;

	TexturePtr albedo = nullptr;
	Vector3D rgb = 0;

	TexturePtr normalMap = nullptr;

	float metallic = 0;
	float smoothness = 0;

	Vector2D tiling = 0;
	Vector2D offset = 0;
};

