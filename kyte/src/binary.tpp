#pragma once

namespace kyte
{
	template<typename ...Ts>
	uint16_t Binary::writeInstruction(spv::Op opCode, Ts... operands)
	{
		uint16_t wordCount = writeOpcode(0, opCode);

		auto m = binary.size() - 1;

		wordCount += writeOperands(operands...);

		binary[m] |= wordCount << spv::WordCountShift;

		return wordCount;
	}

	template<typename ...Ts>
	uint16_t Binary::writeOperands(std::variant<uint32_t, const char*> operand, Ts... operands)
	{
		uint16_t wordCount = writeOperands(operand);
		return wordCount + writeOperands(operands...);
	}
} // namespace kyte
