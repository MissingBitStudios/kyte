#pragma once

#include <string>
#include <vector>

namespace kyte
{
	struct SourceFile
	{
		std::string name;
		std::string source;
	};

	std::vector<uint32_t> compile(const std::vector<SourceFile>& sourceFiles);
} // namespace kyte
