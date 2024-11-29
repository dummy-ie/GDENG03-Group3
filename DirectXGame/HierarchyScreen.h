#pragma once
#include "UIScreen.h"

namespace mrlol
{
	class HierarchyScreen final : public UIScreen
	{
	public:
		explicit HierarchyScreen();

	protected:
		void draw() override;
	};
}

