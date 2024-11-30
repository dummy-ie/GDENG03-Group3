#pragma once
#include "UIScreen.h"

#include <vector>

namespace mrlol
{
	using std::string;
	using std::vector;

	class DebugScreen final : public UIScreen
	{
	public:
		explicit DebugScreen();

		void logToConsole(const string& message);

	private:
		friend class UIManager;

		vector<string> logList;

	protected:
		void draw() override;
	};
}

