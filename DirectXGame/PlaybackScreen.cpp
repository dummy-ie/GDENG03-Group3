#include "PlaybackScreen.h"

#include "EngineBackend.h"
#include "imgui.h"
#include "LogUtils.h"

namespace gdeng03
{
	PlaybackScreen::PlaybackScreen() : UIScreen("PlaybackScreen")
	{
		LogUtils::log(this, "Initialized");
	}

	PlaybackScreen::~PlaybackScreen()
	{
	}

	void PlaybackScreen::draw()
	{
		ImGui::Begin("Playback", &isActive);

		EngineBackend* backend = EngineBackend::get();
		if (ImGui::Button("Play"))
		{
			if (backend->getMode() == EngineBackend::EDITOR)
			{
				backend->setMode(EngineBackend::PLAY);
			}
			else
			{
				backend->setMode(EngineBackend::EDITOR);
			}

		}
		if (ImGui::Button("Pause"))
		{
			if (backend->getMode() == EngineBackend::PLAY)
			{
				backend->setMode(EngineBackend::PAUSED);
			}
			else if (backend->getMode() == EngineBackend::PAUSED)
			{
				backend->setMode(EngineBackend::PLAY);
			}
		}
		if (ImGui::Button("Step"))
		{
			if (backend->getMode() == EngineBackend::PAUSED)
			{
				backend->startFrameStep();
			}
		}

		ImGui::End();
	}
}
