#pragma once

#include <stack>

namespace gdeng03
{
	class EditorAction;
	class GameObject;
	class ActionHistory
	{
	public:
		typedef std::stack<EditorAction*> ActionStack;

		static ActionHistory* get();

		void recordAction(GameObject* gameObject);
		bool hasRemainingUndoActions() const;
		bool hasRemainingRedoActions() const;
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
