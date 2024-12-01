#pragma once
#include <ctime>
#include <chrono>
#include <iostream>

namespace gdeng03
{
	class Window;

	class EngineTime
	{
	public:
		static void initialize();
		static double getDeltaTimeDouble();
		static float getDeltaTime();

		EngineTime(EngineTime const&) = delete;
		EngineTime& operator=(EngineTime const&) = delete;
		EngineTime(EngineTime&& other) noexcept = delete;
		EngineTime& operator=(EngineTime&& other) noexcept = delete;

	private:
		EngineTime();
		~EngineTime();
		static EngineTime* sharedInstance;

		static void logFrameStart();
		static void logFrameEnd();

		std::chrono::system_clock::time_point start;
		std::chrono::system_clock::time_point end;

		double deltaTime = 0.0;

		friend class Window;
	};
}

