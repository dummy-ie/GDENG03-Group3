#include "PhysicsComponent.h"

#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "GameObject.h"
#include "Vector3D.h"


namespace mrlol
{
	using namespace reactphysics3d;
	using reactphysics3d::Quaternion;

	PhysicsComponent::PhysicsComponent(std::string name, GameObject* owner) : Component(name, ComponentType::PHYSICS, owner)
	{
		BaseComponentSystem::get()->getPhysicsSystem()->registerComponent(this);
		PhysicsCommon* physicsCommon = BaseComponentSystem::get()->getPhysicsSystem()->getPhysicsCommon();
		PhysicsWorld* physicsWorld = BaseComponentSystem::get()->getPhysicsSystem()->getPhysicsWorld();

		const Vector3D scale = this->getOwner()->getLocalScale();
		const Vector3D position = this->getOwner()->getLocalPosition();
		const Vector3D rotation = this->getOwner()->getLocalRotation();

		Quaternion quaternion = Quaternion::fromEulerAngles(rotation.x, rotation.y, rotation.z);
		//Transform transform = Transform(Vector3(position.x, position.y, position.z), quaternion);

		Transform transform;
		transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());

		BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.x / 1.0f, scale.y / 1.0f, scale.z / 1.0f));

		this->rigidBody = physicsWorld->createRigidBody(transform);
		this->rigidBody->addCollider(boxShape, transform);
		this->rigidBody->updateMassPropertiesFromColliders();
		this->rigidBody->setMass(this->mass);
		this->rigidBody->setType(BodyType::DYNAMIC);

		transform = this->rigidBody->getTransform();
		float matrix[16];
		transform.getOpenGLMatrix(matrix);

		this->getOwner()->setLocalMatrix(matrix);
		//const Vector3 position1 = transform.getPosition();
		//const Quaternion orientation = transform.getOrientation();
		//const Vector3 rotation1 = orientation.getVectorV();

		//this->getOwner()->setPosition(Vector3D(position1.x, position1.y, position1.z));
		//this->getOwner()->setRotation(Vector3D(rotation1.x, rotation1.y, rotation1.z));
	}

	PhysicsComponent::~PhysicsComponent()
	{
		BaseComponentSystem::get()->getPhysicsSystem()->unregisterComponent(this);
		Component::~Component();

		PhysicsWorld* physicsWorld = BaseComponentSystem::get()->getPhysicsSystem()->getPhysicsWorld();
		physicsWorld->destroyRigidBody(this->rigidBody);
	}

	void PhysicsComponent::update()
	{
		/*const Transform transform = this->rigidBody->getTransform();
		const Vector3 position = transform.getPosition();
		const Quaternion orientation = transform.getOrientation();
		const Vector3 rotation = orientation.getVectorV();

		this->getOwner()->setPosition(Vector3D(position.x, position.y, position.z));
		//this->getOwner()->setRotation(Vector3D(rotation.x, rotation.y, rotation.z));*/
		Transform transform = this->rigidBody->getTransform();
		const Vector3 position = transform.getPosition();
		const reactphysics3d::Quaternion orientation = transform.getOrientation();

		//this->getOwner()->setPosition(Vector3D(position.x, position.y, position.z));
		//this->getOwner()->setOrientation(Vector4D(orientation.x, orientation.y, orientation.z, orientation.w));

		//this->rigidBody->setTransform(Transform(position, orientation));
		//transform = Transform(position, quaternion);
		//this->rigidBody->setTransform(transform);
		float matrix[16];
		transform.getOpenGLMatrix(matrix);
		//this->getOwner()->setLocalMatrix(Vector4D(orientation.x, orientation.y, orientation.z, orientation.w), matrix);
		this->getOwner()->setLocalMatrix(matrix);
		const Vector3D position2 = this->getOwner()->getLocalPosition();

		//this->getOwner()->setLocalMatrix(Vector3D(position.x, position.y, position.z), Vector4D(orientation.x, orientation.y, orientation.z, orientation.w), matrix);
		//Logger::log("Updating Component : " + this->name);
	}

	RigidBody* PhysicsComponent::getRigidBody()
	{
		return this->rigidBody;
	}

	float PhysicsComponent::getMass()
	{
		return mass;
	}

	bool PhysicsComponent::getUseGravity()
	{
		return this->rigidBody->isGravityEnabled();
	}

	BodyType PhysicsComponent::getType()
	{
		return this->rigidBody->getType();
	}

	float PhysicsComponent::getLinearDrag()
	{
		return this->rigidBody->getLinearDamping();
	}

	float PhysicsComponent::getAngularDrag()
	{
		return this->rigidBody->getAngularDamping();
	}

	bool PhysicsComponent::getConstraint(EConstraints constraint)
	{
		return (constraints & static_cast<uint8_t>(constraint)) == static_cast<uint8_t>(constraint);
	}

	void PhysicsComponent::setTransformFromOpenGL(float* matrix)
	{
		Transform transform;
		transform.setFromOpenGL(matrix);
		this->rigidBody->setTransform(transform);
	}

	void PhysicsComponent::setMass(float mass)
	{
		this->mass = mass;
		this->rigidBody->setMass(mass);
	}

	void PhysicsComponent::setUseGravity(const bool isUsingGravity)
	{
		this->rigidBody->enableGravity(isUsingGravity);
	}

	void PhysicsComponent::setType(const BodyType type) const
	{
		this->rigidBody->setType(type);
	}

	void PhysicsComponent::setLinearDrag(float linearDrag)
	{
		if (linearDrag < 0)
			linearDrag = 0;

		this->rigidBody->setLinearDamping(linearDrag);
	}

	void PhysicsComponent::setAngularDrag(float angularDrag)
	{
		if (angularDrag < 0)
			angularDrag = 0;

		this->rigidBody->setAngularDamping(angularDrag);
	}

	void PhysicsComponent::setConstraints(EConstraints constraints)
	{
		this->constraints = static_cast<uint8_t>(constraints);

		// getConstraint returns 1 if true. AxisFactor of ReactPhysics3D is 0 to freeze.
		const Vector3 freezePosition = Vector3(
			!getConstraint(EConstraints::FreezePositionX),
			!getConstraint(EConstraints::FreezePositionY),
			!getConstraint(EConstraints::FreezePositionZ));

		const Vector3 freezeRotation = Vector3(
			!getConstraint(EConstraints::FreezeRotationX),
			!getConstraint(EConstraints::FreezeRotationY),
			!getConstraint(EConstraints::FreezeRotationZ));

		this->rigidBody->setLinearLockAxisFactor(freezePosition);
		this->rigidBody->setAngularLockAxisFactor(freezeRotation);
	}
}