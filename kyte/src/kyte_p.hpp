#pragma once

#include "kyte/kyte.hpp"

#include <spirv/unified1/spirv.hpp>
#include <spirv/unified1/GLSL.std.450.h>
#include <spirv-tools/libspirv.hpp>

#include <variant>
#include <unordered_map>

namespace kyte
{
	const uint32_t MagicNumber = 23;
	const uint32_t Version = 1;
	const uint32_t SourceLanguageKyte = spv::SourceLanguageUnknown;

	const spv_target_env SpvTargetEnv = SPV_ENV_UNIVERSAL_1_5;

	class Binary
	{
	public:
		uint16_t writeWord(uint32_t word);
		template<typename ...Ts>
		uint16_t writeWords(uint32_t word, Ts... words);
		uint16_t writeWord64(uint64_t word);
		uint16_t writeInt(int32_t value);
		uint16_t writeInt64(int64_t value);
		uint16_t writeFloat(float value);
		uint16_t writeFloat64(double value);
		uint16_t writeLiteralString(const char* literalString);
		uint16_t writeOpcode(uint16_t wordCount, spv::Op opCode);
		uint16_t writeInstruction(spv::Op opCode);
		template<typename ...Ts>
		uint16_t writeInstruction(spv::Op opCode, Ts... operands);

		const std::vector<uint32_t>& get() const;
	private:
		uint16_t writeWords(uint32_t word);
		uint16_t writeOperands(std::variant<uint32_t, const char*, std::vector<std::variant<uint32_t, const char*>>> operand);
		template<typename ...Ts>
		uint16_t writeOperands(std::variant<uint32_t, const char*, std::vector<std::variant<uint32_t, const char*>>> operand, Ts... operands);
		std::vector<uint32_t> binary;
	};

	class CodeGenerator
	{
	public:
		uint32_t registerType();
		uint32_t registerExtInst(const std::string& extInstName);
		uint32_t registerFunction();
		uint32_t registerConstant();
		void registerEntryPoint(spv::ExecutionModel executionModel, uint32_t function);

		std::vector<uint32_t> generate(Options options);
	private:
		uint32_t getNextId();
		uint32_t nextId = 1;

		std::unordered_map<std::string, uint32_t> extInst;
	};

	// void parse(const std::string& sourceCode);
} // namespace kyte

#include "binary.tpp"
#include "code_generator.tpp"
