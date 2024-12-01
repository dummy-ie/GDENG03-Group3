#include "GameObject.h"

#include <iostream>
#include <utility>

#include "CameraManager.h"
#include "EditorAction.h"
#include "PhysicsComponent.h"

namespace gdeng03
{
	GameObject::GameObject(const std::string& name) : displayName(name), name(name)
	{
	}

	void GameObject::setPosition(const Vector3D& position)
	{
		globalPosition = position;

		localPosition = (parent) ?
			globalPosition - parent->getGlobalPosition() :
			globalPosition;

		for(GameObjectPtr child : children)
		{
			child->setPosition(position + child->getLocalPosition());
		}

		updateLocalMatrix();
	}

	void GameObject::setLocalPosition(const Vector3D& position)
	{
		localPosition = position;

		globalPosition = (parent) ?
			localPosition + parent->getGlobalPosition() :
			localPosition;

		for (GameObjectPtr child : children)
		{
			child->setPosition(globalPosition + child->getLocalPosition());
		}

		updateLocalMatrix();
	}

	void GameObject::translate(const Vector3D& translation)
	{
		localPosition += translation;

		globalPosition = (parent) ?
			localPosition + parent->getGlobalPosition() :
			localPosition;

		for (GameObjectPtr child : children)
		{
			child->setPosition(globalPosition + child->getLocalPosition());
		}

		updateLocalMatrix();
	}

	Vector3D GameObject::getGlobalPosition()
	{
		return globalPosition;
	}

	Vector3D GameObject::getLocalPosition()
	{
		return localPosition;
	}

	void GameObject::setLocalScale(const Vector3D& scale)
	{
		localScale = scale;
		updateGlobalScaleWithChildren();
	}

	void GameObject::scale(const Vector3D& scale)
	{
		localScale += scale;
		updateGlobalScaleWithChildren();
	}

	Vector3D GameObject::getGlobalScale()
	{
		return globalScale;
	}

	Vector3D GameObject::getLocalScale()
	{
		return localScale;
	}

	void GameObject::updateGlobalScaleWithChildren()
	{
		globalScale = (parent) ?
			localScale * parent->getGlobalScale() :
			localScale;

		for (GameObjectPtr child : children)
		{
			child->updateGlobalScaleWithChildren();
		}

		updateLocalMatrix();
	}

	void GameObject::setRotation(const Vector3D& rotation)
	{
		globalRotation = rotation;

		localRotation = (parent) ?
			globalRotation - parent->getGlobalRotation() :
			globalRotation;

		for (GameObjectPtr child : children)
		{
			child->setRotation(globalRotation + child->getLocalRotation());
		}

		const reactphysics3d::Quaternion quat = reactphysics3d::Quaternion::fromEulerAngles(rotation.x, rotation.y, rotation.z);
		orientation = Vector4D(quat.x, quat.y, quat.z, quat.w);

		updateLocalMatrix();
	}

	void GameObject::setLocalRotation(const Vector3D& rotation)
	{
		localRotation = rotation;

		globalRotation = (parent) ?
			localRotation + parent->getGlobalRotation() :
			localRotation;

		for (GameObjectPtr child : children)
		{
			child->setRotation(globalRotation + child->getLocalRotation());
		}

		const reactphysics3d::Quaternion quat = reactphysics3d::Quaternion::fromEulerAngles(rotation.x, rotation.y, rotation.z);
		orientation = Vector4D(quat.x, quat.y, quat.z, quat.w);
		updateLocalMatrix();
	}

	void GameObject::rotate(const Vector3D& rotation)
	{
		localRotation += rotation;

		globalRotation = (parent) ?
			localRotation + parent->getGlobalRotation() :
			localRotation;

		for (GameObjectPtr child : children)
		{
			child->setRotation(globalRotation + child->getLocalRotation());
		}

		const reactphysics3d::Quaternion quat = reactphysics3d::Quaternion::fromEulerAngles(rotation.x, rotation.y, rotation.z);
		orientation = Vector4D(quat.x, quat.y, quat.z, quat.w);
		updateLocalMatrix();
	}

	Vector3D GameObject::getGlobalRotation()
	{
		return globalRotation;
	}

	Vector3D GameObject::getLocalRotation()
	{
		return localRotation;
	}

	void GameObject::setOrientation(const Vector4D& orientation)
	{
		this->orientation = orientation;
		updateLocalMatrix();
	}

	Vector4D GameObject::getOrientation()
	{
		return orientation;
	}

	void GameObject::setEnabled(const bool enabled)
	{
		isEnabled = enabled;
	}

