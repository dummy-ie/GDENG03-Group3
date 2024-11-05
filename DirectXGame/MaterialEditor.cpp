#include "MaterialEditor.h"

#include <algorithm>

#include "GraphicsEngine.h"

MaterialEditor::MaterialEditor() : UIScreen("MenuScreen")
{
	LogUtils::logHResult(
		this,
		DirectX::CreateWICTextureFromFile(
			GraphicsEngine::get()->getRenderSystem()->getDevice(),
			L"images/texWoodBark_1.jpg",
			nullptr,
			albedoTexture.ReleaseAndGetAddressOf()));
	LogUtils::logHResult(
		this,
		DirectX::CreateWICTextureFromFile(
			GraphicsEngine::get()->getRenderSystem()->getDevice(),
			L"images/texWoodBark_1_m.png",
			nullptr,
			metallicTexture.ReleaseAndGetAddressOf()));
	LogUtils::logHResult(
		this,
		DirectX::CreateWICTextureFromFile(
			GraphicsEngine::get()->getRenderSystem()->getDevice(),
			L"images/texWoodBark_1_s.png",
			nullptr,
			smoothnessTexture.ReleaseAndGetAddressOf()));
	LogUtils::logHResult(
		this,
		DirectX::CreateWICTextureFromFile(
			GraphicsEngine::get()->getRenderSystem()->getDevice(),
			L"images/texWoodBark_1_n.png",
			nullptr,
			normalTexture.ReleaseAndGetAddressOf()));
}

