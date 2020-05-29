#include "kyte_p.hpp"

#include <iostream> // std::cout, std::cerr, std::endl

namespace kyte
{
	std::vector<uint32_t> Compiler::compile(const std::string& source) const
	{
		// AST Transform
		// parse(source);

		CodeGenerator cg;

		std::vector<uint32_t> binary = cg.generate(options);

		if (options.validate || options.showDisassembly)
		{
			spvtools::SpirvTools core(kyte::SpvTargetEnv);

			auto print_msg_to_stderr = [](spv_message_level_t, const char*,
				const spv_position_t&, const char* m) {
					std::cerr << "error: " << m << std::endl;
			};

			core.SetMessageConsumer(print_msg_to_stderr);

			// Validation
			if (options.validate)
			{
				if (!core.Validate(binary)) throw std::exception();
			}

			// Disassembly
			if (options.showDisassembly)
			{
				std::string disassembly;
				if (!core.Disassemble(binary, &disassembly)) throw std::exception();
				std::cout << disassembly << "\n";
			}
		}

		return binary;
	}

	const Options& Compiler::getOptions() const
	{
		return options;
	}

	void Compiler::setOptions(const Options& newOptions)
	{
		if (newOptions.optimizationLevel < 0 || newOptions.optimizationLevel > 4)
		{
			throw std::exception("Invalid optimization level");
		}
		options = newOptions;
	}
} // namespace kyte
