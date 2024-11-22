#pragma once

#include <wrl/client.h>
#include "WICTextureLoader.h"
#include "DirectXHelpers.h"
#include "StateManager.h"
#include "UIScreen.h"

class HeirarchyScreen final :
	public UIScreen
{
public:
	HeirarchyScreen();

private:
	void draw() override;
};
