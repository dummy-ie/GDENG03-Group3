#pragma once
#include <string>

#include "ComponentType.h"
#include "Prerequisites.h"


class Component
{
public:
	Component(std::string name, ComponentType type, GameObjectPtr owner);
	virtual ~Component();
	Component(Component const&) = default;
	Component& operator=(Component const&) = default;
	Component(Component&& other) noexcept = default;
	Component& operator=(Component&& other) noexcept = default;

	void attachOwner(GameObjectPtr owner);
	void detachOwner();

	GameObjectPtr getOwner();
	ComponentType getType() const;
	std::string getName();

	// use EngineTime deltaTime
	virtual void update() = 0;

protected:
	std::string name;
	ComponentType type;
	GameObjectPtr owner;
};

