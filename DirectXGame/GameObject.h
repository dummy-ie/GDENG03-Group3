#pragma once
using namespace std;

#include <string>;
#include <Windows.h>

#include "Matrix4x4.h"

class VertexShader;
class PixelShader;

struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};


__declspec(align(16))
struct CBData
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};

class GameObject
{
public:
	GameObject(std::wstring name);
	~GameObject();

	virtual void update(float deltaTime, RECT windowBounds) = 0;
	virtual void draw(int width, int height, float deltaTime, VertexShader* vertexShader, PixelShader* pixelShader) = 0;

public:
	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

protected:
	std::wstring name;
	Vector3D localRotation;
	Vector3D localPosition;
	Vector3D localScale;

};

