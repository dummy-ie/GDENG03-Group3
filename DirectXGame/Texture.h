#pragma once
#include <d3d11.h>
#include <wrl/client.h>  // For Microsoft::WRL::ComPtr

class Texture
{
public:
    Texture();
    ~Texture();

    bool init(ID3D11Device* device, const wchar_t* file_path); // Loads texture from file
    void bind(ID3D11DeviceContext* device_context, UINT slot = 0); // Binds the texture to the pipeline
    void release();

private:
    Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shader_resource_view;
};
