#pragma once
#include "Camera.h"
#include "Matrix4x4.h"


class CameraManager
{
public:
	void update() const;

	void setActiveCamera(Camera* newActiveCamera);
	Matrix4x4 getView() const;

private:
	bool checkActiveCamera() const;

public:
	// temporary
	Camera* activeCamera;

	// Singleton
public:
	static CameraManager* getInstance()
	{
		if (!sharedInstance)
			sharedInstance = new CameraManager();

		return sharedInstance;
	}

	CameraManager(CameraManager const&) = delete;
	CameraManager& operator=(CameraManager const&) = delete;
	CameraManager(CameraManager&& other) noexcept = delete;
	CameraManager& operator=(CameraManager&& other) noexcept = delete;

private:
	CameraManager();
	~CameraManager();
	static CameraManager* sharedInstance;
};

