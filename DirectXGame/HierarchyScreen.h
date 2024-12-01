#pragma once
#include "UIScreen.h"

namespace gdeng03
{
	class HierarchyScreen final : public UIScreen
	{
	public:
		explicit HierarchyScreen();

	protected:
		void draw() override;
	};
}

