#pragma once

#include <string>
#include <vector>

namespace kyte
{
	enum class Platform : uint8_t
	{
		SPIRV,
		GLSL,
		ESSL,
		ASMJS,
		HLSL,
		MSL
	};

	struct Target
	{
		Platform platform;
	};

	bool compile(const std::string& source, const std::vector<Target>& targets);
}
