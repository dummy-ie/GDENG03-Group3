#include "HierarchyScreen.h"

#include "AppWindow.h"
#include "GameObjectManager.h"

namespace mrlol
{
	HierarchyScreen::HierarchyScreen() : UIScreen("HierarchyScreen")
	{
	}

	void HierarchyScreen::draw()
	{
		ImGui::SetNextWindowSize(ImVec2(UIManager::WindowWidth / 6, UIManager::WindowHeight), ImGuiCond_Once);
		ImGui::Begin("Scene Hierarchy");

		ImGui::BeginChild("Hierarchy");
		for (const auto& gameObject : GameObjectManager::get()->getAllObjects())
		{
			if (ImGui::Button(gameObject->getUniqueName().c_str(), ImVec2(250, 0)))
				GameObjectManager::get()->setSelectedObject(gameObject.get());
		}
		ImGui::EndChild();

		ImGui::End();
	}
}
