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
		usedIDs.clear();

		ImGui::SetNextWindowSize(ImVec2(UIManager::WindowWidth / 6, UIManager::WindowHeight), ImGuiCond_Once);
		ImGui::Begin("Scene Hierarchy");

		ImGui::BeginChild("Hierarchy");
		int id = 0;
		for (const auto& gameObject : GameObjectManager::get()->getAllObjects())
		{
			if(gameObject->getLevel() == 0)
			{
				drawHierarchy(gameObject, &id);
			}


			/*ImGui::PushID(id);
			float offset = gameObject->getLevel() * 15;
			ImGui::SetCursorPosX(offset);

			if (ImGui::Button(gameObject->getDisplayName().c_str(), ImVec2(250, 0)))
			{
				GameObjectManager::get()->setSelectedObject(gameObject.get());
			}
			if (ImGui::BeginDragDropSource()) {
				ImGui::SetDragDropPayload("GAME_OBJECT", &gameObject, sizeof(GameObjectPtr));
				ImGui::Text("%s", gameObject->getDisplayName().c_str());
				ImGui::EndDragDropSource();
			}

			if (ImGui::BeginDragDropTarget()) {
				const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GAME_OBJECT");
				if (payload) {
					GameObjectPtr draggedObject = *(GameObjectPtr*)payload->Data;
					if (draggedObject != gameObject && draggedObject->getParent() != gameObject.get()) {
						gameObject->attachChild(draggedObject);
					}
				}
				ImGui::EndDragDropTarget();
			}
			id++;
			ImGui::PopID();*/
		}
		ImGui::EndChild();

		ImGui::End();
	}

	void HierarchyScreen::drawHierarchy(const GameObjectPtr& gameObject, int* id)
	{
		if (usedIDs.find(*id) != usedIDs.end()) {
			return;
		}
		usedIDs.insert(*id);
		ImGui::PushID(*id);

		float offset = gameObject->getLevel() * 15;
		ImGui::SetCursorPosX(offset);

		if (ImGui::Button(gameObject->getDisplayName().c_str(), ImVec2(250, 0)))
		{
			GameObjectManager::get()->setSelectedObject(gameObject.get());
		}
		if (ImGui::BeginDragDropSource()) {
			ImGui::SetDragDropPayload("GAME_OBJECT", &gameObject, sizeof(GameObjectPtr));
			ImGui::Text("%s", gameObject->getDisplayName().c_str());
			ImGui::EndDragDropSource();
		}

		if (ImGui::BeginDragDropTarget()) {
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GAME_OBJECT");
			if (payload) {
				GameObjectPtr draggedObject = *(GameObjectPtr*)payload->Data;
				if (draggedObject != gameObject && draggedObject->getParent() != gameObject.get()) {
					gameObject->attachChild(draggedObject);
				}
			}
			ImGui::EndDragDropTarget();
		}
		*id = *id + 1;

		for (const auto& child : gameObject->getChildren()) {
			drawHierarchy(child, id); // Increase level for children
		}
		
		ImGui::PopID();
	}
}
