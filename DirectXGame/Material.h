#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "Prerequisites.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

namespace gdeng03
{
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
		void setAlbedo(const TexturePtr& albedo);

	private:
		void setToDefaultTextures();

		PixelShaderPtr pixelShader = nullptr;

		Vector4D color = { 1, 1, 1, 1 };

		TexturePtr albedoTexture = nullptr;
		TexturePtr metallicTexture = nullptr;
		TexturePtr smoothnessTexture = nullptr;
		TexturePtr normalTexture = nullptr;

		SamplerStatePtr samplerState = nullptr;

		float metallic = 1;
		float smoothness = 1;
		float flatness = 1;

		Vector2D tiling = 0;
		Vector2D offset = 0;

		friend class MaterialEditor;
		friend class InspectorScreen;
		friend class DeviceContext;
		friend class AppWindow;
		friend class Renderer3D;
	};
}

