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
        float fMass = 0.0f;
        bool hasGravity = true;

        if (selectedCube->GetPhysicsComponent() == nullptr)
            hasPhysComp = false;

       
        if (ImGui::Checkbox("Physics Component", &hasPhysComp)) {
                selectedCube->TogglePhysicsComponent(hasPhysComp);
        }

        if (hasPhysComp != false) {

            fMass = selectedCube->GetPhysicsComponent()->getMass();

            if (!selectedCube->GetPhysicsComponent()->getGravity())
                hasGravity = false;

            if (ImGui::InputFloat("Mass Value", &fMass)) {
                selectedCube->GetPhysicsComponent()->setMass(fMass);
            }

            if (ImGui::Checkbox("Has Gravity", &hasGravity)) {
                selectedCube->GetPhysicsComponent()->setGravity(hasGravity);
            }
        }
        // other stuff like gravity down here

    }
    else {
        ImGui::Text("No object selected.");
    }

    ImGui::End();
}