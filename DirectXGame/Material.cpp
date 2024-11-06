#include "Material.h"

#include "GraphicsEngine.h"

Material::Material(PixelShaderPtr pixelShader) : pixelShader(pixelShader)
{
}

Material::Material(const std::string& pixelShaderName)
{
	void* shaderByteCode = nullptr;
	size_t byteCodeSize = 0;

	std::string append = pixelShaderName + ".hlsl";
	const std::wstring widestr = std::wstring(append.begin(), append.end());

	LogUtils::log(this, "Pixel shader compilation");
	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(widestr.c_str(), "main", &shaderByteCode, &byteCodeSize);
	pixelShader = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shaderByteCode, byteCodeSize);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
}

PixelShaderPtr Material::getPixelShader() const
{
	return pixelShader;
}
