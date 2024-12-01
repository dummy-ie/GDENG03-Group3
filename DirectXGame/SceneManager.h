#pragma once



#include <unordered_map>
#include <iostream>
#include <fstream>
#include "PrimitiveType.h"
#include "GameObject.h"
#include <string>
#include "StringUtils.h"

namespace gdeng03
{
	class SceneManager
	{
	public:
		typedef std::string String;

		void readFile();
		void writeFile();

		static SceneManager* getInstance();

		SceneManager(SceneManager const&) = delete;
		SceneManager& operator=(SceneManager const&) = delete;
		SceneManager(SceneManager&& other) noexcept = delete;
		SceneManager& operator=(SceneManager&& other) noexcept = delete;

	private:
		SceneManager(String directory);
		~SceneManager();
		String directory;
		static SceneManager* sharedInstance;

	};
}
