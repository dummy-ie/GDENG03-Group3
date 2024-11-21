#pragma once

#include <string>

class PhysicsSystem;

class BaseComponentSystem
{
public:
	PhysicsSystem* getPhysicsSystem() const;

private:
	PhysicsSystem* physicsSystem;

	// Singleton
public:
	static BaseComponentSystem* get()
	{
		if (!sharedInstance)
			sharedInstance = new BaseComponentSystem();

		return sharedInstance;
	}

	BaseComponentSystem(BaseComponentSystem const&) = delete;
	BaseComponentSystem& operator=(BaseComponentSystem const&) = delete;
	BaseComponentSystem(BaseComponentSystem&& other) noexcept = delete;
	BaseComponentSystem& operator=(BaseComponentSystem&& other) noexcept = delete;

private:
	BaseComponentSystem();
	~BaseComponentSystem();
	static BaseComponentSystem* sharedInstance;
};

