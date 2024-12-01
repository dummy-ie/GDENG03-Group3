#pragma once
#include <string>
#include <iostream>
#include <winerror.h>

#define DEBUG_LOGS true
#define ERROR_LOGS true
#define SUCCESS_LOGS false

namespace gdeng03
{
	class LogUtils
	{
	public:
		template <class T>
		static void log(T* sender, const std::string& message)
		{
			if constexpr (!DEBUG_LOGS)
				return;

			std::string finalMessage = "[" + getType(sender) + " DEBUG]: " + message + '\n';
			logToConsole(finalMessage);
			std::cout << finalMessage;
		}

		static void log(const std::string& message)
		{
			if constexpr (!DEBUG_LOGS)
				return;

			std::string finalMessage = "[DEBUG]: " + message + '\n';
			logToConsole(finalMessage);
			std::cout << finalMessage;
		}

		template <class T>
		static bool logHResult(T* sender, const long hResult)
		{
			if (FAILED(hResult)) {
				const std::string message = std::system_category().message(hResult);
				log(sender, message);
				throw std::exception(message.data());
				return false;
			}

			if constexpr (SUCCESS_LOGS)
				log(sender, "Operation was successful.");

			return true;
		}

		template <class T>
		static bool logBool(T* sender, const bool bResult, const bool throwExcept = true)
		{
			if (!bResult) {
				std::string message = "[" + std::to_string(bResult) + "] Operation failed!";
				log(sender, message);

				if (throwExcept)
					throw std::exception(message.data());

				return false;
			}

			if constexpr (SUCCESS_LOGS)
				log(sender, "Operation was successful.");

			return true;
		}

		template <class T>
		static void error(T* sender, const std::string& msg)
		{
			if constexpr (!ERROR_LOGS)
				return;

			std::string message = "[" + getType(sender) + " ERROR]: " + msg + '\n';
			std::cout << message;
			throw std::exception(message.data());
		}

		static void error(const std::string& msg)
		{
			if constexpr (!ERROR_LOGS)
				return;

			std::string message = "[ERROR]: " + msg + '\n';
			std::cout << message;
			throw std::exception(message.data());
		}

	private:
		template <class T>
		static std::string getType(T* type)
		{
			return typeid(*type).name();
		}

		static void logToConsole(const std::string& message);
	};
}
