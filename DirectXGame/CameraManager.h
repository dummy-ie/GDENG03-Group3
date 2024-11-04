#pragma once
#include "Camera.h"
#include "Matrix4x4.h"


class CameraManager
{
public:
	static CameraManager* getInstance();
	static void initialize();
	static void destroy();

	void update() const;

	void setActiveCamera(Camera* newActiveCamera);
	Matrix4x4 getView() const;

private:
	// Singleton
	CameraManager();
	~CameraManager();
	CameraManager(CameraManager const&) {}
	CameraManager& operator=(CameraManager const&) { }
	static CameraManager* sharedInstance;

	bool checkActiveCamera() const;

public:
	// temporary
	Camera* activeCamera;

};

