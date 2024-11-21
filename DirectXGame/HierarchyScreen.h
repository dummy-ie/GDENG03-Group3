#pragma once
#include "UIScreen.h"

class HierarchyScreen final : public UIScreen
{
public:
	explicit HierarchyScreen();

protected:
	void draw() override;
};

