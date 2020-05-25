#include "kyte_p.hpp"

#include <iostream> // std::cout, std::cerr, std::endl

namespace kyte
{
	std::vector<uint32_t> Compiler::compile(const std::string& source) const
	{
		// AST Transform
		// parse(source);

		// Binarification https://www.khronos.org/registry/spir-v/specs/unified1/SPIRV.html
		Binary b;

		// Header
		b.writeWords(
			spv::MagicNumber, // https://www.khronos.org/registry/spir-v/specs/unified1/SPIRV.html#_a_id_magic_a_magic_number
			spv::Version, // SPIR-V Version
			kyte::MagicNumber, // Generatorís magic number
			255, // Bound
			0 // Reserved
		);

		// Begin Instruction Stream
		// OpCapability Instructions
		b.writeInstruction(spv::OpCapability, spv::CapabilityLinkage); // @Temp
		b.writeInstruction(spv::OpCapability, spv::CapabilityShader);
		
		// OpExtension Instructions
		
		// OpExtInstImport Instructions
		
		// OpMemoryModel Instruction
		b.writeInstruction(spv::OpMemoryModel, spv::AddressingModelLogical, spv::MemoryModelGLSL450);
		
		// OpEntryPoint Instructions
		
		// OpExecutionMode/OpExecutionModeId Instructions

		// Debug
		if (options.debugInfo)
		{
			// OpString/OpSourceExtension/OpSource/OpSourceContinued Instructions
			b.writeInstruction(spv::OpSource, kyte::SourceLanguageKyte, kyte::Version);
			// OpName/OpMemberName Instructions
			// OpModuleProcessed Instructions
		}

		// Annotation
		// OpDecorate/OpMemberDecorate/OpGroupDecorate/OpGroupMemberDecorate/OpDecorationGroup Instructions

		// OpTypeXXX/OpConstantXXX/OpSpecXXX/OpVariable(Storage Class != Function) Instructions
		// Preffered location of OpUndef Instructions
		// This section is the first section to allow use of OpLine/OpNoLine Instructions

		// Function Declarations
		// Per function
		// OpFunction
			// OpFunctionParameter...
		// opFunctionEnd

		// Function Definitions
		// OpFunction
			// OpFunctionParameter...
			// Block...
		// opFunctionEnd

		std::vector<uint32_t> binary = b.get();

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
