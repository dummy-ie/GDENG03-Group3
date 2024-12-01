#pragma once

#include <cstdint>

namespace gdeng03
{
	enum class PrimitiveType : std::uint8_t
	{
		CUBE,
		PLANE,
		SPHERE,
		CAPSULE
	};
}