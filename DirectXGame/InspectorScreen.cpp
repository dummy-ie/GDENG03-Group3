#include "InspectorScreen.h"
#include "CubeManager.h"

InspectorScreen::InspectorScreen() : UIScreen("InspectorScreen")
{
	
}


void InspectorScreen::draw() {

    ImGui::Begin("Inspector Screen");

    if (CubeManager::GetInstance().GetSelectedCube() != nullptr) {
        Cube* selectedCube = CubeManager::GetInstance().GetSelectedCube();

        // Display name
        ImGui::Text("Object: %s", selectedCube->GetName().c_str());

        // physics component checkbox
        bool hasPhysComp = true;
        if (selectedCube->GetPhysicsComponent() == nullptr)
            hasPhysComp = false;

        if (ImGui::Checkbox("Physics Component", &hasPhysComp)) {
            selectedCube->TogglePhysicsComponent(hasPhysComp);
        }

        // other stuff like gravity down here

    }
    else {
        ImGui::Text("No object selected.");
    }

    ImGui::End();
}