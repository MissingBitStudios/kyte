#include "kyte_p.hpp"

namespace kyte
{
	void Binary::writeWord(uint32_t word)
	{
		binary.push_back(word);
	}

	void Binary::writeLiteralString(const std::string& literalString)
	{
		uint32_t word = 0;
		uint8_t size = 0;
		for (uint8_t c : literalString)
		{
			word |= c << sizeof(c) * size;
			size++;
			if (size >= 4)
			{
				binary.push_back(word);
				word = 0;
				size = 0;
			}
		}
	}

	void Binary::writeOpcode(uint16_t wordCount, spv::Op opCode)
	{
		uint32_t word = wordCount << spv::WordCountShift;
		word |= opCode;
		binary.push_back(word);
	}

	void Binary::writeInstruction(spv::Op opCode)
	{
		writeOpcode(1, opCode);
	}

	void Binary::writeInstruction(spv::Op opCode, std::vector<std::variant<uint32_t, std::string>> operands)
	{
		writeOpcode(0, opCode);

		auto m = binary.size() - 1;

		uint16_t wordCount = 1;
		for (auto operand : operands)
		{
			if (std::holds_alternative<uint32_t>(operand))
			{
				wordCount++;
				writeWord(std::get<uint32_t>(operand));
			}
			else
			{
				std::string s = std::get<std::string>(operand);
				uint16_t size = s.size();
				wordCount += size / 4 + (size % 4 != 0);
				writeLiteralString(s);
			}
		}

		binary[m] |= wordCount << spv::WordCountShift;
	}

	const std::vector<uint32_t>& Binary::get()
	{
		return binary;
	}
}
