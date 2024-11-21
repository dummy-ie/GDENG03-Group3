#include "HierarchyScreen.h"

#include "AppWindow.h"
#include "GameObjectManager.h"

HierarchyScreen::HierarchyScreen() : UIScreen("HierarchyScreen")
{
}

void HierarchyScreen::draw()
{
	ImGui::Begin("Scene Hierarchy");

	for (const auto& gameObject : GameObjectManager::get()->getAllObjects())
	{
		if (ImGui::Button(gameObject->getName().c_str(), ImVec2(250, 0)))
			GameObjectManager::get()->setSelectedObject(gameObject);
	}

	ImGui::End();
}
