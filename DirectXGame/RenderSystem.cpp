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

#include "LogUtils.h"

RenderSystem::RenderSystem()
= default;

RenderSystem::~RenderSystem()
= default;

bool RenderSystem::init()
{
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	constexpr UINT numDriverTypes = ARRAYSIZE(driverTypes);

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

	if (FAILED(res))
		return false;

	immDeviceContext = new DeviceContext(immContext, this);

	LogUtils::log(this, directXDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice)));
	LogUtils::log(this, dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter)));
	LogUtils::log(this, dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgiFactory)));

	return true;
}

bool RenderSystem::release() const
{
	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();

	//immDeviceContext->release();
	delete immDeviceContext;

	immContext->Release();
	directXDevice->Release();

	return true;
}

SwapChain* RenderSystem::createSwapChain(const HWND windowHandle, const UINT width, const UINT height)
{
	try { return new SwapChain(windowHandle, width, height, this); }
	catch (...) { return nullptr; }
}

DeviceContext* RenderSystem::getImmediateDeviceContext() const
{
	return this->immDeviceContext;
}

VertexBuffer* RenderSystem::createVertexBuffer(
	const void* listVertices,
	const UINT sizeVertex,
	const UINT sizeList,
	const void* shaderByteCode,
	const UINT sizeByteShader)
{

	try { return new VertexBuffer(listVertices, sizeVertex, sizeList, shaderByteCode, sizeByteShader, this); }
	catch (...) { return nullptr; }
}

IndexBuffer* RenderSystem::createIndexBuffer(const void* listIndices, const UINT sizeList)
{
	try { return new IndexBuffer(listIndices, sizeList, this); }
	catch (...) { return nullptr; }
}

ConstantBuffer* RenderSystem::createConstantBuffer(const void* buffer, const UINT sizeBuffer)
{
	try { return new ConstantBuffer(buffer, sizeBuffer, this); }
	catch (...) { return nullptr; }
}

VertexShader* RenderSystem::createVertexShader(const void* shaderByteCode, const size_t byteCodeSize)
{
	try { return new VertexShader(shaderByteCode, byteCodeSize, this); }
	catch (...) { return nullptr; }
}

PixelShader* RenderSystem::createPixelShader(const void* shaderByteCode, const size_t byteCodeSize)
{
	try { return new PixelShader(shaderByteCode, byteCodeSize, this); }
	catch (...) { return nullptr; }
}

GeometryShader* RenderSystem::createGeometryShader(const void* shaderByteCode, const size_t byteCodeSize)
{
	try { return new GeometryShader(shaderByteCode, byteCodeSize, this); }
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

bool RenderSystem::compileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shader_byte_code, size_t* byte_code_size)
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

	*shader_byte_code = blob->GetBufferPointer();
	*byte_code_size = blob->GetBufferSize();

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