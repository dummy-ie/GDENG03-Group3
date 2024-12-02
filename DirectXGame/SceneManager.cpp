#include "SceneManager.h"

#include <utility>

#include "GameObjectManager.h"
#include "PrimitiveType.h"
#include "ComponentType.h"


namespace gdeng03
{
	using namespace std;

	SceneManager* SceneManager::sharedInstance = nullptr;

	void SceneManager::readFile()
	{	
		String fileDir = this->directory + ".iet";
		if (this->directory.find(".iet") != String::npos) {
			fileDir = this->directory; 
		}

		std::fstream sceneFile;
		sceneFile.open(fileDir, std::ios::in);

		int index = 0;
		String readLine;

		String objectName;
		PrimitiveType objectType;
		Vector3D position;
		Vector3D rotation;
		Vector3D scale;
		while (std::getline(sceneFile, readLine)) {
			if (index == 0) {
				objectName = readLine;
				index++;
			}
			else if (index == 1) {
				std::vector stringSplit = StringUtils::split(readLine, ' ');
				objectType = (PrimitiveType)std::stoi(stringSplit[1]);
				index++;
			}
			else if (index == 2) {
				std::vector stringSplit = StringUtils::split(readLine, ' ');
				position = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
				index++;
			}
			else if (index == 3) {
				std::vector stringSplit = StringUtils::split(readLine, ' ');
				rotation = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
				index++;
			}
			else if (index == 4) {
				std::vector stringSplit = StringUtils::split(readLine, ' ');
				scale = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
				index = 0;

				//GameObjectManager::get()->createObject(objectName, objectType, position, rotation, scale); //NOTE -> CREATE OBJECT FROM FILE FUNCTION MUST BE MADE
			}
		}
	}

	void SceneManager::writeFile()
	{
		String fileDir = this->directory + ".iet";

		std::fstream sceneFile;

		sceneFile.open(fileDir, std::ios::out);

		std::cout << "Selected filename" << fileDir << "\n";

		GameObjectManager::GameObjectList allObjects = GameObjectManager::get()->getAllObjects();

		for (int i = 0; i < allObjects.size(); i++) {
			sceneFile << allObjects[i]->getDisplayName() << std::endl;
			sceneFile << allObjects[i]->getUniqueName() << std::endl;
			Vector3D position = allObjects[i]->getLocalPosition();
			Vector3D rotation = allObjects[i]->getLocalRotation();
			Vector3D scale = allObjects[i]->getLocalScale();
			GameObject::ComponentList rendererList = allObjects[i]->getComponentsOfType(ComponentType::RENDERER);
		
			Renderer3D* renderer = nullptr;

			// Retrieve the first renderer component
			for (auto component : rendererList) {
				renderer = dynamic_cast<Renderer3D*>(component);
				if (renderer != nullptr) {
					break; // Exit loop once the first valid renderer is found
				}
			}

			PrimitiveType type = renderer->getMesh()->getType();


			sceneFile << "Type: " << (int)type << std::endl;
			sceneFile << "Position: " << position.x << " " << position.y << position.z << std::endl;
			sceneFile << "Rotation: " << rotation.x << " " << rotation.y << rotation.z << std::endl;
			sceneFile << "Scale: " << scale.x << " " << scale.y << scale.z << std::endl;

		}

		sceneFile.close();

	}

	void SceneManager::setSaveDirectory(String filePath)
	{
		this->directory = std::move(filePath);
	}

	SceneManager* SceneManager::getInstance()
	{
		if (!sharedInstance)
			sharedInstance = new SceneManager();

		return sharedInstance;
	}

	SceneManager::SceneManager() 
	{
		LogUtils::log(this, " created");
	}

	SceneManager::~SceneManager()
	{
		delete sharedInstance;
	}
}