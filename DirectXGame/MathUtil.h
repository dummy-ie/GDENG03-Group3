#pragma once
#include <random>


namespace mrlol
{
	static int randomRangeInt(const int start, const int end) {
		std::random_device dev;
		std::mt19937 generator(dev());
		std::uniform_int_distribution<int> distribution(start, end);
		return distribution(generator);
	}

	static float randomRangeFloat(const float start, const float end) {
		std::random_device dev;
		std::mt19937 generator(dev());
		std::uniform_real_distribution<float> distribution(start, end);
		return distribution(generator);
	}

	static Vector3D randomRangeVector3D(const float start, const float end)
	{
		return { randomRangeFloat(start, end), randomRangeFloat(start, end), randomRangeFloat(start, end) };
	}
}