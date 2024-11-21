#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "Prerequisites.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

class Renderer3D;

class Material
{
public:
	explicit Material(PixelShaderPtr pixelShader);

	/**
	 * Passing a string will get the shader specified.
	 * @param pixelShaderName The filename of the shader.
	 */
	explicit Material(const std::wstring& pixelShaderName);

	PixelShaderPtr getPixelShader() const;

private:
	PixelShaderPtr pixelShader = nullptr;

	Vector4D color = {1, 1, 1, 1};

	TexturePtr albedoTexture = nullptr;
	TexturePtr metallicTexture = nullptr;
	TexturePtr smoothnessTexture = nullptr;
	TexturePtr normalTexture = nullptr;

	SamplerStatePtr samplerState = nullptr;

	float metallic = 0;
	float smoothness = 0;
	float flatness = 0;

	Vector2D tiling = 0;
	Vector2D offset = 0;

	friend class MaterialEditor;
	friend class DeviceContext;
	friend class AppWindow;
	friend class Renderer3D;
};

