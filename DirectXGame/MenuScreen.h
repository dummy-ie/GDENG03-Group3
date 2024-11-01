#pragma once
#include "UIScreen.h"
class MenuScreen final :
	public UIScreen
{
public:
	MenuScreen() : UIScreen("MenuScreen") {}

private:
	void draw() override;
	void onCreateCubeClicked();
	void onCreateSphereClicked();
	void onCreatePlaneClicked();
	void showCreditsWindow();

	bool isCreditsOpen = false;

};

