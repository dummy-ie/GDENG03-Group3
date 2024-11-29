#pragma once

#include "Component.h"
#include <reactphysics3d/reactphysics3d.h>

#include "GameObject.h"

namespace mrlol
{
	using namespace reactphysics3d;
	class PhysicsComponent : public Component
	{
	public:
		enum class EConstraints : uint8_t
		{
			None = 0,
			FreezePositionX = 1 << 0,
			FreezePositionY = 1 << 1,
			FreezePositionZ = 1 << 2,
			FreezeRotationX = 1 << 3,
			FreezeRotationY = 1 << 4,
			FreezeRotationZ = 1 << 5,
			FreezePosition = FreezePositionX | FreezePositionY | FreezePositionZ,
			FreezeRotation = FreezeRotationX | FreezeRotationY | FreezeRotationZ,
			FreezeAll = FreezePosition | FreezeRotation
		};

	private:
		RigidBody* rigidBody;
		float mass = 10.0f;
		uint8_t constraints = 0;

	public:
		PhysicsComponent(std::string name, GameObject* owner);
		~PhysicsComponent() override;

	public:
		void update() override;
		RigidBody* getRigidBody();

		float getMass();
		bool getUseGravity();
		BodyType getType();
		float getLinearDrag();
		float getAngularDrag();
		bool getConstraint(EConstraints constraint);

		void setTransformFromOpenGL(float* matrix);
		void setMass(float mass);
		void setUseGravity(bool isUsingGravity);
		void setType(BodyType type) const;
		void setLinearDrag(float linearDrag);
		void setAngularDrag(float angularDrag);
		void setConstraints(EConstraints constraints);
	};
}
