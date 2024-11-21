#pragma once
#include <reactphysics3d/reactphysics3d.h>

#include "Component.h"

class PhysicsComponent final : public Component
{
public:
	PhysicsComponent(std::string name, GameObject* owner);
	~PhysicsComponent();

	void update() override;

	reactphysics3d::RigidBody* getRigidBody() const;

private:
	float mass = 1000.f;
	reactphysics3d::RigidBody* rigidBody;
};

