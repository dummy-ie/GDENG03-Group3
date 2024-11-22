#include "HeirarchyScreen.h"
#include "CubeManager.h"

HeirarchyScreen::HeirarchyScreen() : UIScreen("HeirarchyScreen") {

}

void HeirarchyScreen::draw() {
    static Cube* selectedCube = nullptr;
    std::vector<Cube*> cube_list = CubeManager::GetInstance().GetCubeList();

    if (ImGui::Begin("Scene Hierarchy")) {
        for (Cube* cube : cube_list) {
            // Highlight if the object is selected
            ImGuiTreeNodeFlags flags = (selectedCube == cube) ? ImGuiTreeNodeFlags_Selected : 0;

            // Display object name as selectable
            if (ImGui::Selectable(cube->GetName().c_str(), selectedCube == cube)) {
                selectedCube = cube; // Update the selected object
                CubeManager::GetInstance().SetSelectedCube(selectedCube);
            }
        }
    }
    ImGui::End();
}
