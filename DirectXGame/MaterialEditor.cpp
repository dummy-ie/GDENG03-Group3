#include "MaterialEditor.h"

#include <algorithm>

#include "GraphicsEngine.h"
#include "Material.h"
#include "Texture.h"
#include "TextureManager.h"
#include "UIManager.h"

using namespace mrlol;

MaterialEditor::MaterialEditor() : UIScreen("MaterialEditor")
{
	albedoTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"assets/images/texScratchyMetal_1.png");
	metallicTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"assets/images/texScratchyMetal_1_m.png");
	smoothnessTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"assets/images/texScratchyMetal_1_s.png");
	normalTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"assets/images/texScratchyMetal_1_n.png");

}

bool* MaterialEditor::getMaterialEditorOpen()
{
	return &isMaterialEditorOpen;
}

void MaterialEditor::draw()
{
	if (isColorPickerOpen && !isMaterialEditorOpen)
		isColorPickerOpen = false;

	if (isColorPickerOpen)
		showColorPickerWindow();

	if (isMaterialEditorOpen)
		showMaterialEditorWindow();

	updateSelectedMaterial();
}

void MaterialEditor::showColorPickerWindow()
{
	if (ImGui::Begin("Color Picker", &isColorPickerOpen))
	{
		ImGui::SameLine();
		ImGui::ColorPicker4("Albedo Color##4", reinterpret_cast<float*>(&color), 0);
	}
	ImGui::End();
}

void MaterialEditor::updateSelectedMaterial() const
{
	// Ideally, the material being edited is picked by the selected gameobject, but we don't have object picking yet
	const std::shared_ptr<Material> currentMaterial = UIManager::get()->mainMaterial;

	currentMaterial->color = { this->color.x, this->color.y, this->color.z, this->color.w };

	currentMaterial->albedoTexture = this->albedoTexture;
	currentMaterial->metallicTexture = this->metallicTexture;
	currentMaterial->smoothnessTexture = this->smoothnessTexture;
	currentMaterial->normalTexture = this->normalTexture;

	currentMaterial->metallic = this->metallic;
	currentMaterial->smoothness = this->smoothness;
	currentMaterial->flatness = this->flatness;

	currentMaterial->tiling = this->tiling;
	currentMaterial->offset = this->offset;
}

