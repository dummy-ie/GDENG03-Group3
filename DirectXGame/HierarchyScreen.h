#pragma once
#include "Prerequisites.h"
#include "UIScreen.h"
#include "unordered_set"

namespace gdeng03
{
	class HierarchyScreen final : public UIScreen
	{
	public:
		explicit HierarchyScreen();

	protected:
		void draw() override;
		void drawHierarchy(const GameObjectPtr& gameObject, int* id);

	private:
		std::unordered_set<int> usedIDs;
	};
}

