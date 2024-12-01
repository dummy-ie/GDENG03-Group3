#pragma once

#include <wrl/client.h>
#include "WICTextureLoader.h"
#include "DirectXHelpers.h"
#include <string>
#include <shobjidl.h> 
#include <vector>

#include "Prerequisites.h"
#include "UIScreen.h"
#include "Vector2D.h"

namespace gdeng03
{
	class MenuScreen;

	class MaterialEditor :
		public UIScreen
	{
	public:
		MaterialEditor();
		//bool* getMaterialEditorOpen();

	private:
		void draw() override;
		void showColorPickerWindow();
		void updateSelectedMaterial() const;
		void showMaterialEditorWindow();

		static std::vector<unsigned char> getPixelData(const TexturePtr& texture);
		static bool isNormalImage(const TexturePtr& texture);

		void loadTextureFile(TexturePtr& texture);
		static void loadBlankTexture(TexturePtr& texture);

		bool isColorPickerOpen = false;
		//bool isMaterialEditorOpen = false;

		ImVec4 color = ImVec4(1, 1, 1, 1);
		float metallic = 0;
		float smoothness = 0;
		float flatness = 0;
		Vector2D tiling = { 1,1 };
		Vector2D offset = { 0,0 };

		TexturePtr albedoTexture;
		TexturePtr metallicTexture;
		TexturePtr smoothnessTexture;
		TexturePtr normalTexture;

		friend class MenuScreen;
	};
}

