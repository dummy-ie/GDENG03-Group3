#include "BaseComponentSystem.h"

#include "PhysicsSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = nullptr;

PhysicsSystem* BaseComponentSystem::getPhysicsSystem() const
{
	return physicsSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
	physicsSystem = new PhysicsSystem();
}

BaseComponentSystem::~BaseComponentSystem()
{
	delete physicsSystem;
	delete sharedInstance;
}
