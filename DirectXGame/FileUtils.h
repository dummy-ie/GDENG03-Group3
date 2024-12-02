#pragma once

#include <fstream>
#include <windows.h>
#include <commdlg.h>
#include <iostream>


class FileUtils
{
	public:

	static void getFilePath(std::string& filePath);
	void getFilePath(std::string* filePath);
};

