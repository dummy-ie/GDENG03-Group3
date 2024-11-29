#include "EngineBackend.h"

#include "GameObjectManager.h"
#include "LogUtils.h"

namespace mrlol
{
	EngineBackend* EngineBackend::sharedInstance = nullptr;
	EngineBackend* EngineBackend::get()
	{
		if (!sharedInstance)
			sharedInstance = new EngineBackend();

		return sharedInstance;
	}

	// void EngineBackend::initialize()
	// {
	// 	if (sharedInstance)
	// 	{
	// 		LogUtils::error("Input System already created");
	// 	}
	// 	sharedInstance = new EngineBackend();
	// }

	// void EngineBackend::destroy()
	// {
	// 	delete sharedInstance;
	// }

	void EngineBackend::setMode(EditorMode mode)
	{
		m_editorMode = mode;
		if (m_editorMode == EditorMode::PLAY)
		{
			GameObjectManager::get()->saveEditStates();
		}
		else if (m_editorMode == EditorMode::EDITOR)
		{
			GameObjectManager::get()->restoreEditStates();
		}
	}

	void EngineBackend::startFrameStep()
	{
		m_frameStepping = true;
	}

	void EngineBackend::endFrameStep()
	{
		m_frameStepping = false;
	}

	bool EngineBackend::insideFrameStep()
	{
		return m_frameStepping;
	}

	EngineBackend::EditorMode EngineBackend::getMode()
	{
		return this->m_editorMode;
	}

	EngineBackend::EngineBackend()
	{
		LogUtils::log(this, "Initialized");
	}

	EngineBackend::~EngineBackend()
	{
		LogUtils::log(this, "Destroyed");
		delete sharedInstance;
	}
}