#pragma once

#include "UIScreen.h"

namespace mrlol {
	class PlaybackScreen : public UIScreen
	{
	public:
		PlaybackScreen();
		~PlaybackScreen();

	private:
		friend class UIManager;

	private:
		virtual void draw() override;
	};
}