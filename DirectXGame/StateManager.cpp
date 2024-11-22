#include "StateManager.h"

StateManager* StateManager::sharedInstance = nullptr;

StateManager::StateType StateManager::getStateType()
{
	return this->currentState;
}

StateManager::StateType StateManager::setStateType(StateType state)
{
	this->currentState = state;
}

StateManager* StateManager::getInstance()
{
	return sharedInstance;
}

void StateManager::initialize()
{
	if (!sharedInstance)
		sharedInstance = new StateManager();
}


