#include "CameraManager.h"
#include "EngineTime.h"
#include "LogUtils.h"

CameraManager* CameraManager::sharedInstance = nullptr;

CameraManager* CameraManager::getInstance()
{
	return sharedInstance;
}

void CameraManager::initialize()
{
	sharedInstance = new CameraManager();
}

void CameraManager::destroy()
{
	delete sharedInstance;
}

void CameraManager::update() const
{
	if (!checkActiveCamera())
		return;

	this->activeCamera->update(EngineTime::getDeltaTime());
}

void CameraManager::setActiveCamera(Camera* newActiveCamera)
{
	activeCamera = newActiveCamera;
}

Matrix4x4 CameraManager::getView() const
{
	if (!checkActiveCamera())
		return {};

	return this->activeCamera->getView();
}

// TODO: FIND CAMERA TAGGED "MAIN" IN SCENE FROM GAME OBJECT MANAGER
CameraManager::CameraManager()
= default;

CameraManager::~CameraManager()
= default;

bool CameraManager::checkActiveCamera() const
{
	if (!activeCamera)
	{
		LogUtils::error(this, "No active camera in scene!");
		return false;
	}

	return true;
}
