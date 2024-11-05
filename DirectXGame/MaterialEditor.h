#pragma once

#include <wrl/client.h>
#include "WICTextureLoader.h"
#include "DirectXHelpers.h"
#include <string>
#include <shobjidl.h> 

#include "UIScreen.h"

class MenuScreen;

class MaterialEditor :
    public UIScreen
{
public:
    MaterialEditor();

private:
    void draw() override;
    void showColorPickerWindow();
    void showMaterialEditorWindow();

    void loadTextureFile(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> &texture);

    bool isColorPickerOpen = false;
    bool isMaterialEditorOpen = true;

    ImVec4 color = ImVec4(1,1,1,1);
    float metallic = 0;
    float smoothness = 0;
    float flatness = 0;
    float tiling[2] = { 1,1 };
    float offset[2] = { 0,0 };

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> albedoTexture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> metallicTexture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> smoothnessTexture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> normalTexture;

    friend class MenuScreen;
};

