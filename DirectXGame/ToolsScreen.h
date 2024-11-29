#pragma once

#include "UIScreen.h"

namespace mrlol
{
	class ToolsScreen : public UIScreen
	{
	public:
		ToolsScreen();
		~ToolsScreen();

	private:
		friend class UIManager;

	private:
		virtual void draw() override;
	};
}