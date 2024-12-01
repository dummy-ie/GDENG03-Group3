#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>

namespace gdeng03
{
	class PhysicsComponent;

	class PhysicsSystem
	{
	public:
		typedef reactphysics3d::PhysicsCommon PhysicsCommon;
		typedef reactphysics3d::PhysicsWorld PhysicsWorld;
		typedef std::unordered_map<std::string, PhysicsComponent*> ComponentMap;
		typedef std::vector<PhysicsComponent*> ComponentList;

		PhysicsSystem();
		~PhysicsSystem();
		PhysicsSystem(PhysicsSystem const&) = default;
		PhysicsSystem& operator=(PhysicsSystem const&) = default;
		PhysicsSystem(PhysicsSystem&& other) noexcept = default;
		PhysicsSystem& operator=(PhysicsSystem&& other) noexcept = default;

		void registerComponent(PhysicsComponent* component);
		void unregisterComponent(PhysicsComponent* component);
		void unregisterComponentByName(const std::string& name);

		PhysicsComponent* findComponentByName(const std::string& name);
		ComponentList getAllComponents();

		void updateAllComponents() const;
		PhysicsCommon* getPhysicsCommon() const;
		PhysicsWorld* getPhysicsWorld() const;

	private:
		ComponentMap componentMap;
		ComponentList componentList;

		PhysicsCommon* physicsCommon;
		PhysicsWorld* physicsWorld;
	};
}
