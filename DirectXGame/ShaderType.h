#pragma once

#include <cstdint>

namespace mrlol {
	enum class ShaderType : std::uint8_t
	{
		VERTEX,
		GEOMETRY,
		PIXEL
	};
}