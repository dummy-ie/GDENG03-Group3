#pragma once

#include "UIScreen.h"

namespace mrlol
{
	class ProfilerScreen : public UIScreen
	{
	public:
		ProfilerScreen();
		~ProfilerScreen();

	private:
		friend class UIManager;

	private:
		virtual void draw() override;
	};
}