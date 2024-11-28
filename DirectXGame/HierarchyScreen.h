#pragma once

#include <wrl/client.h>
#include "WICTextureLoader.h"
#include "DirectXHelpers.h"
#include "StateManager.h"
#include "UIScreen.h"

class HierarchyScreen final :
	public UIScreen
{
public:
	HierarchyScreen();

private:
	void draw() override;
};
