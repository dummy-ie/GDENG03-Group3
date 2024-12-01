#pragma once
#include <string>

#include "ShaderType.h"
namespace gdeng03
{
	struct ShaderToCompile
	{
		ShaderType type;
		std::wstring name;
	};
}
