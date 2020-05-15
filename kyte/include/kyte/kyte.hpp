#pragma once

#include <string>
#include <vector>

namespace kyte
{
	const uint32_t MagicNumber = 23;
	const uint32_t Version = 1;
	const uint32_t SourceLanguageKyte = 0;

	struct SourceFile
	{
		std::string name;
		std::string source;
	};

	std::vector<uint32_t> compile(const std::vector<SourceFile>& sourceFiles);
} // namespace kyte
