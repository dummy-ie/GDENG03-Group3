#include "SceneManager.h"
#include "GameObjectManager.h"

namespace gdeng03
{
	using namespace std;

	SceneManager* SceneManager::sharedInstance = nullptr;



	void SceneManager::readFile()
	{	
	}

	void SceneManager::writeFile()
	{
		String fileDir = this->directory + ".iet";

		ofstream sceneFile;

		sceneFile.open(fileDir, std::ios::out);

		std::cout << "Selected filename" << fileDir << "\n";

		GameObjectManager::GameObjectList allObjects = GameObjectManager::get()->getAllObjects();

		for (int i = 0; i < allObjects.size(); i++) {
			sceneFile << allObjects[i]->getDisplayName() << std::endl;
			sceneFile << allObjects[i]->getUniqueName() << std::endl;
			Vector3D position = allObjects[i]->getLocalPosition();
			Vector3D rotation = allObjects[i]->getLocalRotation();
			Vector3D scale = allObjects[i]->getLocalScale();

			//sceneFile << "Type: " << allObjects[i]->getPrimitiveType() << std::endl;
			sceneFile << "Position: " << position.x << " " << position.y << position.z << std::endl;
			sceneFile << "Rotation: " << rotation.x << " " << rotation.y << rotation.z << std::endl;
			sceneFile << "Scale: " << scale.x << " " << scale.y << scale.z << std::endl;

		}

		sceneFile.close();

	}

	SceneManager* SceneManager::getInstance()
	{
		return sharedInstance;
	}

	SceneManager::SceneManager()
		= default;

	SceneManager::~SceneManager()
	{
		delete sharedInstance;
	}
}