#pragma once

#include <cstdint>

enum class ComponentType : std::int8_t
{
	NOT_SET = -1,
	SCRIPT,
	RENDERER,
	INPUT,
	PHYSICS
};

inline const char* ToString(const ComponentType e)
{
	switch (e)
	{
	case ComponentType::NOT_SET: return "Not Set";
	case ComponentType::SCRIPT: return "Script";
	case ComponentType::RENDERER: return "Renderer";
	case ComponentType::INPUT: return "Input";
	case ComponentType::PHYSICS: return "Physics";
	default: return "Unknown Component Type";
	}
}