	bool GameObject::getEnabled() const
	{
		return isEnabled;
	}

	// can be non-unique.
	void GameObject::setDisplayName(const std::string& displayName)
	{
		this->displayName = std::move(displayName);
	}

	std::string GameObject::getUniqueName()
	{
		return name;
	}

	std::string GameObject::getDisplayName()
	{
		return displayName;
	}

	void GameObject::updateLocalMatrix()
	{
		//setup transformation matrix for drawing.
		Matrix4x4 allMatrix; allMatrix.setIdentity();
		Matrix4x4 translationMatrix; translationMatrix.setIdentity();  translationMatrix.setTranslation(getLocalPosition());
		Matrix4x4 scaleMatrix; scaleMatrix.setScale(getLocalScale());
		Vector3D rotation = getLocalRotation();
		Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.x);
		Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.y);
		Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.z);

		//Scale --> Rotate --> Transform as recommended order.
		Matrix4x4 rotMatrix; rotMatrix.setIdentity();
		rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

		allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
		allMatrix = allMatrix.multiplyTo(translationMatrix);
		this->localMatrix = allMatrix;

		ComponentList result = getComponentsOfType(ComponentType::PHYSICS);
		if (result.size() == 0) return;
		PhysicsComponent* physicsComponent = reinterpret_cast<PhysicsComponent*>(result.front());
		if(physicsComponent != nullptr)
		{
			physicsComponent->setTransformFromOpenGL(getPhysicsLocalMatrix());
		}
	}

	Matrix4x4 GameObject::getLocalMatrix() const
	{
		return localMatrix;
	}

	void GameObject::setLocalMatrix(float matrix[16])
	{
		// Matrix4x4 physMat;
		// physMat.setIdentity();
		//
		// int index = 0;
		// for (int i = 0; i < 4; i++) {
		// 	for (int j = 0; j < 4; j++) {
		// 		physMat.mat[i][j] = matrix[index];
		// 		index++;
		// 	}
		// }
		// 	this->localMatrix = physMat;

		float matrix4x4[4][4];
		matrix4x4[0][0] = matrix[0];
		matrix4x4[0][1] = matrix[1];
		matrix4x4[0][2] = matrix[2];
		matrix4x4[0][3] = matrix[3];

		matrix4x4[1][0] = matrix[4];
		matrix4x4[1][1] = matrix[5];
		matrix4x4[1][2] = matrix[6];
		matrix4x4[1][3] = matrix[7];

		matrix4x4[2][0] = matrix[8];
		matrix4x4[2][1] = matrix[9];
		matrix4x4[2][2] = matrix[10];
		matrix4x4[2][3] = matrix[11];

		matrix4x4[3][0] = matrix[12];
		matrix4x4[3][1] = matrix[13];
		matrix4x4[3][2] = matrix[14];
		matrix4x4[3][3] = matrix[15];

		Matrix4x4 newMatrix; newMatrix.setMatrix(matrix4x4);

		Matrix4x4
			translateMatrix,
			scaleMatrix;

		translateMatrix.setTranslation(getLocalPosition());
		scaleMatrix.setScale(getLocalScale());

		localMatrix = scaleMatrix * translateMatrix * newMatrix;

		// Matrix4x4 scaleMatrix; scaleMatrix.setLocalScale(this->localScale);
		// Matrix4x4 transMatrix; transMatrix.setTranslation(this->localPosition);
		// this->localMatrix = scaleMatrix.multiplyTo(transMatrix.multiplyTo(newMatrix));

		//localMatrix = newMatrix;

		// temp.setLocalMatrix(matrix4X4);
		// scale.setLocalScale(this->localScale);
		// translation.setTranslation(this->localPosition);
		// this->localMatrix = scale * translation * temp;
	}

	float* GameObject::getPhysicsLocalMatrix()
	{
		// Matrix4x4 allMatrix; allMatrix.setIdentity();
		// Matrix4x4 translationMatrix; translationMatrix.setIdentity();
		// translationMatrix.setTranslation(getLocalPosition());
		// Matrix4x4 scaleMatrix; scaleMatrix.setLocalScale(1); //physics 3D only accepts uniform scale for rigidbody
		// Vector3D rotation = getLocalRotation();
		// Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.x);
		// Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.y);
		// Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.z);
		//
		// //Scale --> Rotate --> Transform as recommended order.
		// Matrix4x4 rotMatrix; rotMatrix.setIdentity();
		// rotMatrix = rotMatrix * xMatrix * yMatrix * zMatrix;
		//
		// allMatrix = allMatrix * scaleMatrix * rotMatrix;
		// allMatrix = allMatrix * translationMatrix;
		//
		// return allMatrix.getLocalMatrix();

		Matrix4x4
			translateMatrix,
			scaleMatrix,
			xMatrix,
			yMatrix,
			zMatrix;

		translateMatrix.setTranslation(getLocalPosition());
		scaleMatrix.setScale(getLocalScale());

		zMatrix.setRotationZ(getLocalRotation().z);
		yMatrix.setRotationY(getLocalRotation().y);
		xMatrix.setRotationX(getLocalRotation().x);

		const Matrix4x4 rotateMatrix = xMatrix * yMatrix * zMatrix;
		return (scaleMatrix * rotateMatrix * translateMatrix).getMatrix();
	}

	void GameObject::recalculateChildTransformWithParent(GameObjectPtr parent)
	{
		setLocalPosition(globalPosition - parent->globalPosition);
		setLocalScale(globalPosition / parent->globalScale);
		setLocalRotation(globalRotation - parent->globalRotation);
	}

	void GameObject::recalculateChildTransformWithoutParent()
	{
		localPosition = globalPosition;
		localScale = globalScale;
		localRotation = globalRotation;
		
		updateLocalMatrix();
	}

	void GameObject::attachComponent(Component* component)
	{
		componentList.push_back(component);
		component->attachOwner(this);
	}

	void GameObject::detachComponent(const Component* component)
	{
		const auto it = std::find(componentList.begin(), componentList.end(), component);
		componentList.erase(it);
	}

	void GameObject::setParent(GameObject* parent)
	{
		this->parent = parent;
	}

	void GameObject::detachParent()
	{
		parent = nullptr;
	}

	void GameObject::attachChild(GameObjectPtr child)
	{
		if (child == nullptr || child.get() == this) return;

		if(child->parent != nullptr)
		{
			child->parent->detachChild(child);
		}

		children.push_back(child);
		child->setParent(this);
		child->level = level + 1;
		child->setEnabled(isEnabled);


	}

	void GameObject::detachChild(GameObjectPtr child)
	{
		if (child.get() == this || child == nullptr) return;

		const GameObjectList::iterator it = std::find(children.begin(), children.end(), child);

		if (it != children.end())
		{
			children.erase(it);
		}

		child->level = 0;
		child->setParent(nullptr);
		child->recalculateChildTransformWithoutParent();
	}

	Component* GameObject::findComponentByName(const std::string& name)
	{
		const auto it = std::find_if(componentList.begin(), componentList.end(),
			[name](Component* component)
			{
				return component->getName() == name;
			});

		if (it != componentList.end())
			return *it;

		return nullptr;
	}

	Component* GameObject::findComponentOfType(ComponentType type, const std::string& name)
	{
		const auto it = std::find_if(componentList.begin(), componentList.end(),
			[type, name](Component* component)
			{
				return component->getType() == type && component->getName() == name;
			});

		if (it != componentList.end())
			return *it;

		return nullptr;
	}

	GameObject::ComponentList GameObject::getComponentsOfType(const ComponentType type) const
	{
		ComponentList result;
		result.reserve(componentList.size());

		for (auto component : componentList)
		{
			if (component->getType() == type)
				result.push_back(component);
		}

		return result;
	}

	// TODO: search child GameObjects recursively.
	GameObject::ComponentList GameObject::getComponentsOfTypeRecursive(const ComponentType type) const
	{
		ComponentList result;
		result.reserve(componentList.size());

		for (auto component : componentList)
		{
			if (component->getType() == type)
				result.push_back(component);
		}

		return result;
	}

	void GameObject::saveEditState()
	{
		lastEditState = new EditorAction(this);
	}

	void GameObject::restoreEditState()
	{
		if (lastEditState)
		{
			localPosition = lastEditState->getStoredPosition();
			localScale = lastEditState->getStoredScale();
			orientation = lastEditState->getStoredOrientation();
			localMatrix = lastEditState->getStoredMatrix();

			for (const ComponentList physicsList = getComponentsOfType(ComponentType::PHYSICS);
				Component * component : physicsList)
			{
				PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(component);
				physicsComponent->setTransformFromOpenGL(localMatrix.getMatrix());
				physicsComponent->getRigidBody()->setAngularVelocity(Vector3(0, 0, 0));
				physicsComponent->getRigidBody()->setLinearVelocity(Vector3(0, 0, 0));
			}

			lastEditState = nullptr;
		}
	}

	void GameObject::setUniqueName(const std::string& uniqueName)
	{
		this->name = uniqueName;
	}
}
