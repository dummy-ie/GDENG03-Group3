#include "ProfilerScreen.h"

#include "imgui.h"
#include "LogUtils.h"

using namespace mrlol;

ProfilerScreen::ProfilerScreen() : UIScreen("ProfilerScreen")
{
    LogUtils::log(this, "Initialized");
}

ProfilerScreen::~ProfilerScreen()
{
}

void ProfilerScreen::draw()
{
    ImGui::Begin("Profiler", &isActive);

    ImGui::Text("%.3f ms/frame, %.1f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    //ImGui::PlotLines()

    ImGui::End();
}