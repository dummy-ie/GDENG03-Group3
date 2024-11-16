#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(String name, GameObject* owner) : Component(name, ComponentType::Physics, owner)
{


}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::perform(float deltaTime)
{
}

RigidBody* PhysicsComponent::getRigidbody()
{
	return nullptr;
}
