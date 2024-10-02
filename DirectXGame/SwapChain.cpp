#include "SwapChain.h"
#include "DeviceContext.h"
#include "GraphicsEngine.h"

SwapChain::SwapChain()
{
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::getInstance()->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 2;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	if (!device) {
		MessageBox(hwnd, L"Direct3D device is not initialized.", L"Error", MB_OK);
		return false;
	}

	if (!GraphicsEngine::getInstance()->m_dxgi_factory) {
		MessageBox(hwnd, L"DXGI factory is not initialized.", L"Error", MB_OK);
		return false;
	}

	//Create the swap chain for the window indicated by HWND parameter
	HRESULT hr = GraphicsEngine::getInstance()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(hr))
	{
		// Log the error message
		MessageBox(hwnd, L"Failed to create swap chain.", L"Error", MB_OK);
		return false;
	}


	//Get the back buffer color and create its render target view
	//--------------------------------
	ID3D11Texture2D* buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();

	if (SUCCEEDED(hr)) {
		hr = GraphicsEngine::getInstance()->getD3DDevice()->CreateRenderTargetView(buffer, nullptr, &m_rtv);
		buffer->Release();  // Release the back buffer after use
	}


	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool SwapChain::present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);

	return true;
}

bool SwapChain::release()
{
	if (m_swap_chain)m_swap_chain->Release();
	return true;
}

SwapChain::~SwapChain()
{
}