#pragma once

#include "kyte/kyte.hpp"

#include <spirv/unified1/spirv.hpp>
#include <spirv-tools/libspirv.hpp>

#include <variant>

namespace kyte
{
	const uint32_t MagicNumber = 23;
	const uint32_t Version = 1;
	const uint32_t SourceLanguageKyte = spv::SourceLanguageUnknown;
	const uint32_t GLSL_STD_450_EXT_INST_ID = 1;

	const spv_target_env SpvTargetEnv = SPV_ENV_UNIVERSAL_1_5;

	class Binary
	{
	public:
		uint16_t writeWord(uint32_t word);
		uint16_t writeLiteralString(const char* literalString);
		uint16_t writeOpcode(uint16_t wordCount, spv::Op opCode);
		uint16_t writeInstruction(spv::Op opCode);
		uint16_t writeInstruction(spv::Op opCode, std::vector<std::variant<uint32_t, const char*>> operands);
		template<typename ...Ts>
		uint16_t writeInstruction(spv::Op opCode, Ts... operands);

		const std::vector<uint32_t>& get();
	private:
		uint16_t writeOperands(std::variant<uint32_t, const char*> operand);
		template<typename ...Ts>
		uint16_t writeOperands(std::variant<uint32_t, const char*> operand, Ts... operands);
		std::vector<uint32_t> binary;
	};
} // namespace kyte

#include "binary.tpp"
