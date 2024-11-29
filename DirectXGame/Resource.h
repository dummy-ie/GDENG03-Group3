#pragma once
#include <string>

namespace mrlol
{
	class Resource
	{
	public:
		explicit Resource(const wchar_t* fullPath);
		virtual ~Resource() = default;
		Resource(Resource const&) = default;
		Resource& operator=(Resource const&) = default;
		Resource(Resource&& other) noexcept = default;
		Resource& operator=(Resource&& other) noexcept = default;

	protected:
		std::wstring fullPath;
	};
}

