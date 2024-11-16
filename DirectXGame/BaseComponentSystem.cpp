#include "BaseComponentSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = nullptr;

BaseComponentSystem* BaseComponentSystem::getInstance()
{
	return nullptr;
}

void BaseComponentSystem::initialize()
{
}

void BaseComponentSystem::destroy()
{
}

PhysicsSystem* BaseComponentSystem::getPhysicsSystem()
{
	return nullptr;
}

BaseComponentSystem::BaseComponentSystem()
{
}

BaseComponentSystem::~BaseComponentSystem()
{
}
