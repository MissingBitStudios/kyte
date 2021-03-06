#pragma once

namespace kyte
{

	template<typename ...Ts>
	uint16_t Binary::writeWords(uint32_t word, Ts... words)
	{
		uint16_t wordCount = writeWord(word);
		return wordCount + writeWords(words...);
	}

	template<typename ...Ts>
	uint16_t Binary::writeInstruction(spv::Op opCode, Ts... operands)
	{
		size_t m = binary.size();

		uint16_t wordCount = writeOpcode(0, opCode);

		wordCount += writeOperands(operands...);

		binary[m] |= wordCount << spv::WordCountShift;

		return wordCount;
	}

	template<typename ...Ts>
	uint16_t Binary::writeOperands(std::variant<uint32_t, const char*, std::vector<std::variant<uint32_t, const char*>>> operand, Ts... operands)
	{
		uint16_t wordCount = writeOperands(operand);
		return wordCount + writeOperands(operands...);
	}
} // namespace kyte