void MaterialEditor::showMaterialEditorWindow()
{
	if (ImGui::Begin("Material Editor", &isMaterialEditorOpen))
	{
		ImGui::Text("Main Maps");
		constexpr ImVec2 imageSize = { 100, 100 };
		//albedo
		ImGui::Text("Albedo Map");
		if (ImGui::ImageButton("Albedo Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(albedoTexture->getShaderResourceView())), imageSize))
		{
			loadTextureFile(albedoTexture);
		}
		ImGui::SameLine();
		if (ImGui::ColorButton("Color", color, 0, ImVec2(50, 30)))
		{
			isColorPickerOpen = !isColorPickerOpen;
		}
		if (ImGui::Button("Clear Albedo"))
		{
			loadBlankTexture(albedoTexture);
		}

		ImGui::NewLine();

		//slider size
		ImGui::PushItemWidth(250);

		//metallic
		ImGui::Text("Metallic Map");
		if (ImGui::ImageButton("Metallic Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(metallicTexture->getShaderResourceView())), imageSize))
		{
			loadTextureFile(metallicTexture);
		}
		ImGui::SameLine();
		ImGui::SliderFloat("Metallic", &metallic, 0, 1);
		if (ImGui::Button("Clear Metallic"))
		{
			loadBlankTexture(metallicTexture);
		}

		ImGui::NewLine();

		//smoothness
		ImGui::Text("Smoothness Map");
		if (ImGui::ImageButton("Smoothness Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(smoothnessTexture->getShaderResourceView())), imageSize))
		{
			loadTextureFile(smoothnessTexture);
		}
		ImGui::SameLine();
		ImGui::SliderFloat("Smoothness", &smoothness, 0, 1);
		if (ImGui::Button("Clear Smoothness"))
		{
			loadBlankTexture(smoothnessTexture);
		}

		ImGui::NewLine();

		//albedo
		ImGui::Text("Normal Map");
		if (ImGui::ImageButton("Normal Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(normalTexture->getShaderResourceView())), imageSize))
		{
			loadTextureFile(normalTexture);
			if (!isNormalImage(normalTexture))
			{
				loadBlankTexture(normalTexture);
			}
		}
		ImGui::SameLine();
		ImGui::SliderFloat("Flatness", &flatness, 0, 1);
		if (ImGui::Button("Clear Normal"))
		{
			loadBlankTexture(normalTexture);
		}

		ImGui::NewLine();

		//input field size
		ImGui::PushItemWidth(125);

		//tiling
		ImGui::Text("Tiling");
		//x
		ImGui::Text("X"); ImGui::SameLine(40);
		ImGui::PushItemWidth(225);
		ImGui::SliderFloat("##TilingXSlider", &tiling.x, -20, 20); ImGui::SameLine();
		ImGui::PushItemWidth(125);
		ImGui::InputFloat("##Tiling X", &tiling.x);
		//y
		ImGui::Text("Y"); ImGui::SameLine(40);
		ImGui::PushItemWidth(225);
		ImGui::SliderFloat("##TilingYSlider", &tiling.y, -20, 20); ImGui::SameLine();
		ImGui::PushItemWidth(125);
		ImGui::InputFloat("##Tiling Y", &tiling.y);

		ImGui::NewLine();

		//offset
		ImGui::Text("Offset");
		//x
		ImGui::Text("X"); ImGui::SameLine(40);
		ImGui::PushItemWidth(225);
		ImGui::SliderFloat("##OffsetXSlider", &offset.x, -20, 20); ImGui::SameLine();
		ImGui::PushItemWidth(125);
		ImGui::InputFloat("##Offset X", &offset.x);
		//y
		ImGui::Text("Y"); ImGui::SameLine(40);
		ImGui::PushItemWidth(225);
		ImGui::SliderFloat("##OffsetYSlider", &offset.y, -20, 20); ImGui::SameLine();
		ImGui::PushItemWidth(125);
		ImGui::InputFloat("##Offset Y", &offset.y);

		ImGui::PopItemWidth();
	}
	ImGui::End();
}

std::vector<unsigned char> MaterialEditor::getPixelData(const TexturePtr& texture)
{
	std::vector<unsigned char> pixelData;

	if (!texture) return pixelData;

	//get the texture resource from the shader resource view
	const Microsoft::WRL::ComPtr<ID3D11Resource> resource = texture->getResource();

	//get the texture description
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	if (FAILED(resource.As(&texture2D))) return pixelData;

	D3D11_TEXTURE2D_DESC textureDesc;
	texture2D->GetDesc(&textureDesc);

	//create a staging texture for cpu access
	textureDesc.Usage = D3D11_USAGE_STAGING;
	textureDesc.BindFlags = 0;
	textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	textureDesc.MiscFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> stagingTexture;
	if (const HRESULT hr = GraphicsEngine::get()->getRenderSystem()->getDevice()->CreateTexture2D(&textureDesc, nullptr, &stagingTexture); FAILED(hr))
		return pixelData;

	//copy the original texture to the staging texture
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->copyResource(stagingTexture.Get(), resource.Get());

	//map the staging texture for reading
	D3D11_MAPPED_SUBRESOURCE mappedData;
	if (!GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->mapResource(stagingTexture.Get(), mappedData, 0, D3D11_MAP_READ, 0)) {
		return pixelData;
	}

	//calculate pixel data size and copy it
	const size_t rowPitch = mappedData.RowPitch;
	const size_t dataSize = rowPitch * textureDesc.Height;
	pixelData.resize(dataSize);
	memcpy(pixelData.data(), mappedData.pData, dataSize);

	//unmap the resource
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->unmapResource(stagingTexture.Get(), 0);

	return pixelData;
}

bool MaterialEditor::isNormalImage(const TexturePtr& texture)
{
	const std::vector<unsigned char> pixelData = getPixelData(texture);

	//calculate average blue dominance.
	const int totalPixels = pixelData.size() / 4;
	int blueDominantCount = 0;

	for (int i = 0; i < totalPixels; ++i)
	{
		const int r = pixelData[i * 4];
		const int g = pixelData[i * 4 + 1];
		const int b = pixelData[i * 4 + 2];

		//check if blue is the highest component.
		if (b > r && b > g)
		{
			blueDominantCount++;
		}
	}

	//threshold
	return (blueDominantCount / static_cast<float>(totalPixels)) >= 0.9f;
}

void MaterialEditor::loadTextureFile(TexturePtr& texture)
{
	//create file object instance
	if (!LogUtils::logHResult(this, CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
	{
		return;
	}

	//create fileopnedialogue object
	IFileOpenDialog* f_FileSystem;
	if (!LogUtils::logHResult(this, CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&f_FileSystem))))
	{
		CoUninitialize();
		return;
	}

	COMDLG_FILTERSPEC fileTypes[] = {
		{ L"Image Files", L"*.jpg;*.jpeg;*.png" }
	};

	f_FileSystem->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
	f_FileSystem->SetFileTypeIndex(1);
	f_FileSystem->SetDefaultExtension(L"jpg");

	//this part does NOT like LogUtils::logHResult at all
	//open file dialogue window
	if (const HRESULT fileSelect = f_FileSystem->Show(nullptr); FAILED(fileSelect))
	{
		LogUtils::log(this, "Texture load cancelled");
		f_FileSystem->Release();
		CoUninitialize();
		return;
	}

	//retrieve file name from selected item
	IShellItem* fFiles;
	if (!LogUtils::logHResult(this, f_FileSystem->GetResult(&fFiles)))
	{
		f_FileSystem->Release();
		CoUninitialize();
		return;
	}

	//store and convert file name
	PWSTR fPath;
	if (!LogUtils::logHResult(this, fFiles->GetDisplayName(SIGDN_FILESYSPATH, &fPath)))
	{
		fFiles->Release();
		f_FileSystem->Release();
		CoUninitialize();
		return;
	}

	//format and store file path
	std::wstring path(fPath);
	std::replace(path.begin(), path.end(), L'\\', L'/');
	const wchar_t* wPath = path.c_str();

	//create texture from file
	texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(wPath);

	// if (!LogUtils::logHResult(
	// 	this,
	// 	DirectX::CreateWICTextureFromFile(
	// 		GraphicsEngine::get()->getRenderSystem()->getDevice(),
	// 		w_path,
	// 		nullptr,
	// 		texture)))
	// {
	// 	LogUtils::log(this, "Texture load failed");
	// 	LogUtils::log(this, std::string(path.begin(), path.end()));
	// }
	// else
	// {
	// 	LogUtils::log(this, "Texture load success");
	// 	LogUtils::log(this, std::string(path.begin(), path.end()));
	// }


	CoTaskMemFree(fPath);
	fFiles->Release();
	f_FileSystem->Release();
	CoUninitialize();
}

void MaterialEditor::loadBlankTexture(TexturePtr& texture)
{
	texture.reset();
	texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"assets/images/default_square.png");
}
