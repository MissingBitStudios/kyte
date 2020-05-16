#pragma once

#include <string>
#include <vector>

namespace kyte
{
	struct Options
	{
		bool debugInfo = false;
		uint8_t optimizationLevel = 0;
	};

	class Compiler
	{
	public:
		std::vector<uint32_t> compile(const std::string& source);
		const Options& getOptions() const;
		void setOptions(const Options& newOptions);
	protected:
		virtual std::string resolve(const std::string& module) = 0;
	private:
		std::string loadModule(const std::string& module);
		std::vector<std::string> visitedModules;
		Options options;
	};
} // namespace kyte
