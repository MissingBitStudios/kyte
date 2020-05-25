#include "kyte_p.hpp"

namespace kyte
{
	uint32_t CodeGenerator::registerType()
	{
		return getNextId();
	}

	uint32_t CodeGenerator::registerExtInst(const std::string& extInstName)
	{
		if (extInst.count(extInstName))
		{
			return extInst[extInstName];
		}
		return extInst[extInstName] = getNextId();
	}

	uint32_t CodeGenerator::registerFunction()
	{
		return getNextId();
	}

	uint32_t CodeGenerator::registerConstant()
	{
		return getNextId();
	}

	void CodeGenerator::registerEntryPoint(spv::ExecutionModel executionModel, uint32_t function)
	{

	}

	uint32_t CodeGenerator::getNextId()
	{
		return nextId++;
	}

	// https://www.khronos.org/registry/spir-v/specs/unified1/SPIRV.html
	std::vector<uint32_t> CodeGenerator::generate(Options options)
	{
		Binary binary;

		// Header
		binary.writeWords(
			spv::MagicNumber, // https://www.khronos.org/registry/spir-v/specs/unified1/SPIRV.html#_a_id_magic_a_magic_number
			spv::Version, // SPIR-V Version
			kyte::MagicNumber, // Generator’s magic number
			getNextId(), // Bound
			0 // Reserved
		);

		// Begin Instruction Stream
		// OpCapability Instructions
		binary.writeInstruction(spv::OpCapability, spv::CapabilityLinkage); // @Temp
		binary.writeInstruction(spv::OpCapability, spv::CapabilityShader);

		// OpExtension Instructions

		// OpExtInstImport Instructions
		for (auto it = extInst.begin(); it != extInst.end(); it++)
		{
			binary.writeInstruction(spv::OpExtInstImport, it->second, it->first.c_str());
		}

		// OpMemoryModel Instruction
		binary.writeInstruction(spv::OpMemoryModel, spv::AddressingModelLogical, spv::MemoryModelGLSL450);

		// OpEntryPoint Instructions

		// OpExecutionMode/OpExecutionModeId Instructions

		// Debug
		if (options.debugInfo)
		{
			// OpString/OpSourceExtension/OpSource/OpSourceContinued Instructions
			binary.writeInstruction(spv::OpSource, kyte::SourceLanguageKyte, kyte::Version);
			// OpName/OpMemberName Instructions
			// OpModuleProcessed Instructions
		}

		// Annotation
		// OpDecorate/OpMemberDecorate/OpGroupDecorate/OpGroupMemberDecorate/OpDecorationGroup Instructions

		// OpTypeXXX/OpConstantXXX/OpSpecXXX/OpVariable(Storage Class != Function) Instructions
		// Preffered location of OpUndef Instructions
		// This section is the first section to allow use of OpLine/OpNoLine Instructions

		// Function Declarations
		// OpFunction
			// OpFunctionParameter...
		// opFunctionEnd

		// Function Definitions
		// OpFunction
			// OpFunctionParameter...
			// Block...
		// opFunctionEnd

		return binary.get();
	}
} // namespace kyte
