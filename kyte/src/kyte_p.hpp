#pragma once

#include "kyte/kyte.hpp"

#include <spirv/unified1/spirv.hpp>

#include <variant>

namespace kyte
{
	class Binary
	{
	public:
		void writeWord(uint32_t word);
		void writeLiteralString(const std::string& literalString);
		void writeOpcode(uint16_t wordCount, spv::Op opCode);
		void writeInstruction(spv::Op opCode);
		void writeInstruction(spv::Op opCode, std::vector<std::variant<uint32_t, std::string>> operands);

		const std::vector<uint32_t>& get();
	private:
		std::vector<uint32_t> binary;
	};
}
