#pragma once

#include <cstdint>

namespace mrlol
{
	enum class PrimitiveType : std::uint8_t
	{
		CUBE,
		PLANE,
		SPHERE,
		CAPSULE
	};
}