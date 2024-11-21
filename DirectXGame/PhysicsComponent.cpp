#include "PhysicsComponent.h"

#include <utility>

#include "GameObject.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"

using namespace reactphysics3d;

PhysicsComponent::PhysicsComponent(std::string name, GameObject* owner) :
	Component(std::move(name), ComponentType::PHYSICS, owner)
{
	BaseComponentSystem::get()->getPhysicsSystem()->registerComponent(this);
	PhysicsCommon* physicsCommon = BaseComponentSystem::get()->getPhysicsSystem()->getPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseComponentSystem::get()->getPhysicsSystem()->getPhysicsWorld();

	const Vector3D scale = getOwner()->getScale();
	Transform transform;
	//transform.setFromOpenGL(getOwner()->getPhysicsLocalMatrix());
	Vector3 physVec3 = Vector3(getOwner()->getPosition().x, getOwner()->getPosition().y, getOwner()->getPosition().z);
	transform.setPosition(physVec3);
	transform.setOrientation(reactphysics3d::Quaternion::identity());
	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.x / 1.f, scale.y / 1.f, scale.z / 1.f)); //half extent
	rigidBody = physicsWorld->createRigidBody(transform);

	rigidBody->addCollider(boxShape, transform);
	rigidBody->updateMassPropertiesFromColliders();
	rigidBody->setMass(mass);
	rigidBody->setType(BodyType::DYNAMIC);

	transform = rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);
	
	getOwner()->setMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
	Component::~Component();
	BaseComponentSystem::get()->getPhysicsSystem()->unregisterComponent(this);
}

void PhysicsComponent::update()
{
	const Transform transform = rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->setMatrix(matrix);
}

RigidBody* PhysicsComponent::getRigidBody() const
{
	return rigidBody;
}
