#include "RenderSystem.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GeometryShader.h"
#include <d3dcompiler.h>

#include "RasterizerState.h"
#include "SamplerState.h"

namespace gdeng03
{
	RenderSystem::RenderSystem()
	{
		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE
		};

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0
		};
		constexpr UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		HRESULT res = 0;
		for (const auto& driverType : driverTypes)
		{
			res = D3D11CreateDevice(
				nullptr,
				driverType,
				nullptr,
				NULL,
				featureLevels,
				numFeatureLevels,
				D3D11_SDK_VERSION,
				&directXDevice,
				&featureLevel,
				&immContext);

			if (SUCCEEDED(res))
				break;
		}

		LogUtils::logHResult(this, res);

		immDeviceContext = std::make_shared<DeviceContext>(immContext, this);

		LogUtils::logHResult(this, directXDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice)));
		LogUtils::logHResult(this, dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter)));
		LogUtils::logHResult(this, dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgiFactory)));

	}

	RenderSystem::~RenderSystem()
	{
		dxgiDevice->Release();
		dxgiAdapter->Release();
		dxgiFactory->Release();

		immContext->Release();
		directXDevice->Release();

	}

	SwapChainPtr RenderSystem::createSwapChain(const HWND windowHandle, const UINT width, const UINT height)
	{
		try { return std::make_shared<SwapChain>(windowHandle, width, height, this); }
		catch (...) { return nullptr; }
	}

	DeviceContextPtr RenderSystem::getImmediateDeviceContext() const
	{
		return this->immDeviceContext;
	}

	ID3D11Device* RenderSystem::getDevice() const
	{
		return this->directXDevice;
	}

	SamplerStatePtr RenderSystem::createSamplerState()
	{
		try
		{
			return std::make_shared<SamplerState>(this);
		}
		catch (...) { return nullptr; }
	}

	RasterizerStatePtr RenderSystem::createRasterizerState(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode)
	{
		try
		{
			return std::make_shared<RasterizerState>(this, fillMode, cullMode);
		}
		catch (...) { return nullptr; }
	}

	VertexBufferPtr RenderSystem::createVertexBuffer(
		const void* listVertices,
		const UINT sizeVertex,
		const UINT sizeList,
		const void* shaderByteCode,
		const UINT sizeByteShader)
	{

		try { return std::make_shared<VertexBuffer>(listVertices, sizeVertex, sizeList, shaderByteCode, sizeByteShader, this); }
		catch (...) { return nullptr; }
	}

	IndexBufferPtr RenderSystem::createIndexBuffer(const void* listIndices, const UINT sizeList)
	{
		try { return std::make_shared<IndexBuffer>(listIndices, sizeList, this); }
		catch (...) { return nullptr; }
	}

	ConstantBufferPtr RenderSystem::createConstantBuffer(const void* buffer, const UINT sizeBuffer)
	{
		try { return std::make_shared<ConstantBuffer>(buffer, sizeBuffer, this); }
		catch (...) { return nullptr; }
	}

	VertexShaderPtr RenderSystem::createVertexShader(const void* shaderByteCode, const size_t byteCodeSize)
	{
		try { return std::make_shared<VertexShader>(shaderByteCode, byteCodeSize, this); }
		catch (...) { return nullptr; }
	}

	PixelShaderPtr RenderSystem::createPixelShader(const void* shaderByteCode, const size_t byteCodeSize)
	{
		try { return std::make_shared<PixelShader>(shaderByteCode, byteCodeSize, this); }
		catch (...) { return nullptr; }
	}

	GeometryShaderPtr RenderSystem::createGeometryShader(const void* shaderByteCode, const size_t byteCodeSize)
	{
		try { return std::make_shared<GeometryShader>(shaderByteCode, byteCodeSize, this); }
		catch (...) { return nullptr; }
	}

	bool RenderSystem::compileGeometryShader(const wchar_t* fileName, const char* entryPointName,
		void** shaderByteCode, size_t* byteCodeSize)
	{
		ID3DBlob* errorBlob = nullptr;
		if (FAILED(::D3DCompileFromFile(
			fileName,
			nullptr,
			nullptr,
			entryPointName,
			"gs_5_0",
			0,
			0,
			&blob,
			&errorBlob)))
		{
			if (errorBlob)
			{
				LogUtils::error(this, "Geometry shader compilation failed!");
				errorBlob->Release();
			}

			return false;
		}

		*shaderByteCode = blob->GetBufferPointer();
		*byteCodeSize = blob->GetBufferSize();

		return true;
	}

	bool RenderSystem::compileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize)
	{
		ID3DBlob* errorBlob = nullptr;
		if (FAILED(::D3DCompileFromFile(
			fileName,
			nullptr,
			nullptr,
			entryPointName,
			"vs_5_0",
			0,
			0,
			&blob,
			&errorBlob
		)))
		{
			if (errorBlob)
			{
				LogUtils::error(this, "Vertex shader compilation failed!");
				errorBlob->Release();
			}

			return false;
		}

		*shaderByteCode = blob->GetBufferPointer();
		*byteCodeSize = blob->GetBufferSize();

		return true;
	}

	bool RenderSystem::compilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode,
		size_t* byteCodeSize)
	{
		ID3DBlob* errorBlob = nullptr;
		if (FAILED(::D3DCompileFromFile(
			fileName,
			nullptr,
			nullptr,
			entryPointName,
			"ps_5_0",
			0,
			0,
			&blob,
			&errorBlob
		)))
		{
			if (errorBlob)
			{
				LogUtils::error(this, "Pixel shader compilation failed!");
				errorBlob->Release();
			}

			return false;
		}

		*shaderByteCode = blob->GetBufferPointer();
		*byteCodeSize = blob->GetBufferSize();

		return true;
	}

	void RenderSystem::releaseCompiledShader() const
	{
		if (blob)
			blob->Release();
	}
}