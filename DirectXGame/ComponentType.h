#pragma once

#include <cstdint>

enum ComponentType : std::int8_t
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
	case NOT_SET: return "Not Set";
	case SCRIPT: return "Script";
	case RENDERER: return "Renderer";
	case INPUT: return "Input";
	case PHYSICS: return "Physics";
	default: return "Unknown Component Type";
	}
}
