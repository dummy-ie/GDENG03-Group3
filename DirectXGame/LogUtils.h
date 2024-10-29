#pragma once
#include <string>
#include <iostream>

#define DEBUG_LOGS true
#define ERROR_LOGS true
#define SUCCESS_LOGS false

class LogUtils
{
public:
	template <class T>
	static void log(T* sender, const std::string& message)
	{
		if (!DEBUG_LOGS)
			return;

		std::cout << "[" << getType(sender) << " DEBUG]: " << message << '\n';
	}

	static void log(const std::string& message)
	{
		if (!DEBUG_LOGS)
			return;

		std::cout << "[DEBUG]: " << message << '\n';
	}

	template <class T>
	static bool log(T* sender, const HRESULT result)
	{
		if (FAILED(result)) {
			const std::string message = std::system_category().message(result);
			log(sender, message);
			throw std::exception(message.data());
			return false;
		}

		if (SUCCESS_LOGS)
			log(sender, "Operation was successful.");

		return true;
	}

	template <class T>
	static void error(T* sender, const std::string& msg)
	{
		if (!ERROR_LOGS)
			return;

		std::string message = "[" + getType(sender) + " ERROR]: " + msg + '\n';
		std::cout << message;
		throw std::exception(message.data());
	}

private:
	template <class T>
	static std::string getType(T* type)
	{
		return typeid(*type).name();
	}
};
