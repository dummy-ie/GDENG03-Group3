#pragma once

#include "UIScreen.h"

#include "RenderTexture.h"
#include "Prerequisites.h"
#include "SceneCamera.h"
#include "Viewport.h"

namespace mrlol
{
	enum EFillMode
	{
		SOLID,
		WIREFRAME,
		SOLID_WIREFRAME
	};

	class ViewportScreen : public UIScreen
	{
	private:
		int index;
		int camIndex;

		SceneCameraPtr currentCamera;
		SceneCameraPtr ownCamera;

		EFillMode currentFillMode = SOLID;
		RenderTexturePtr renderTexture;

		bool isRightMouseDown = false;

		int selectedProj = 0;
		int selectedState = 0;
		int selectedCameraIndex;

	public:
		ViewportScreen(int index);
		~ViewportScreen();

	public:
		virtual void draw() override;

	private:
		void handleInput();
		void drawViewportUI(ImVec2 position);

	private:
		friend class UIManager;
		friend class ViewportManager;
	};
}