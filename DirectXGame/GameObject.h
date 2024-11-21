#pragma once

#include <vector>
#include <corecrt_math_defines.h>
#include <reactphysics3d/reactphysics3d.h>

#include "Quaternion.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vectors.h"
#include "Vertex.h"
#include "Constant.h"
#include "ConstantBuffer.h"
#include "LogUtils.h"
#include "Material.h"
#include "Component.h"

class GameObject
{
public:
	typedef std::vector<Component*> ComponentList;

	explicit GameObject(std::string name);

	virtual ~GameObject() = default;
	GameObject(GameObject const&) = default;
	GameObject& operator=(GameObject const&) = default;
	GameObject(GameObject&& other) noexcept = default;
	GameObject& operator=(GameObject&& other) noexcept = default;

	virtual void awake() {}
	virtual void update(float deltaTime) {}

	void setPosition(const Vector3D& position);
	void translate(const Vector3D& translation);
	Vector3D getPosition();

	void setScale(const Vector3D& scale);
	void scale(const Vector3D& scale);
	Vector3D getScale();

	void setRotation(const Vector3D& rotation);
	void rotate(const Vector3D& rotation);
	Vector3D getRotation();

	void setEnabled(const bool enabled);
	bool getEnabled() const;

	std::string getName();

	void updateLocalMatrix();
	Matrix4x4 getMatrix() const;
	void setMatrix(float matrix[16]);
	float* getPhysicsLocalMatrix();

	void attachComponent(Component* component);
	void detachComponent(const Component* component);

	Component* findComponentByName(const std::string& name);
	Component* findComponentOfType(ComponentType type, const std::string& name);
	ComponentList getComponentsOfType(ComponentType type) const;
	ComponentList getComponentsOfTypeRecursive(ComponentType type) const;

	//reactphysics3d::Transform transform;

protected:
	float elapsedTime = 0.f;

	std::string name;
	bool isEnabled = true;

	Vector3D localScale = 1.f;
	Vector3D localPosition = 0.f;
	Vector3D localRotation = 0.f;
	Matrix4x4 localMatrix;
	Quaternion orientation;


	ComponentList componentList;

	friend class GameObjectManager;
};
