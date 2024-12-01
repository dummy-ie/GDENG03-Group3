#pragma once

#include <cstdint>
#include "LogUtils.h"

namespace gdeng03
{
	enum class PrimitiveType : std::uint8_t
	{
		NOT_PRIMITIVE = 0, // NOT a primitive, it is from an .obj file
		CUBE,
		PLANE,
		SPHERE,
		CAPSULE
	};

	inline const wchar_t* toString(const PrimitiveType pt)
	{
		switch (pt)
		{
		case PrimitiveType::NOT_PRIMITIVE:
			return L"Not_Primitive";
		case PrimitiveType::CUBE:
			return L"Cube";
		case PrimitiveType::PLANE:
			return L"Plane";
		case PrimitiveType::SPHERE:
			return L"Sphere";
		case PrimitiveType::CAPSULE:
			return L"Capsule";
		}

		LogUtils::error("Invalid PrimitiveType found!");
		return nullptr;
	}
}
