#include "BaseComponentSystem.h"

#include "PhysicsSystem.h"
namespace gdeng03
{
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
}
