#include "MaterialEditor.h"

#include <algorithm>

#include "GraphicsEngine.h"
#include "Material.h"
#include "UIManager.h"

MaterialEditor::MaterialEditor() : UIScreen("MenuScreen")
{
	LogUtils::logHResult(
		this,
		DirectX::CreateWICTextureFromFile(
			GraphicsEngine::get()->getRenderSystem()->getDevice(),
			L"images/texScratchyMetal_1.png",
			nullptr,
			albedoTexture.ReleaseAndGetAddressOf()));
	LogUtils::logHResult(
		this,
		DirectX::CreateWICTextureFromFile(
			GraphicsEngine::get()->getRenderSystem()->getDevice(),
			L"images/texScratchyMetal_1_m.png",
			nullptr,
			metallicTexture.ReleaseAndGetAddressOf()));
	LogUtils::logHResult(
		this,
		DirectX::CreateWICTextureFromFile(
			GraphicsEngine::get()->getRenderSystem()->getDevice(),
			L"images/texScratchyMetal_1_s.png",
			nullptr,
			smoothnessTexture.ReleaseAndGetAddressOf()));
	LogUtils::logHResult(
		this,
		DirectX::CreateWICTextureFromFile(
			GraphicsEngine::get()->getRenderSystem()->getDevice(),
			L"images/texScratchyMetal_1_n.png",
			nullptr,
			normalTexture.ReleaseAndGetAddressOf()));
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
		if (ImGui::ImageButton("Albedo Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(albedoTexture.Get())), imageSize))
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
			albedoTexture.Reset();
		}

		ImGui::NewLine();

		//slider size
		ImGui::PushItemWidth(250);

		//metallic
		ImGui::Text("Metallic Map");
		if (ImGui::ImageButton("Metallic Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(metallicTexture.Get())), imageSize))
		{
			loadTextureFile(metallicTexture);
		}
		ImGui::SameLine();
		ImGui::SliderFloat("Metallic", &metallic, 0, 1);
		if (ImGui::Button("Clear Metallic"))
		{
			metallicTexture.Reset();
		}

		ImGui::NewLine();

		//smoothness
		ImGui::Text("Smoothness Map");
		if (ImGui::ImageButton("Smoothness Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(smoothnessTexture.Get())), imageSize))
		{
			loadTextureFile(smoothnessTexture);
		}
		ImGui::SameLine();
		ImGui::SliderFloat("Smoothness", &smoothness, 0, 1);
		if(ImGui::Button("Clear Smoothness"))
		{
			smoothnessTexture.Reset();
		}

		ImGui::NewLine();

		//albedo
		ImGui::Text("Normal Map");
		if (ImGui::ImageButton("Normal Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(normalTexture.Get())), imageSize))
		{
			loadTextureFile(normalTexture);
		}
		ImGui::SameLine();
		ImGui::SliderFloat("Flatness", &flatness, 0, 1);
		if (ImGui::Button("Clear Normal"))
		{
			normalTexture.Reset();
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

void MaterialEditor::loadTextureFile(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& texture)
{
	//create file object instance
	if (!LogUtils::logHResult(this, CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
	{
		return;
	}

	//create fileopnedialogue object
	IFileOpenDialog* f_FileSystem;
	if (!LogUtils::logHResult(this, CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&f_FileSystem))))
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
	HRESULT fileSelect = f_FileSystem->Show(NULL);
	if (FAILED(fileSelect))
	{
		LogUtils::log(this, "Texture load cancelled");
		f_FileSystem->Release();
		CoUninitialize();
		return;
	}

	//retrieve file name from selected item
	IShellItem* f_Files;
	if (!LogUtils::logHResult(this, f_FileSystem->GetResult(&f_Files)))
	{
		f_FileSystem->Release();
		CoUninitialize();
		return;
	}

	//store and convert file name
	PWSTR f_Path;
	if (!LogUtils::logHResult(this, f_Files->GetDisplayName(SIGDN_FILESYSPATH, &f_Path)))
	{
		f_Files->Release();
		f_FileSystem->Release();
		CoUninitialize();
		return;
	}

	//format and store file path
	std::wstring path(f_Path);
	std::replace(path.begin(), path.end(), L'\\', L'/');
	const wchar_t* w_path = path.c_str();

	//create texture from file
	if (!LogUtils::logHResult(
		this,
		DirectX::CreateWICTextureFromFile(
			GraphicsEngine::get()->getRenderSystem()->getDevice(),
			w_path,
			nullptr,
			texture.ReleaseAndGetAddressOf())))
	{
		LogUtils::log(this, "Texture load failed");
		LogUtils::log(this, std::string(path.begin(), path.end()));
	}
	else
	{
		LogUtils::log(this, "Texture load success");
		LogUtils::log(this, std::string(path.begin(), path.end()));
	}


	CoTaskMemFree(f_Path);
	f_Files->Release();
	f_FileSystem->Release();
	CoUninitialize();
}