#include "Texture.h"
#include <fstream>
#include <vector>

Texture::Texture() {}

Texture::~Texture()
{
    release();
}

bool Texture::init(ID3D11Device* device, const wchar_t* file_path)
{
    // Simplified image loading (could be replaced with custom or a library for specific formats)
    // Example of a raw texture loader: assume a .raw file containing only RGB or RGBA bytes
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return false;

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) return false;

    // For simplicity, assume we are loading a fixed size texture (e.g., 256x256 RGBA)
    D3D11_TEXTURE2D_DESC texture_desc = {};
    texture_desc.Width = 256; // Assuming 256x256 image
    texture_desc.Height = 256;
    texture_desc.MipLevels = 1;
    texture_desc.ArraySize = 1;
    texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // Assuming RGBA
    texture_desc.SampleDesc.Count = 1;
    texture_desc.Usage = D3D11_USAGE_DEFAULT;
    texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = buffer.data();
    init_data.SysMemPitch = 256 * 4; // Row pitch: width * bytes per pixel (4 for RGBA)

    HRESULT hr = device->CreateTexture2D(&texture_desc, &init_data, m_texture.GetAddressOf());
    if (FAILED(hr)) return false;

    D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
    srv_desc.Format = texture_desc.Format;
    srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srv_desc.Texture2D.MostDetailedMip = 0;
    srv_desc.Texture2D.MipLevels = texture_desc.MipLevels;

    hr = device->CreateShaderResourceView(m_texture.Get(), &srv_desc, m_shader_resource_view.GetAddressOf());
    if (FAILED(hr)) return false;

    return true;
}

void Texture::bind(ID3D11DeviceContext* device_context, UINT slot)
{
    device_context->PSSetShaderResources(slot, 1, m_shader_resource_view.GetAddressOf());
}

void Texture::release()
{
    m_texture.Reset();
    m_shader_resource_view.Reset();
}
