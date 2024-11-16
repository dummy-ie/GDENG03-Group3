#include "PhysicsSystem.h"
//#include "PhysicsComponent.h"
#include <iostream>
#include "EngineTime.h"


PhysicsSystem::PhysicsSystem()
{
	this->physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = Vector3(0, -9.81, 0);

	this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
	std::cout << "Successfully created physics world.\n";

}
