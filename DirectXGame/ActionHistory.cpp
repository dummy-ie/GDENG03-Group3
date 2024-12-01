#include "ActionHistory.h"

#include "EditorAction.h"
#include "EngineBackend.h"
#include "LogUtils.h"

namespace gdeng03
{
	ActionHistory* ActionHistory::sharedInstance = nullptr;

	ActionHistory* ActionHistory::get()
	{
		if (!sharedInstance)
		{
			sharedInstance = new ActionHistory();
		}

		return sharedInstance;
	}

	void ActionHistory::recordAction(GameObject* gameObject)
	{
		if (EngineBackend::get()->getMode() == EngineBackend::EditorMode::EDITOR)
		{
			EditorAction* editorAction = new EditorAction(gameObject);
			this->actionsPerformed.push(editorAction);

			LogUtils::log("Stored Action " + gameObject->getDisplayName());
		}
	}

	bool ActionHistory::hasRemainingUndoActions() const
	{
		return !actionsPerformed.empty();
	}

	bool ActionHistory::hasRemainingRedoActions() const
	{
		return !actionsCancelled.empty();
	}

	EditorAction* ActionHistory::undoAction()
	{
		if (EngineBackend::get()->getMode() != EngineBackend::EditorMode::EDITOR)
		{
			LogUtils::log("Cannot perform undo action during play.");
			return nullptr;
		}

		if (this->hasRemainingUndoActions())
		{
			EditorAction* action = actionsPerformed.top();
			actionsPerformed.pop();
			actionsCancelled.push(action);
			return action;
		}

		LogUtils::log("No more actions remaining.");
		return nullptr;
	}

	EditorAction* ActionHistory::redoAction()
	{
		if (EngineBackend::get()->getMode() != EngineBackend::EditorMode::EDITOR)
		{
			LogUtils::log("Cannot perform redo action during play.");
			return nullptr;
		}

		if (this->hasRemainingRedoActions())
		{
			EditorAction* action = actionsCancelled.top();
			actionsCancelled.pop();
			actionsPerformed.push(action);
			return action;
		}

		LogUtils::log("No more actions remaining.");
		return nullptr;
	}

	void ActionHistory::clear()
	{
		for (int i = 0; i < actionsCancelled.size(); i++)
		{
			actionsCancelled.pop();
		}
	}

	ActionHistory::ActionHistory()
	{
		LogUtils::log(this, "Initialized");
	}

	ActionHistory::~ActionHistory()
	{
		LogUtils::log(this, "Destroyed");
		delete sharedInstance;
	}
}
