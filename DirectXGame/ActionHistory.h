#pragma once

#include <stack>

namespace mrlol
{
	class EditorAction;
	class GameObject;
	class ActionHistory
	{
	public:
		typedef std::stack<EditorAction*> ActionStack;

		static ActionHistory* getInstance();
		static void initialize();
		static void destroy();

		void recordAction(GameObject* gameObject);
		bool hasRemainingUndoActions();
		bool hasRemainingRedoActions();
		EditorAction* undoAction();
		EditorAction* redoAction();
		void clear();

	private:
		ActionHistory();
		ActionHistory(ActionHistory const&) {}
		ActionHistory& operator=(ActionHistory const&) {}
		~ActionHistory();

		static ActionHistory* sharedInstance;

		ActionStack actionsPerformed;
		ActionStack actionsCancelled;
	};
}