void MaterialEditor::draw()
{
	if (isColorPickerOpen)
		showColorPickerWindow();

	if (isMaterialEditorOpen)
		showMaterialEditorWindow();
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

void MaterialEditor::showMaterialEditorWindow()
{
	if (ImGui::Begin("Material Editor", &isMaterialEditorOpen))
	{
		ImGui::Text("Main Maps");
		constexpr ImVec2 imageSize = { 100, 100 };
		//albedo
		ImGui::Text("Albedo Map");
		if(ImGui::ImageButton("Albedo Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(albedoTexture.Get())), imageSize))
		{
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture = loadTextureFile();
			if(texture != nullptr)
			{
				Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> oldTexture = albedoTexture;
				albedoTexture = texture;
				oldTexture->Release();
			}
		}
		ImGui::SameLine();
		if(ImGui::ColorButton("Color", color, 0, ImVec2(50,30)))
		{
			isColorPickerOpen = !isColorPickerOpen;
		}

		ImGui::NewLine();

		//slider size
		ImGui::PushItemWidth(250);

		//metallic
		ImGui::Text("Metallic Map");
		if (ImGui::ImageButton("Metallic Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(metallicTexture.Get())), imageSize))
		{
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture = loadTextureFile();
			if (texture != nullptr)
			{
				Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> oldTexture = metallicTexture;
				metallicTexture = texture;
				oldTexture->Release();
			}
		}
		ImGui::SameLine();
		ImGui::SliderFloat("Metallic", &metallic, 0, 1);

		ImGui::NewLine();

		//smoothness
		ImGui::Text("Smoothness Map");
		if (ImGui::ImageButton("Smoothness Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(smoothnessTexture.Get())), imageSize))
		{
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture = loadTextureFile();
			if (texture != nullptr)
			{
				Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> oldTexture = smoothnessTexture;
				smoothnessTexture = texture;
				oldTexture->Release();
			}
		}
		ImGui::SameLine();
		ImGui::SliderFloat("Smoothness", &smoothness, 0, 1);

		ImGui::NewLine();

		//albedo
		ImGui::Text("Normal Map");
		if (ImGui::ImageButton("Normal Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(normalTexture.Get())), imageSize))
		{
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture = loadTextureFile();
			if (texture != nullptr)
			{
				Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> oldTexture = normalTexture;
				normalTexture = texture;
				oldTexture->Release();
			}
		}
		ImGui::SameLine();
		ImGui::SliderFloat("Flatness", &flatness, 0, 1);

		ImGui::NewLine();

		//input field size
		ImGui::PushItemWidth(125);

		//tiling
		ImGui::Text("Tiling");
		//x
		ImGui::Text("X"); ImGui::SameLine(40);
		ImGui::PushItemWidth(225);
		ImGui::SliderFloat("##TilingXSlider", &tiling[0], -20, 20);ImGui::SameLine();
		ImGui::PushItemWidth(125);
		ImGui::InputFloat("##Tiling X", &tiling[0]);
		//y
		ImGui::Text("Y"); ImGui::SameLine(40);
		ImGui::PushItemWidth(225);
		ImGui::SliderFloat("##TilingYSlider", &tiling[1], -20, 20);ImGui::SameLine();
		ImGui::PushItemWidth(125);
		ImGui::InputFloat("##Tiling Y", &tiling[1]);

		ImGui::NewLine();

		//offset
		ImGui::Text("Offset");
		//x
		ImGui::Text("X"); ImGui::SameLine(40);
		ImGui::PushItemWidth(225);
		ImGui::SliderFloat("##OffsetXSlider", &offset[0], -20, 20);ImGui::SameLine();
		ImGui::PushItemWidth(125);
		ImGui::InputFloat("##Offset X", &offset[0]);
		//y
		ImGui::Text("Y"); ImGui::SameLine(40);
		ImGui::PushItemWidth(225);
		ImGui::SliderFloat("##OffsetYSlider", &offset[1], -20, 20);ImGui::SameLine();
		ImGui::PushItemWidth(125);
		ImGui::InputFloat("##Offset Y", &offset[1]);

		ImGui::PopItemWidth();
	}
	ImGui::End();
}

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> MaterialEditor::loadTextureFile()
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	//create file object instance
	if (!LogUtils::logHResult(this, CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
	{
		return nullptr;
	}

	//create fileopnedialogue object
	IFileOpenDialog* f_FileSystem;
	if (!LogUtils::logHResult(this, CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&f_FileSystem))))
	{
		CoUninitialize();
		return nullptr;
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
		return nullptr;
	}

	//retrieve file name from selected item
	IShellItem* f_Files;
	if (!LogUtils::logHResult(this, f_FileSystem->GetResult(&f_Files)))
	{
		f_FileSystem->Release();
		CoUninitialize();
		return nullptr;
	}

	//store and convert file name
	PWSTR f_Path;
	if (!LogUtils::logHResult(this, f_Files->GetDisplayName(SIGDN_FILESYSPATH, &f_Path)))
	{
		f_Files->Release();
		f_FileSystem->Release();
		CoUninitialize();
		return nullptr;
	}

	//format and store file path
	std::wstring path(f_Path);
	std::replace(path.begin(), path.end(), L'\\', L'/');
	const wchar_t* w_path = path.c_str();

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> oldTexture = texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> newTexture;

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

	return texture;
}

//void MaterialEditor::loadTextureFile(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture)
//{
//	//create file object instance
//	if(!LogUtils::logHResult(this,CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
//	{
//		return;
//	}
//
//	//create fileopnedialogue object
//	IFileOpenDialog* f_FileSystem;
//	if(!LogUtils::logHResult(this,CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&f_FileSystem))))
//	{
//		CoUninitialize();
//		return;
//	}
//
//	COMDLG_FILTERSPEC fileTypes[] = {
//		{ L"Image Files", L"*.jpg;*.jpeg;*.png" }
//	};
//
//	f_FileSystem->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
//	f_FileSystem->SetFileTypeIndex(1);
//	f_FileSystem->SetDefaultExtension(L"jpg");
//
//	//this part does NOT like LogUtils::logHResult at all
//	//open file dialogue window
//	HRESULT fileSelect = f_FileSystem->Show(NULL);
//	if(FAILED(fileSelect))
//	{
//		LogUtils::log(this, "Texture load cancelled");
//		f_FileSystem->Release();
//		CoUninitialize();
//		return;
//	}
//
//	//retrieve file name from selected item
//	IShellItem* f_Files;
//	if(!LogUtils::logHResult(this, f_FileSystem->GetResult(&f_Files)))
//	{
//		f_FileSystem->Release();
//		CoUninitialize();
//		return;
//	}
//
//	//store and convert file name
//	PWSTR f_Path;
//	if (!LogUtils::logHResult(this, f_Files->GetDisplayName(SIGDN_FILESYSPATH, &f_Path)))
//	{
//		f_Files->Release();
//		f_FileSystem->Release();
//		CoUninitialize();
//		return;
//	}
//
//	//format and store file path
//	std::wstring path(f_Path);
//	std::replace(path.begin(), path.end(), L'\\', L'/');
//	const wchar_t* w_path = path.c_str();
//
//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> oldTexture = texture;
//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> newTexture;
//
//	//create texture from file
//	if(!LogUtils::logHResult(
//		this,
//		DirectX::CreateWICTextureFromFile(
//			GraphicsEngine::get()->getRenderSystem()->getDevice(),
//			w_path,
//			nullptr,
//			texture.ReleaseAndGetAddressOf())))
//	{
//		LogUtils::log(this, "Texture load failed");
//		LogUtils::log(this, std::string(path.begin(), path.end()));
//	}
//	else
//	{
//		LogUtils::log(this, "Texture load success");
//		LogUtils::log(this, std::string(path.begin(), path.end()));
//	}
//	
//
//	CoTaskMemFree(f_Path);
//	f_Files->Release();
//	f_FileSystem->Release();
//	CoUninitialize();
//}