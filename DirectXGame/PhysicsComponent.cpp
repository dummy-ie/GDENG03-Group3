#include "PhysicsComponent.h"
#include "GameObject.h"

PhysicsComponent::PhysicsComponent(String name, GameObject* owner) : Component(name, ComponentType::Physics, owner)
{
	BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
	PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

	//create a rigid body for the world
	Vector3D scale = this->getOwner()->getLocalScale();

	Transform transform; 
	transform.setFromOpenGL(this->getOwner()->getLocalPhysicsMatrix().toColumnMajor());

	BoxShape* boxshape = physicsCommon->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2));
	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(boxshape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	Matrix4x4 newLocalMatrix;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			newLocalMatrix.m_mat[i][j] = matrix[i * 4 + j];
		}
	}

	
	this->getOwner()->setLocalMatrix(newLocalMatrix);

}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::perform(float deltaTime)
{
	if (this->rigidBody) {

		const Transform transform = this->rigidBody->getTransform();
		float matrix[16];
		transform.getOpenGLMatrix(matrix);

		Matrix4x4 newLocalMatrix;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				newLocalMatrix.m_mat[i][j] = matrix[i * 4 + j];
			}
		}

		if (this->getOwner()->overrideMatrix != false){
			this->getOwner()->setLocalMatrix(newLocalMatrix);
		}
		std::cout << "It is moving" << std::endl;
	}
}


RigidBody* PhysicsComponent::getRigidbody()
{
	return this->rigidBody;
}
