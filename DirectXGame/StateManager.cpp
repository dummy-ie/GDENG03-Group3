#include "StateManager.h"

StateManager* StateManager::sharedInstance = nullptr;

void StateManager::initialize()
{
	if (!sharedInstance)
		sharedInstance = new StateManager();

}

StateManager::StateManager() {

}

StateManager::~StateManager()
{}


StateManager::StateType StateManager::getStateType()
{
	return this->currentState;
}

void StateManager::setStateType(StateType state)
{
	this->currentState = state;
}

StateManager* StateManager::getInstance()
{
	return sharedInstance;
}




