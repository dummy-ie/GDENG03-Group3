#pragma once
#include "Camera.h"
#include "Matrix4x4.h"
#include "SceneCamera.h"

namespace mrlol
{
	class CameraManager
	{
		typedef std::vector<Camera*> CameraList;
		typedef std::vector<SceneCamera*> SceneCameraList;

	public:
		void update() const;

		void setActiveCamera(Camera* newActiveCamera);
		Matrix4x4 getView() const;

		Matrix4x4 getMainCameraView() const;
		Matrix4x4 getMainCameraProjection() const;
		Matrix4x4 getSceneCameraView() const;
		Matrix4x4 getSceneCameraProjection() const;
		SceneCamera* getSceneCamera() const;
		SceneCamera* getSceneCameraByIndex(int index);
		std::vector<SceneCamera*> getSceneCameras();
		void setMainCamera(Camera* camera);
		void setMainCameraByIndex(int index);
		void setSceneCameraProjection(int type) const;
		void updateSceneCamera(float deltaTime) const;
		void addCamera(Camera* camera);
		void addSceneCamera(SceneCamera* camera);
		void removeSceneCamera(SceneCamera* camera);
		void removeCamera(Camera* camera);

	private:
		bool checkActiveCamera() const;


	private:
		SceneCamera* activeSceneCamera;
		Camera* activeCamera;
		CameraList cameraList;
		SceneCameraList sceneCameraList;

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
}

