#include "HierarchyScreen.h"

#include "AppWindow.h"
#include "GameObjectManager.h"

namespace gdeng03
{
	HierarchyScreen::HierarchyScreen() : UIScreen("HierarchyScreen")
	{
	}

	void HierarchyScreen::draw()
	{
		ImGui::SetNextWindowSize(ImVec2(UIManager::WindowWidth / 6, UIManager::WindowHeight), ImGuiCond_Once);
		ImGui::Begin("Scene Hierarchy");

		ImGui::BeginChild("Hierarchy");
		int id = 0;
		for (const auto& gameObject : GameObjectManager::get()->getAllObjects())
		{
			if (ImGui::IsMouseClicked(0))
			{
				GameObjectManager::get()->setSelectedObject(nullptr);
			}

			ImGui::PushID(id);
			if (ImGui::Button(gameObject->getDisplayName().c_str(), ImVec2(250, 0)))
			{
				GameObjectManager::get()->setSelectedObject(gameObject.get());

				// if (MaterialEditor* matEditorScreen = dynamic_cast<MaterialEditor*>(UIManager::get()->getScreen("MaterialEditor").get()))
				// 	matEditorScreen->unselectMaterial();
			}
			id++;
			ImGui::PopID();
		}
		ImGui::EndChild();

		ImGui::End();
	}
}
