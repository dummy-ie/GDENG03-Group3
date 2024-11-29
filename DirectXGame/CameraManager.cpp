#include "CameraManager.h"
#include "EngineTime.h"
#include "LogUtils.h"

namespace mrlol
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

	Matrix4x4 CameraManager::getSceneCameraView() const
	{
		return activeSceneCamera->getView();
	}

	Matrix4x4 CameraManager::getSceneCameraProjection() const
	{
		return activeSceneCamera->getProjection();
	}

	SceneCamera* CameraManager::getSceneCamera() const
	{
		return activeSceneCamera;
	}

	SceneCamera* CameraManager::getSceneCameraByIndex(const int index)
	{
		if (index > sceneCameraList.size())
		{
			LogUtils::log(this, "Camera Index over Cameras in system");
			return nullptr;
		}
		return sceneCameraList[index];
	}

	std::vector<SceneCamera*> CameraManager::getSceneCameras()
	{
		return sceneCameraList;
	}

	void CameraManager::setMainCamera(Camera* camera)
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

	void CameraManager::addCamera(Camera* camera)
	{
		if (!activeCamera)
			setMainCamera(camera);
		cameraList.push_back(camera);
	}

	void CameraManager::addSceneCamera(SceneCamera* camera)
	{
		if (!activeSceneCamera)
			activeSceneCamera = camera;

		this->sceneCameraList.push_back(camera);
	}

	void CameraManager::removeSceneCamera(SceneCamera* camera)
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

	void CameraManager::removeCamera(Camera* camera)
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
