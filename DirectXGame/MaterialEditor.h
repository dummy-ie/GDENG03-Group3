#pragma once

#include <wrl/client.h>
#include "WICTextureLoader.h"
#include "DirectXHelpers.h"
#include <string>
#include <shobjidl.h> 
#include <vector>

#include "UIScreen.h"
#include "Vector2D.h"

class MenuScreen;

class MaterialEditor :
    public UIScreen
{
public:
    MaterialEditor();
    bool* getMaterialEditorOpen();

private:
    void draw() override;
    void showColorPickerWindow();
    void updateSelectedMaterial() const;
    void showMaterialEditorWindow();

    std::vector<unsigned char> getPixelData(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& texture);
    bool isNormalImage(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& texture);

    void loadTextureFile(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> &texture);

    bool isColorPickerOpen = false;
    bool isMaterialEditorOpen = false;

    ImVec4 color = ImVec4(1,1,1,1);
    float metallic = 0;
    float smoothness = 0;
    float flatness = 0;
    Vector2D tiling = { 1,1 };
    Vector2D offset = { 0,0 };

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> albedoTexture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> metallicTexture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> smoothnessTexture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> normalTexture;

    friend class MenuScreen;
};

