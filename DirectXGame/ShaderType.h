#pragma once

#include <cstdint>

namespace gdeng03 {
	enum class ShaderType : std::uint8_t
	{
		VERTEX,
		GEOMETRY,
		PIXEL
	};
}