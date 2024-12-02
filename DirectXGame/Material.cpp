#include "Material.h"

#include <utility>

#include "GraphicsEngine.h"
#include "ShaderLibrary.h"

namespace gdeng03
{
	Material::Material(PixelShaderPtr pixelShader) : pixelShader(std::move(pixelShader))
	{
		samplerState = GraphicsEngine::get()->getRenderSystem()->createSamplerState();
		setToDefaultTextures();
		// albedoTexture = nullptr;
		// metallicTexture = nullptr;
		// smoothnessTexture = nullptr;
		// normalTexture = nullptr;
	}

	Material::Material(const std::wstring& pixelShaderName)
	{
		samplerState = GraphicsEngine::get()->getRenderSystem()->createSamplerState();
		pixelShader = ShaderLibrary::get()->getPixelShader(pixelShaderName);
		// albedoTexture = nullptr;
		// metallicTexture = nullptr;
		// smoothnessTexture = nullptr;
		// normalTexture = nullptr;
		setToDefaultTextures();

		// void* shaderByteCode = nullptr;
		// size_t byteCodeSize = 0;
		//
		// std::string append = pixelShaderName;
		// const std::wstring widestr = std::wstring(append.begin(), append.end());
		//
		// LogUtils::log(this, "Pixel shader compilation");
		// GraphicsEngine::get()->getRenderSystem()->compilePixelShader(widestr.c_str(), "main", &shaderByteCode, &byteCodeSize);
		// pixelShader = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shaderByteCode, byteCodeSize);
		// GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
	}

	PixelShaderPtr Material::getPixelShader() const
	{
		return pixelShader;
	}

	void Material::setAlbedo(const TexturePtr& albedo)
	{
		albedoTexture = albedo;
	}

	void Material::setToDefaultTextures()
	{
		color = { 1, 1, 1, 1 };
		albedoTexture = GraphicsEngine::get()->getTextureManager()->getBlankTexture();
		metallicTexture = GraphicsEngine::get()->getTextureManager()->getBlankTexture();
		smoothnessTexture = GraphicsEngine::get()->getTextureManager()->getBlankTexture();
		normalTexture = GraphicsEngine::get()->getTextureManager()->getBlankTexture();

	}
}
