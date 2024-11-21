#pragma once
#include <string>

#include "ComponentType.h"
#include "Prerequisites.h"
#include "EngineTime.h"

class Component
{
public:
	Component(std::string name, ComponentType type, GameObject* owner);
	virtual ~Component();
	Component(Component const&) = default;
	Component& operator=(Component const&) = default;
	Component(Component&& other) noexcept = default;
	Component& operator=(Component&& other) noexcept = default;

	void attachOwner(GameObject* owner);
	void detachOwner();

	GameObject* getOwner() const;
	ComponentType getType() const;
	std::string getName();

	// use EngineTime deltaTime
	virtual void update() = 0;

protected:
	std::string name;
	ComponentType type;
	GameObject* owner;
};

