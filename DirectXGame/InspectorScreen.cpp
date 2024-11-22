#include "InspectorScreen.h"
#include "CubeManager.h"

InspectorScreen::InspectorScreen() : UIScreen("InspectorScreen")
{
	
}


void InspectorScreen::draw() {

    ImGui::Begin("Inspector Screen");

    if (CubeManager::GetInstance().GetSelectedCube() != nullptr) {
        Cube* selectedCube = CubeManager::GetInstance().GetSelectedCube();

        // Display the selected cube's name
        ImGui::Text("Object: %s", selectedCube->GetName().c_str());

        // Toggle checkbox for the 'isActive' property
        bool hasPhysComp = true;
        if (selectedCube->GetPhysicsComponent() == nullptr)
            hasPhysComp = false;

        if (ImGui::Checkbox("Physics Component", &hasPhysComp)) {
            selectedCube->TogglePhysicsComponent(hasPhysComp);
        }

        // You can add more properties to inspect in a similar way
    }
    else {
        ImGui::Text("No object selected.");
    }

    ImGui::End();
}