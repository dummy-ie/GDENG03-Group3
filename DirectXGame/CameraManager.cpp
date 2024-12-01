#include "CameraManager.h"
#include "EngineTime.h"
#include "LogUtils.h"

namespace gdeng03
{
	CameraManager* CameraManager::sharedInstance = nullptr;

	Matrix4x4 CameraManager::getMainCameraView() const
	{
		return activeCamera->getView();
	}

	Matrix4x4 CameraManager::getMainCameraProjection() const
	{
		return activeCamera->getProjection();
	}

	Matrix4x4 CameraManager::getActiveSceneCameraView() const
	{
		return activeSceneCamera->getView();
	}

	Matrix4x4 CameraManager::getActiveSceneCameraProjection() const
	{
		return activeSceneCamera->getProjection();
	}

	SceneCameraPtr CameraManager::getActiveSceneCamera() const
	{
		return activeSceneCamera;
	}

	SceneCameraPtr CameraManager::getSceneCameraByIndex(const int index)
	{
		if (index > sceneCameraList.size())
		{
			LogUtils::log(this, "Camera Index over Cameras in system");
			return nullptr;
		}
		return sceneCameraList[index];
	}

	CameraManager::SceneCameraList CameraManager::getSceneCameras()
	{
		return sceneCameraList;
	}

	void CameraManager::setMainCamera(const CameraPtr& camera)
	{
		activeCamera = camera;
	}

	void CameraManager::setMainCameraByIndex(const int index)
	{
		if (index > cameraList.size())
		{
			LogUtils::log(this, "Camera Index over Cameras in system");
			return;
		}
		setMainCamera(cameraList[index]);
	}

	void CameraManager::setSceneCameraProjection(const int type) const
	{
		activeSceneCamera->setProjectionType(type);
	}

	void CameraManager::updateSceneCamera(float deltaTime) const
	{
		activeSceneCamera->update(deltaTime);
	}

	void CameraManager::addCamera(const CameraPtr& camera)
	{
		if (!activeCamera)
			setMainCamera(camera);
		cameraList.push_back(camera);
	}

	void CameraManager::addSceneCamera(const SceneCameraPtr& camera)
	{
		if (!activeSceneCamera)
			activeSceneCamera = camera;

		this->sceneCameraList.push_back(camera);
	}

	void CameraManager::removeSceneCamera(const SceneCameraPtr& camera)
	{
		std::string name = camera->getUniqueName();
		int index = -1;

		for (int i = 0; i < this->sceneCameraList.size() && index == -1; i++)
		{
			if (this->sceneCameraList[i] == camera)
				index = i;
		}

		if (index != -1)
		{
			this->sceneCameraList.erase(this->sceneCameraList.begin() + index);
		}
	}

	void CameraManager::removeCamera(const CameraPtr& camera)
	{
		std::string name = camera->getUniqueName();
		int index = -1;

		for (int i = 0; i < this->cameraList.size() && index == -1; i++)
		{
			if (this->cameraList[i] == camera)
				index = i;
		}

		if (index != -1)
		{
			this->cameraList.erase(this->cameraList.begin() + index);
		}
	}

	void CameraManager::update() const
	{
		if (!checkActiveCamera())
			return;

		this->activeCamera->update(EngineTime::getDeltaTime());
	}

	void CameraManager::setActiveCamera(const CameraPtr& newActiveCamera)
	{
		activeCamera = newActiveCamera;
	}

	Matrix4x4 CameraManager::getView() const
	{
		if (!checkActiveCamera())
			return {};

		return this->activeCamera->getView();
	}

	CameraManager::CameraManager() = default;

	CameraManager::~CameraManager()
	{
		delete sharedInstance;
	};

	bool CameraManager::checkActiveCamera() const
	{
		if (!activeCamera)
		{
			LogUtils::error(this, "No active camera in scene!");
			return false;
		}

		return true;
	}
}
