#include "ShaderLibrary.h"

#include "GraphicsEngine.h"
#include "ShaderToCompile.h"

namespace gdeng03
{
	ShaderLibrary* ShaderLibrary::sharedInstance = nullptr;

	void ShaderLibrary::requestVertexShaderData(const std::wstring& name, void** shaderByteCode, size_t* byteCodeSize)
	{
		GraphicsEngine::get()->getRenderSystem()->compileVertexShader(name.c_str(), "main", shaderByteCode, byteCodeSize);
	}

	VertexShaderPtr ShaderLibrary::getVertexShader(const std::wstring& name)
	{
		if (activeVS[name])
			return activeVS[name];

		LogUtils::error(this, "Vertex shader does not exist!");
		return nullptr;
	}

	GeometryShaderPtr ShaderLibrary::getGeometryShader(const std::wstring& name)
	{
		if (activeGS[name])
			return activeGS[name];

		LogUtils::error(this, "Geometry shader does not exist!");
		return nullptr;
	}

	PixelShaderPtr ShaderLibrary::getPixelShader(const std::wstring& name)
	{
		if (activePS[name])
			return activePS[name];

		LogUtils::error(this, "Pixel shader does not exist!");
		return nullptr;
	}

	ShaderLibrary::ShaderLibrary()
	{
		ShaderToCompile shaderInitializationList[] = {
			{ShaderType::VERTEX, L"VertexShader.hlsl"},
			{ShaderType::VERTEX, L"VertexMeshLayoutShader.hlsl"},
			{ShaderType::VERTEX, L"DebugRendererVertexShader.hlsl"},
			//{ShaderType::GEOMETRY, L"GeometryShader.hlsl"},
			{ShaderType::PIXEL, L"PixelShader.hlsl"},
			{ShaderType::PIXEL, L"DebugRendererPixelShader.hlsl"},
			// !! ADD MORE SHADERS HERE !! 
		};

		for (const auto& [type, name] : shaderInitializationList)
		{
			void* shaderByteCode = nullptr;
			size_t byteCodeSize = 0;

			switch (type)
			{
			case ShaderType::VERTEX:
			{
				GraphicsEngine::get()->getRenderSystem()->compileVertexShader(name.c_str(), "main", &shaderByteCode, &byteCodeSize);
				activeVS[name] = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shaderByteCode, byteCodeSize);
				//GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
				break;
			}
			case ShaderType::GEOMETRY:
			{
				GraphicsEngine::get()->getRenderSystem()->compileGeometryShader(name.c_str(), "main", &shaderByteCode, &byteCodeSize);
				activeGS[name] = GraphicsEngine::get()->getRenderSystem()->createGeometryShader(shaderByteCode, byteCodeSize);
				break;
			}
			case ShaderType::PIXEL:
			{
				GraphicsEngine::get()->getRenderSystem()->compilePixelShader(name.c_str(), "main", &shaderByteCode, &byteCodeSize);
				activePS[name] = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shaderByteCode, byteCodeSize);
				break;
			}
			}
		}

		LogUtils::log(this, "All shaders initialized.");
	}

	ShaderLibrary::~ShaderLibrary()
	{
		// smart pointers will release on their own
		activeVS.clear();
		activeGS.clear();
		activePS.clear();
	}
}
