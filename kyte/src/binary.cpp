#include "kyte_p.hpp"

#include <climits> // CHAR_BIT

namespace kyte
{
	uint16_t Binary::writeWord(uint32_t word)
	{
		binary.push_back(word);
		return 1;
	}

	uint16_t Binary::writeWords(uint32_t word)
	{
		return writeWord(word);
	}

	/*The low-order 32 bits appear in the first operand.*/
	uint16_t Binary::writeWord64(uint64_t word)
	{
		uint32_t high = (uint32_t)(word >> sizeof(uint32_t)* CHAR_BIT);
		uint32_t low = (uint32_t)word;
		return writeWords(low, high);
	}

	uint16_t Binary::writeInt(int32_t value)
	{
		return writeWord(reinterpret_cast<uint32_t&>(value));
	}

	uint16_t Binary::writeInt64(int64_t value)
	{
		return writeWord64(reinterpret_cast<uint64_t&>(value));
	}

	uint16_t Binary::writeFloat(float value)
	{
		return writeWord(reinterpret_cast<uint32_t&>(value));
	}

	uint16_t Binary::writeFloat64(double value)
	{
		return writeWord64(reinterpret_cast<uint64_t&>(value));
	}

	/* A string is interpreted as a nul-terminated stream of characters. The
	character set is Unicode in the UTF-8 encoding scheme. The UTF-8 octets
	(8-bit bytes) are packed four per word, following the little-endian
	convention (i.e., the first octet is in the lowest-order 8 bits of the word).
	The final word contains the string’s nul-termination character (0), and all
	contents past the end of the string in the final word are padded with 0. */
	uint16_t Binary::writeLiteralString(const char* c)
	{
		uint16_t wordCount = 0;
		uint32_t word = 0;
		uint8_t size = 0;

		for (;; c++)
		{
			word |= *c << size * sizeof(char) * CHAR_BIT;
			size++;
			if (size >= 4 || *c == '\0')
			{
				wordCount += writeWord(word);
				if (*c == '\0') return wordCount;
				word = size = 0;
			}
		}
	}

	/*The 16 high-order bits are the WordCount of the instruction.
	The 16 low-order bits are the opcode enumerant. 0xWWWWOOOO*/
	uint16_t Binary::writeOpcode(uint16_t wordCount, spv::Op opCode)
	{
		return writeWord((wordCount << spv::WordCountShift) | opCode);
	}

	uint16_t Binary::writeInstruction(spv::Op opCode)
	{
		return writeOpcode(1, opCode);
	}

	uint16_t Binary::writeOperands(std::variant<uint32_t, const char*> operand)
	{
		if (std::holds_alternative<uint32_t>(operand))
		{
			return writeWord(std::get<uint32_t>(operand));
		}
		else
		{
			return writeLiteralString(std::get<const char*>(operand));
		}
	}

	uint16_t Binary::writeExtInstruction(uint32_t setId, uint32_t instruction, uint32_t resultTypeId, uint32_t resultId)
	{
		writeOpcode(5, spv::OpExtInst);
		writeWords(resultTypeId, resultId, setId, instruction);
		return 5;
	}

	uint32_t Binary::getNextId()
	{
		return nextId++;
	}

	const std::vector<uint32_t>& Binary::get() const
	{
		return binary;
	}
} // namespace kyte
