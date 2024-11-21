#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager::GameObjectPtr GameObjectManager::findObjectByName(const std::string& name)
{
	return gameObjectMap[name];
}

GameObjectManager::GameObjectList GameObjectManager::getAllObjects()
{
	return gameObjectList;
}

int GameObjectManager::activeObjects() const
{
	return static_cast<int>(gameObjectList.size());
}

void GameObjectManager::updateAll(const float deltaTime) const
{
	for (const auto& gameObject : gameObjectList)
	{
		if (!gameObject->getEnabled())
			continue;

		gameObject->update(deltaTime);
		//LogUtils::log(this, gameObject->getName() + " position: " + gameObject->getPosition().toString());
	}
}

void GameObjectManager::drawAll() const
{
	for (const auto& gameObject : gameObjectList)
	{
		if (!gameObject->getEnabled())
			continue;

		for (const auto renderer : gameObject->getComponentsOfType(ComponentType::RENDERER))
		{
			renderer->update();
			//LogUtils::log(this, "rendering: " + renderer->getName());
		}

	}
}

void GameObjectManager::addObject(const GameObjectPtr& gameObject)
{
	int duplicateCount = 0;
	std::string name = gameObject->getName();
	while (!gameObjectMap.insert(std::make_pair(name, gameObject)).second) // While insertion into the map fails, add number to the gameObject's name
	{
		name = gameObject->getName() + " (" + std::to_string(duplicateCount) + ")";
		duplicateCount++;
	}

	gameObjectList.push_back(gameObject);
}

void GameObjectManager::createObject(const PrimitiveType type, void* shaderByteCode, size_t sizeShader)
{
	switch (type)
	{
	case PrimitiveType::CUBE:
	{
		//const std::shared_ptr<Cube> cube = std::make_shared<Cube>("Cube", shaderByteCode, sizeShader);
		//addObject(cube);
		break;
	}
	case PrimitiveType::PLANE:
	{
		//const std::shared_ptr<Plane> plane = std::make_shared<Plane>("Plane", shaderByteCode, sizeShader);
		//addObject(plane);
		break;
	}
	case PrimitiveType::SPHERE:
	{

		break;
	}
	case PrimitiveType::CAPSULE:
	{

		break;
	}
	}
}

void GameObjectManager::deleteObject(const GameObjectPtr& gameObject)
{
	gameObjectMap.erase(gameObject->getName());
	const GameObjectList::iterator it = std::find(gameObjectList.begin(), gameObjectList.end(), gameObject);

	if (it != gameObjectList.end())
	{
		gameObjectList.erase(it);
	}
}

void GameObjectManager::deleteObjectByName(const std::string& name)
{
	// const GameObjectList::iterator it = std::find_if(
	// 	gameObjectList.begin(),
	// 	gameObjectList.end(),
	// 	[name](const GameObjectPtr& go) {return go->getName() == name; });
	// nvm

	deleteObject(findObjectByName(name));
}

void GameObjectManager::setSelectedObject(const std::string& name)
{
	if (!gameObjectMap[name])
		return;

	setSelectedObject(gameObjectMap[name]);
}

void GameObjectManager::setSelectedObject(const GameObjectPtr& gameObject)
{
	selectedObject = gameObject;
}

GameObjectManager::GameObjectPtr GameObjectManager::getSelectedObject()
{
	return selectedObject;
}

GameObjectManager* GameObjectManager::get()
{
	if (!sharedInstance)
		sharedInstance = new GameObjectManager();

	return sharedInstance;
}

GameObjectManager::GameObjectManager()
= default;

GameObjectManager::~GameObjectManager()
{
	gameObjectMap.clear();
	gameObjectList.clear();

	delete sharedInstance;
}
