#pragma once
#include "GameObject.h"
#include "UIScreen.h"

namespace mrlol
{
	class InspectorScreen : public UIScreen
	{

	public:
		InspectorScreen();

	private:
		virtual void draw() override;
		void drawInspector();
		void drawTransformTable(GameObject* gameObject);
		void drawComponentList(GameObject* gameObject);

	private:
		GameObject* selectedObject = nullptr;
		float position[3];
		float scale[3];
		float rotation[3];
		bool hasChanged = false;
		bool isLeftDown = false;
		bool addComponent = false;

		friend class UIManager;
	};
}