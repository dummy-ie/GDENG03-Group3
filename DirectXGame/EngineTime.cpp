#include "EngineTime.h"

namespace mrlol
{
	EngineTime* EngineTime::sharedInstance = nullptr;

	void EngineTime::initialize()
	{
		sharedInstance = new EngineTime();
	}

	double EngineTime::getDeltaTimeDouble()
	{
		return sharedInstance->deltaTime;
	}

	float EngineTime::getDeltaTime()
	{
		return static_cast<float>(sharedInstance->deltaTime);
	}

	EngineTime::EngineTime()
		= default;

	EngineTime::~EngineTime()
		= default;

	void EngineTime::logFrameStart()
	{
		sharedInstance->start = std::chrono::system_clock::now();
	}

	void EngineTime::logFrameEnd()
	{
		sharedInstance->end = std::chrono::system_clock::now();
		const std::chrono::duration<double> elapsedSeconds = sharedInstance->end - sharedInstance->start;

		sharedInstance->deltaTime = elapsedSeconds.count();
	}
}
