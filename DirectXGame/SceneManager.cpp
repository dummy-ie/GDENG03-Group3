#include "SceneManager.h"

#include <utility>

#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "MeshManager.h"
#include "PrimitiveType.h"
#include "ComponentType.h"


namespace gdeng03
{
	using namespace std;

	SceneManager* SceneManager::sharedInstance = nullptr;

	void SceneManager::readFile()
	{
		String fileDir = this->directory + ".level";
		if (this->directory.find(".level") != String::npos) {
			fileDir = this->directory;
		}

		std::fstream sceneFile;
		sceneFile.open(fileDir, std::ios::in);

		GameObjectManager::get()->deleteScene();

		int index = 0;
		String readLine;

		String objectName;
		String uniqueName;
		PrimitiveType objectType;
		Vector3D position;
		Vector3D rotation;
		Vector3D scale;
		bool hasPhysicsEnabled = false;

		while (std::getline(sceneFile, readLine)) {
			if (index == 0) {
				objectName = readLine;
				index++;
			}

			else if (index == 1) {
				uniqueName = readLine;
				index++;
			}
			else if (index == 2) {
				std::vector stringSplit = StringUtils::split(readLine, ' ');
				objectType = static_cast<PrimitiveType>(std::stoi(stringSplit[1]));
				index++;
			}
			else if (index == 3) {
				std::vector stringSplit = StringUtils::split(readLine, ' ');
				position = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
				index++;
			}
			else if (index == 4) {
				std::vector stringSplit = StringUtils::split(readLine, ' ');
				rotation = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
				index++;
			}
			else if (index == 5) {
				std::vector stringSplit = StringUtils::split(readLine, ' ');
				scale = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
				index++;
			}

			//check if physics is enabled
			else if (index == 6) {

				//check for physics component as the last check
				std::vector stringSplit = StringUtils::split(readLine, ' ');
				hasPhysicsEnabled = static_cast<bool>(std::stoi(stringSplit[2]));

				GameObjectPtr savedObject;
				MeshPtr savedMesh;
				savedObject = std::make_shared<GameObject>(objectName);
				savedObject->setUniqueName(uniqueName);
				savedMesh = GraphicsEngine::get()->getMeshManager()->createMeshFromPrimitiveType(objectType);
				savedObject->attachComponent(new Renderer3D(savedObject.get(), savedMesh));
				savedObject->setLocalPosition(position);
				rotation = rotation * (M_PI / 180.f);
				savedObject->setLocalRotation(rotation);
				savedObject->setLocalScale(scale);
				PhysicsComponent* physics = new PhysicsComponent(savedObject.get(), objectType);
				
				if (!hasPhysicsEnabled) {
					physics->getRigidBody()->setType(BodyType::STATIC);
				}
				savedObject->attachComponent(physics);

				// if (hasPhysicsEnabled)
				// {
				// 	PhysicsComponent* physics = new PhysicsComponent(savedObject.get(), objectType);
				// 	savedObject->attachComponent(physics);
				// }


				GameObjectManager::get()->addObject(savedObject);

				index = 0;

			}
		}
	}

	void SceneManager::writeFile()
	{
		const String fileDir = this->directory + ".level";

		std::fstream sceneFile;

		sceneFile.open(fileDir, std::ios::out);

		std::cout << "Selected filename" << fileDir << "\n";

		const GameObjectManager::GameObjectList allObjects = GameObjectManager::get()->getAllObjects();

		for (int i = 0; i < allObjects.size(); i++) {
			sceneFile << allObjects[i]->getDisplayName() << std::endl;
			sceneFile << allObjects[i]->getUniqueName() << std::endl;

			Vector3D position = allObjects[i]->getLocalPosition();
			Vector3D rotation = allObjects[i]->getLocalRotation();
			Vector3D scale = allObjects[i]->getLocalScale();
			if (allObjects[i]->getParent() != nullptr) {
				position = allObjects[i]->getGlobalPosition();
				rotation = allObjects[i]->getGlobalRotation();
				scale = allObjects[i]->getGlobalScale();
			}
			rotation = rotation * (180 / M_PI);

			GameObject::ComponentList rendererList = allObjects[i]->getComponentsOfType(ComponentType::RENDERER);
			GameObject::ComponentList physicsList = allObjects[i]->getComponentsOfType(ComponentType::PHYSICS);
			const Renderer3D* renderer = nullptr;
			bool hasPhysicsSystem = false;

			// Retrieve the first renderer component
			for (const auto component : rendererList) {
				renderer = dynamic_cast<Renderer3D*>(component);
				if (renderer != nullptr) {
					break; // Exit loop once the first valid renderer is found
				}
			}

			PrimitiveType type = renderer->getMesh()->getType();


			if (!physicsList.empty()) {
				const PhysicsComponent* physics = nullptr;
				// Retrieve the first renderer component
				for (const auto component : physicsList) {
					physics = dynamic_cast<PhysicsComponent*>(component);
					if (physics != nullptr) {
						break; // Exit loop once the first valid physics component is found
					}
				}

				hasPhysicsSystem = physics->getBodyType() == BodyType::DYNAMIC;
			}

			else {
				hasPhysicsSystem = false;
			}


			sceneFile << "Type: " << (int)type << std::endl;
			sceneFile << "Position: " << position.x << " " << position.y << " " << position.z << std::endl;
			sceneFile << "Rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;
			sceneFile << "Scale: " << scale.x << " " << scale.y << " " << scale.z << std::endl;
			sceneFile << "Physics Enabled: " << (int)hasPhysicsSystem << std::endl;

		}

		sceneFile.close();

	}

	void SceneManager::setSaveDirectory(String filePath)
	{
		this->directory = std::move(filePath);
	}

	SceneManager::String SceneManager::getSaveDirectiory()
	{
		return this->directory;
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