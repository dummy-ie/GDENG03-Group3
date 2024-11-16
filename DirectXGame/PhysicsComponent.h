#pragma once
#include "Component.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(String name, GameObject* owner);
	~PhysicsComponent();

	void perform(float deltaTime) override;
	RigidBody* getRigidbody();

private:
	float mass = 1000.0f;
	RigidBody* rigidBody;

};

