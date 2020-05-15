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
	std::vector<uint32_t> compile(const std::vector<SourceFile>& sourceFiles)
	{
		Binary b;

		// Header
		b.writeWord(spv::MagicNumber);
		b.writeWord(spv::Version);
		b.writeWord(kyte::MagicNumber); // Generator’s magic number
		b.writeWord(255); // Bound
		b.writeWord(0); // Reserved

		// Begin Instruction Stream
		b.writeInstruction(spv::OpCapability, {spv::CapabilityLinkage});
		b.writeInstruction(spv::OpCapability, {spv::CapabilityShader});
		b.writeInstruction(spv::OpMemoryModel, { spv::AddressingModelLogical, spv::MemoryModelGLSL450 });

		std::vector<uint32_t> binary = b.get();

		spv_target_env env = SPV_ENV_UNIVERSAL_1_5;
		spvtools::SpirvTools core(env);
		spvtools::Optimizer opt(env);

		auto print_msg_to_stderr = [](spv_message_level_t, const char*,
			const spv_position_t&, const char* m) {
				std::cerr << "error: " << m << std::endl;
		};

		core.SetMessageConsumer(print_msg_to_stderr);
		opt.SetMessageConsumer(print_msg_to_stderr);

		if (!core.Validate(binary)) throw std::exception();
		if (!opt.Run(binary.data(), binary.size(), &binary)) throw std::exception();

		std::string disassembly;
		if (!core.Disassemble(binary, &disassembly)) throw std::exception();
		std::cout << disassembly << "\n";

		return std::move(binary);
	}
}
