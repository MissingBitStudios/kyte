#include "kyte_p.hpp"

#include <spirv-tools/libspirv.hpp>
#include <spirv-tools/optimizer.hpp>
#include <spirv-tools/linker.hpp>

#include <spirv_parser.hpp>
#include <spirv_glsl.hpp>
#include <spirv_msl.hpp>
#include <spirv_hlsl.hpp>

#include <iostream>

namespace kyte
{
	bool compile(const std::string& source, const std::vector<Target>& targets)
	{
		spv_target_env env = SPV_ENV_UNIVERSAL_1_5;
		spvtools::SpirvTools core(env);
		spvtools::Optimizer opt(env);

		auto print_msg_to_stderr = [](spv_message_level_t, const char*,
			const spv_position_t&, const char* m) {
				std::cerr << "error: " << m << std::endl;
		};

		core.SetMessageConsumer(print_msg_to_stderr);
		opt.SetMessageConsumer(print_msg_to_stderr);

		std::vector<uint32_t> binary;
		if (!core.Assemble(source, &binary)) return false;
		if (!core.Validate(binary)) return false;
		if (!opt.Run(binary.data(), binary.size(), &binary)) return false;

		std::string disassembly;
		if (!core.Disassemble(binary, &disassembly)) return 1;
		std::cout << disassembly << "\n";

		return true;
	}
}
