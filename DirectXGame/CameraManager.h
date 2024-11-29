#pragma once
#include "Camera.h"
#include "Matrix4x4.h"
#include "SceneCamera.h"
#include "Prerequisites.h"

namespace mrlol
{
	class CameraManager
	{
		typedef std::vector<CameraPtr> CameraList;
		typedef std::vector<SceneCameraPtr> SceneCameraList;

	public:
		void update() const;

		void setActiveCamera(const CameraPtr& newActiveCamera);
		Matrix4x4 getView() const;

		Matrix4x4 getMainCameraView() const;
		Matrix4x4 getMainCameraProjection() const;
		Matrix4x4 getActiveSceneCameraView() const;
		Matrix4x4 getActiveSceneCameraProjection() const;
		SceneCameraPtr getActiveSceneCamera() const;
		SceneCameraPtr getSceneCameraByIndex(int index);
		SceneCameraList getSceneCameras();
		void setMainCamera(const CameraPtr& camera);
		void setMainCameraByIndex(int index);
		void setSceneCameraProjection(int type) const;
		void updateSceneCamera(float deltaTime) const;
		void addCamera(const CameraPtr& camera);
		void addSceneCamera(const SceneCameraPtr& camera);
		void removeSceneCamera(const SceneCameraPtr& camera);
		void removeCamera(const CameraPtr& camera);

	private:
		bool checkActiveCamera() const;


	private:
		SceneCameraPtr activeSceneCamera;
		CameraPtr activeCamera;
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

