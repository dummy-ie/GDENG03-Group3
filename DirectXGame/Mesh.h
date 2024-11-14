#pragma once

#include "Resource.h"
#include "GameObject.h"
#include "Prerequisites.h"

class Mesh final : public Resource, public GameObject
{
public:
	explicit Mesh(const wchar_t* fullPath, const std::string& name);
	
	const VertexBufferPtr& getVertexBuffer();
	const IndexBufferPtr& getIndexBuffer();
	void update(float deltaTime) override;

	float scaleSpeed = 1.0f;

	bool interpolateScale = false;

	Vector3D scale1;
	Vector3D scale2;

	float deltaScale = 0.0f;

private:
	//VertexBufferPtr vertexBuffer;
	//IndexBufferPtr indexBuffer;

	friend class DeviceContext;
};

