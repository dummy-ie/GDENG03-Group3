#include "Component.h"

namespace gdeng03
{
	Component::Component(
		std::string name,
		const ComponentType type,
		GameObject* owner
	) :
		name(std::move(name)),
		type(type),
		owner(owner)
	{
	}

	Component::~Component()
	{
		owner = nullptr;
		type = ComponentType::NOT_SET;
	}

	void Component::attachOwner(GameObject* owner)
	{
		this->owner = owner;
	}

	void Component::detachOwner()
	{
		owner = nullptr;
		delete this;
	}

	GameObject* Component::getOwner() const
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
}
