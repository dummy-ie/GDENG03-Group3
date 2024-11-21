#include "GameObject.h"

GameObject::GameObject(String name)
{
	this->name = name;
	this->localPosition = Vector3D(0, 0, 0);
	this->localRotation = Vector3D(0, 0, 0);
	this->localScale = Vector3D(1, 1, 1);


}

GameObject::~GameObject()
{
}

void GameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x,y,z);
}

void GameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
}

Vector3D GameObject::getLocalPosition()
{
	return this->localPosition;
}

void GameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);

}

void GameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
}

Vector3D GameObject::getLocalScale()
{
	return this->localScale;
}

void GameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
}

void GameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
}

Vector3D GameObject::getLocalRotation()
{
	return this->localRotation;
}

Matrix4x4 GameObject::getLocalMatrix()
{
	return this->localMatrix;
}

Matrix4x4 GameObject::getLocalPhysicsMatrix()
{
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity(); translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 zMatrix; zMatrix.setIdentity(); zMatrix.setRotationZ(rotation.m_z);
	Matrix4x4 xMatrix; xMatrix.setIdentity(); xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setIdentity(); yMatrix.setRotationY(rotation.m_y);

	allMatrix *= scaleMatrix;
	allMatrix *= zMatrix;
	allMatrix *= yMatrix;
	allMatrix *= xMatrix;
	allMatrix *= translationMatrix;
	this->localPhysicsMatrix.setIdentity();
	this->localPhysicsMatrix *= allMatrix;

	return this->localPhysicsMatrix;
}

void GameObject::setLocalMatrix(const Matrix4x4& matrix)
{
	
		Matrix4x4 allMatrix; allMatrix.setIdentity();
		Matrix4x4 translationMatrix; translationMatrix.setIdentity(); translationMatrix.setTranslation(this->getLocalPosition());
		Matrix4x4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->getLocalScale());
		Vector3D rotation = this->getLocalRotation();
		Matrix4x4 zMatrix; zMatrix.setIdentity(); zMatrix.setRotationZ(rotation.m_z);
		Matrix4x4 xMatrix; xMatrix.setIdentity(); xMatrix.setRotationX(rotation.m_x);
		Matrix4x4 yMatrix; yMatrix.setIdentity(); yMatrix.setRotationY(rotation.m_y);

		allMatrix *= scaleMatrix;
		allMatrix *= zMatrix;
		allMatrix *= yMatrix;
		allMatrix *= xMatrix;
		allMatrix *= translationMatrix;

		this->localMatrix = matrix;
		this->localMatrix *= allMatrix;
	
}

void GameObject::setLocalPhysicsMatrix(const Matrix4x4& matrix)
{
	this->localPhysicsMatrix = matrix;
}

void GameObject::attachComponent(Component* component)
{
	component->attachOwner(this);
}

void GameObject::detachComponent(Component* component)
{
	component->detachOwner();
}

Component* GameObject::findComponentByName(String Name)
{
	for (Component* component : this->componentList) {
		if (component->getName() == Name) {
			return component;
		}
	}
}

Component* GameObject::findComponentofType(Component::ComponentType type, String name)
{
	for (Component* component : this->componentList) {
		if (component->getType() == type) {

			if (component->getName() == name)
				return component;
		}
	}
	
}

GameObject::ComponentList GameObject::getComponentsofType(Component::ComponentType type)
{
	ComponentList list = {};
	for (Component* component : this->componentList) {
		if (component->getType() == type) {
			list.push_back(component);
		}
	}

	return list;
}

GameObject::ComponentList GameObject::getComponentsOfTypeRecursive(Component::ComponentType type)
{
	ComponentList list = {};
	for (Component* component : this->componentList) {
		if (component->getType() == type) {
			list.push_back(component);
			getComponentsofType(type);
		}
	}

	return list;
}

void GameObject::Awake()
{
}
