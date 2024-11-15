#include "Component.h"

Component::Component(
	std::string name,
	const ComponentType type,
	GameObjectPtr owner
) :
	name(std::move(name)),
	type(type),
	owner(std::move(owner))
{
}

Component::~Component()
{
	owner = nullptr;
	type = NOT_SET;
}

void Component::attachOwner(GameObjectPtr owner)
{
	this->owner = std::move(owner);
}

void Component::detachOwner()
{
	owner = nullptr;
	delete this;
}

GameObjectPtr Component::getOwner()
{
	return owner;
}

ComponentType Component::getType() const
{
	return type;
}

std::string Component::getName()
{
	return name;
}
