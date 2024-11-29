#pragma once

#include <d3d11.h>

namespace mrlol
{
    class RenderTexture
    {
    private:
        ID3D11Texture2D* renderTarget = nullptr;
        ID3D11RenderTargetView* renderTargetView = nullptr;
        ID3D11ShaderResourceView* shaderResourceView = nullptr;
        ID3D11DepthStencilView* depthStencilView = nullptr;

        size_t width;
        size_t height;

    private:
        friend class DeviceContext;
        friend class SwapChain;

    public:
        RenderTexture();
        ~RenderTexture();

        void resizeResources(size_t newWidth, size_t newHeight);

        ID3D11Texture2D* getRenderTarget() const;
        ID3D11RenderTargetView* getRenderTargetView() const;
        ID3D11ShaderResourceView* getShaderResourceView() const;
    };
}