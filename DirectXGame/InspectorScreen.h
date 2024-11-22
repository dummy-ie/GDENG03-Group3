#pragma once

#include <wrl/client.h>
#include "WICTextureLoader.h"
#include "DirectXHelpers.h"
#include "StateManager.h"
#include "UIScreen.h"

class InspectorScreen final :
	public UIScreen
{
public:
	InspectorScreen();

private:
	void draw() override;
	

	//Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> creditsTexture;
};
