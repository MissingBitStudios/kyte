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

		spirv_cross::Parser parser(std::move(binary));
		parser.parse();

		std::unique_ptr<spirv_cross::CompilerGLSL> compiler;

		for (Target target : targets)
		{
			switch (target.platform)
			{
			case Platform::GLSL:
				break;
			case Platform::HLSL:
				break;
			case Platform::MSL:
				break;
			default:
				break;
			}
			if (platforms == Platform::GLSL)
			{
				spirv_cross::CompilerGLSL glsl(std::move(binary));
				spirv_cross::CompilerGLSL::Options options;
				// set options
				options.version = 450;
				glsl.set_common_options(options);
				std::string source = glsl.compile();

				std::cout << source << std::endl;
			}

			if (platforms & Platform::MSL)
			{
				compiler.reset(new spirv_cross::CompilerMSL(std::move(parser.get_parsed_ir())));
				auto* msl_compiler = static_cast<spirv_cross::CompilerMSL*>(compiler.get());
				spirv_cross::CompilerMSL::Options options = msl_compiler->get_msl_options();
				// set options
				msl_compiler->set_msl_options(options);
				std::string source = msl_compiler->compile();

				std::cout << source << std::endl;
			}

			if (platforms & Platform::HLSL)
			{
				spirv_cross::CompilerHLSL hlsl(std::move(binary));
				spirv_cross::CompilerHLSL::Options options;
				// set options
				hlsl.set_hlsl_options(options);
				std::string source = hlsl.compile();

				std::cout << source << std::endl;
			}
		}

		return true;
	}
}
