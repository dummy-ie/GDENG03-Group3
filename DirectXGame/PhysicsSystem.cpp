#include "PhysicsSystem.h"

#include "PhysicsComponent.h"
#include "EngineTime.h"
#include "LogUtils.h"

namespace gdeng03
{
	PhysicsSystem::PhysicsSystem()
	{
		physicsCommon = new PhysicsCommon();
		PhysicsWorld::WorldSettings settings;
		settings.defaultVelocitySolverNbIterations = 50;
		settings.gravity = reactphysics3d::Vector3(0, -9.81, 0);
		physicsWorld = physicsCommon->createPhysicsWorld(settings);
		LogUtils::log(this, "Physics world initialized successfully.");
	}

	PhysicsSystem::~PhysicsSystem()
	{
		delete this->physicsCommon;
	}

	void PhysicsSystem::registerComponent(PhysicsComponent* component)
	{
		componentMap[component->getName()] = component;
		componentList.push_back(component);
	}

	void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
	{
		if (!componentMap[component->getName()])
		{
			LogUtils::log(this, "Component not registered to physics system.");
			return;
		}

		// remove from map
		componentMap.erase(component->getName());

		// remove from list
		const auto it = std::find(componentList.begin(), componentList.end(), component);
		componentList.erase(it);
	}

	void PhysicsSystem::unregisterComponentByName(const std::string& name)
	{
		if (!componentMap[name])
		{
			LogUtils::log(this, "Component not found in physics system.");
			return;
		}

		unregisterComponent(componentMap[name]);
	}

	PhysicsComponent* PhysicsSystem::findComponentByName(const std::string& name)
	{
		if (!componentMap[name])
		{
			LogUtils::log(this, "Component not found in physics system.");
			return nullptr;
		}

		return componentMap[name];
	}

	PhysicsSystem::ComponentList PhysicsSystem::getAllComponents()
	{
		return componentList;
	}

	void PhysicsSystem::updateAllComponents() const
	{
		if (EngineTime::getDeltaTime() > 0.0f) {
			physicsWorld->update(EngineTime::getDeltaTime());
			for (const auto pc : componentList)
			{
				pc->update();
				LogUtils::log(this, pc->getName() + " position: " + pc->getRigidBody()->getTransform().getPosition().to_string());
			}
		}
	}

	PhysicsSystem::PhysicsCommon* PhysicsSystem::getPhysicsCommon() const
	{
		return physicsCommon;
	}

	PhysicsSystem::PhysicsWorld* PhysicsSystem::getPhysicsWorld() const
	{
		return physicsWorld;
	}
}
