#pragma once
#include <string>

#include "ShaderType.h"
namespace mrlol
{
	struct ShaderToCompile
	{
		ShaderType type;
		std::wstring name;
	};
}
