#include "Material.h"

#include <utility>

#include "GraphicsEngine.h"
#include "ShaderLibrary.h"

namespace mrlol
{
	Material::Material(PixelShaderPtr pixelShader) : pixelShader(std::move(pixelShader))
	{
		samplerState = GraphicsEngine::get()->getRenderSystem()->createSamplerState();

	}

	Material::Material(const std::wstring& pixelShaderName)
	{
		samplerState = GraphicsEngine::get()->getRenderSystem()->createSamplerState();
		pixelShader = ShaderLibrary::get()->getPixelShader(pixelShaderName);

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
}
