#pragma once

#include "UIScreen.h"

namespace gdeng03 {
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