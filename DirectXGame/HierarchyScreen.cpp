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
			ImGui::PushID(id);
			if (ImGui::Button(gameObject->getDisplayName().c_str(), ImVec2(250, 0)))
			{
				GameObjectManager::get()->setSelectedObject(gameObject.get());
			}
			id++;
			ImGui::PopID();
		}
		ImGui::EndChild();

		ImGui::End();
	}
}
