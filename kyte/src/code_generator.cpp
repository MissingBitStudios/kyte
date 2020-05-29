#include "kyte_p.hpp"

namespace kyte
{
	uint32_t CodeGenerator::getTypeID()
	{
		return getNextId();
	}

	uint32_t CodeGenerator::getExtInstID(const std::string& extInstName)
	{
		if (extInsts.count(extInstName))
		{
			return extInsts[extInstName];
		}
		return extInsts[extInstName] = getNextId();
	}

	uint32_t CodeGenerator::registerFunction()
	{
		return getNextId();
	}

	uint32_t CodeGenerator::getConstantID()
	{
		return getNextId();
	}

	void CodeGenerator::registerDebugName(uint32_t resultId, const std::string& debugName)
	{
		debugNames[resultId] = debugName;
	}

	void CodeGenerator::registerDecoration(uint32_t targetId, uint32_t decoration, const std::vector<std::variant<uint32_t, const char*>>& operands = std::vector<std::variant<uint32_t, const char*>>())
	{
		decorations[targetId] = { decoration, operands };
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
		for (auto it = extInsts.begin(); it != extInsts.end(); it++)
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
			for (auto it = debugNames.begin(); it != debugNames.end(); it++)
			{
				binary.writeInstruction(spv::OpName, it->first, it->second.c_str());
			}
			// OpModuleProcessed Instructions
		}

		// Annotation
		// OpDecorate/OpMemberDecorate/OpGroupDecorate/OpGroupMemberDecorate/OpDecorationGroup Instructions
		for (auto it = decorations.begin(); it != decorations.end(); it++)
		{
			binary.writeInstruction(spv::OpDecorate, it->first, it->second.first, it->second.second);
		}

		// OpTypeXXX/OpConstantXXX/OpSpecXXX/OpVariable(Storage Class != Function) Instructions
		// Preffered location of OpUndef Instructions
		// This section is the first section to allow use of OpLine/OpNoLine Instructions

		// Function Declarations
		// OpFunction
			// OpFunctionParameter...
		// OpFunctionEnd

		// Function Definitions
		// OpFunction
			// OpFunctionParameter...
			// Block...
		// OpFunctionEnd

		return binary.get();
	}
} // namespace kyte
