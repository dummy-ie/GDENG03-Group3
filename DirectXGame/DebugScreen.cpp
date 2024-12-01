#include "DebugScreen.h"

#include "AppWindow.h"

gdeng03::DebugScreen::DebugScreen() : UIScreen("Debug Screen")
{
}

void gdeng03::DebugScreen::logToConsole(const string& message)
{
	logList.push_back(message);
}

void gdeng03::DebugScreen::draw()
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
