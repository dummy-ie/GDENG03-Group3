#pragma once

#include <wrl/client.h>
#include "WICTextureLoader.h"
#include "DirectXHelpers.h"

#include "UIScreen.h"

class MenuScreen final :
	public UIScreen
{
public:
	MenuScreen();

private:
	void draw() override;
	void onCreateCubeClicked();
	void onCreateSphereClicked();
	void onCreatePlaneClicked();
	void showCreditsWindow();
	void showColorPickerWindow();

	bool isColorPickerOpen = false;
	bool isCreditsOpen = false;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> creditsTexture;
};

