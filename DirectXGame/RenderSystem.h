#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();
	RenderSystem(const RenderSystem& obj) = default;
	RenderSystem(RenderSystem&& other) noexcept = default;
	RenderSystem& operator=(const RenderSystem& other) = default;
	RenderSystem& operator=(RenderSystem&& other) noexcept = default;

	//bool init();
	//bool release() const;

	DeviceContextPtr getImmediateDeviceContext() const;
	ID3D11Device* getDevice() const;

	SwapChainPtr createSwapChain(HWND windowHandle, UINT width, UINT height);
	VertexBufferPtr createVertexBuffer(const void* listVertices, UINT sizeVertex, UINT sizeList, const void* shaderByteCode, UINT sizeByteShader);
	IndexBufferPtr createIndexBuffer(const void* listIndices, UINT sizeList);
	ConstantBufferPtr createConstantBuffer(const void* buffer, UINT sizeBuffer);
	VertexShaderPtr createVertexShader(const void* shaderByteCode, size_t byteCodeSize);
	PixelShaderPtr createPixelShader(const void* shaderByteCode, size_t byteCodeSize);
	GeometryShaderPtr createGeometryShader(const void* shaderByteCode, size_t byteCodeSize);

	bool compileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	bool compilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	bool compileGeometryShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	void releaseCompiledShader() const;

private:
	DeviceContextPtr immDeviceContext = nullptr;

	ID3D11Device* directXDevice = nullptr;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11DeviceContext* immContext = nullptr;

	IDXGIDevice* dxgiDevice = nullptr;
	IDXGIAdapter* dxgiAdapter = nullptr;
	IDXGIFactory* dxgiFactory = nullptr;

	ID3DBlob* blob = nullptr;

	ID3DBlob* vertexShaderBlob = nullptr;
	ID3DBlob* pixelShaderBlob = nullptr;
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;

	friend class SwapChain;
	friend class VertexBuffer;
	friend class IndexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class GeometryShader;
};

