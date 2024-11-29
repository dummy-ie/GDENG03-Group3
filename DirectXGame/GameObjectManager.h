#pragma once

#include <unordered_map>

#include "PrimitiveType.h"
#include "GameObject.h"

namespace mrlol
{
	class GameObjectManager
	{
	public:
		typedef std::shared_ptr<GameObject> GameObjectPtr;
		typedef std::vector<GameObjectPtr> GameObjectList;
		typedef std::unordered_map<std::string, GameObjectPtr> GameObjectHashMap;

		GameObjectPtr findObjectByName(const std::string& name);
		GameObjectList getAllObjects();
		int activeObjects() const;

		void updateAll(float deltaTime) const;
		void drawAll(int width, int height) const;

		void addObject(const GameObjectPtr& gameObject);
		void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
		void deleteObject(const GameObjectPtr& gameObject);
		void deleteObjectByName(const std::string& name);
		void setSelectedObject(const std::string& name);
		void setSelectedObject(GameObject* gameObject);
		GameObject* getSelectedObject() const;

		void saveEditStates();
		void restoreEditStates();

		static GameObjectManager* get();

		GameObjectManager(GameObjectManager const&) = delete;
		GameObjectManager& operator=(GameObjectManager const&) = delete;
		GameObjectManager(GameObjectManager&& other) noexcept = delete;
		GameObjectManager& operator=(GameObjectManager&& other) noexcept = delete;

	private:
		GameObjectManager();
		~GameObjectManager();
		static GameObjectManager* sharedInstance;

		GameObjectHashMap gameObjectMap;
		GameObjectList gameObjectList;

		GameObject* selectedObject = nullptr;

	};
}

