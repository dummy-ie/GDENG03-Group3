#pragma once



#include <unordered_map>
#include <iostream>
#include <fstream>
#include "PrimitiveType.h"
#include "GameObject.h"
#include <string>
#include "StringUtils.h"
#include "Renderer3D.h";
#include "Mesh.h"
namespace gdeng03
{
	class SceneManager
	{
	public:
		typedef std::string String;

		void readFile();
		void writeFile();
		void setSaveDirectory(String filePath);

		static SceneManager* getInstance();

		SceneManager(SceneManager const&) = delete;
		SceneManager& operator=(SceneManager const&) = delete;
		SceneManager(SceneManager&& other) noexcept = delete;
		SceneManager& operator=(SceneManager&& other) noexcept = delete;

	private:
		SceneManager();
		~SceneManager();
		String directory = "assets/scenes/test";
		static SceneManager* sharedInstance;

	};
}
