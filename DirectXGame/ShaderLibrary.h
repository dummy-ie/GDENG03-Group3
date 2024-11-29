#pragma once
#include <string>
#include <unordered_map>
#include "Prerequisites.h"

namespace mrlol
{
	// class VertexShader;
	// class GeometryShader;
	// class PixelShader;

	class ShaderLibrary
	{
	public:
		typedef std::unordered_map<std::wstring, VertexShaderPtr> VSMap;
		typedef std::unordered_map<std::wstring, GeometryShaderPtr> GSMap;
		typedef std::unordered_map<std::wstring, PixelShaderPtr> PSMap;

		static void requestVertexShaderData(const std::wstring& name, void** shaderByteCode, size_t* byteCodeSize);
		VertexShaderPtr getVertexShader(const std::wstring& name);
		GeometryShaderPtr getGeometryShader(const std::wstring& name);
		PixelShaderPtr getPixelShader(const std::wstring& name);

	private:
		VSMap activeVS;
		GSMap activeGS;
		PSMap activePS;

		// Singleton
	public:
		static ShaderLibrary* get()
		{
			if (!sharedInstance)
				sharedInstance = new ShaderLibrary();

			return sharedInstance;
		}

		ShaderLibrary(ShaderLibrary const&) = delete;
		ShaderLibrary& operator=(ShaderLibrary const&) = delete;
		ShaderLibrary(ShaderLibrary&& other) noexcept = delete;
		ShaderLibrary& operator=(ShaderLibrary&& other) noexcept = delete;

	private:
		ShaderLibrary();
		~ShaderLibrary();
		static ShaderLibrary* sharedInstance;
	};
}

