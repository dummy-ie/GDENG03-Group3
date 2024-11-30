#include "DebugScreen.h"

#include "AppWindow.h"

mrlol::DebugScreen::DebugScreen() : UIScreen("Debug Screen")
{
}

void mrlol::DebugScreen::logToConsole(const string& message)
{
	logList.push_back(message);
}

void mrlol::DebugScreen::draw()
{
	//ImGui::SetNextWindowSize(ImVec2(UIManager::WindowWidth / 6, UIManager::WindowHeight), ImGuiCond_Once);
	ImGui::Begin("Debug Console");

	ImGui::BeginChild("Output");
	for (string log : logList)
	{
		ImGui::Text(log.data());
	}
	ImGui::EndChild();

	ImGui::End();
}
