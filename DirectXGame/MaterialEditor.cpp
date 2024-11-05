#include "MaterialEditor.h"

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
			
		}
		ImGui::SameLine();
		if(ImGui::ColorButton("Color", color, 0, ImVec2(50,30)))
		{
			isColorPickerOpen = !isColorPickerOpen;
		}

		ImGui::NewLine();

		//metallic
		ImGui::Text("Metallic Map");
		if (ImGui::ImageButton("Metallic Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(metallicTexture.Get())), imageSize))
		{

		}
		ImGui::SameLine();
		ImGui::SliderFloat("Metallic", &metallic, 0, 1);

		ImGui::NewLine();

		//smoothness
		ImGui::Text("Smoothness Map");
		if (ImGui::ImageButton("Smoothness Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(smoothnessTexture.Get())), imageSize))
		{

		}
		ImGui::SameLine();
		ImGui::SliderFloat("Smoothness", &smoothness, 0, 1);

		ImGui::NewLine();

		//albedo
		ImGui::Text("Normal Map");
		if (ImGui::ImageButton("Normal Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(normalTexture.Get())), imageSize))
		{

		}

		ImGui::NewLine();

		/*ImGui::Text("Tiling"); ImGui::SameLine();*/ ImGui::InputFloat2("Tiling", tiling);
		ImGui::InputFloat2("Offset", offset);

	}
	ImGui::End();
}
