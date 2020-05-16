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
		uint16_t wordCount = writeOpcode(0, opCode);

		size_t m = binary.size() - 1;

		wordCount += writeOperands(operands...);

		binary[m] |= wordCount << spv::WordCountShift;

		return wordCount;
	}

	template<typename ...Ts>
	uint16_t Binary::writeExtInstruction(uint32_t setId, uint32_t instruction, uint32_t resultTypeId, uint32_t resultId, Ts... operands)
	{
		size_t m = binary.size();

		uint16_t wordCount = writeExtInstruction(setId, instruction, resultTypeId, ResultId);

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
