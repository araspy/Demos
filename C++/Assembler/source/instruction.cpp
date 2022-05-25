#include <sstream>

#include "instruction.h"
#include "tools.h"

namespace sic
{
	uint8_t registerNumber(std::string mnemonic)
	{
		if(mnemonic == "A")
			return 0;
		if(mnemonic == "X")
			return 1;
		if(mnemonic == "L")
			return 2;
		if(mnemonic == "B")
			return 3;
		if(mnemonic == "B")
			return 4;
		if(mnemonic == "S")
			return 5;
		if(mnemonic == "T")
			return 6;
		if(mnemonic == "F")
			return 7;
		if(mnemonic == "PC")
			return 8;
		if(mnemonic == "SW")
			return 9;

		//invalid register is largest 8 bit int
		return -1;
	}

	std::ostream& operator << (std::ostream& os, const InstructionType& type)
	{
		os << type.mnemonic << "," << type.format << "," << type.opcode << ",";
		if(type.privileged)
		{
			os << "P";
		}
		os << ",";
		if(type.extendedOnly)
		{
			os << "X";
		}
		os << ",";
		if(type.floatingPoint)
		{
			os << "F";
		}
		os << ",";
		if(type.setsConditionCode)
		{
			os << "C";
		}
		os << std::endl;
		return os;
	}

	std::istream& operator >> (std::istream& is,  InstructionType &type)
	{
		char field = 0;
		std::stringstream sstream;
		while((field < 7) && is.good())
		{
			bool endOfField = false;
			if(aTools::tryConsumeNL(is))
			{
				field = 7;
				endOfField = true;
			} 
			else if(is.peek() == ',')
			{
				is.ignore();
				endOfField = true;
			}

			//end of column
			if(endOfField)
			{
				std::string data = sstream.str();
				switch(field)
				{
					case 0:
						type.mnemonic = data;
						break;
					case 1:
						type.format = data;
						break;
					case 2:
						type.opcode = aTools::hexToInt(data);
						break;
					case 3:
						type.privileged = !data.empty();
						break;
					case 4:
						type.extendedOnly = !data.empty();
						break;
					case 5:
						type.floatingPoint = !data.empty();
						break;
					case 6:
						type.setsConditionCode = !data.empty();
						break;
				}
				sstream.str("");
				field++;
			} else {

				if(std::isspace(is.peek()))
				{
					is.ignore();
				}
				else
				{
					sstream << (char) is.get();
				}

			}
		}
		return is;

	}

	size_t InstructionType::operandCount()
	{
		if(format == "1")
		{
			return 0;
		} 

		if (format == "2")
		{
			return 2;
		} 

		return 1;
	}

	InstructionFormat InstructionType::instructionFormat()
	{
		if(format == "1")
		{
			return InstructionFormat::Format1;
		}
		if(format == "2")
		{
			return InstructionFormat::Format2;
		}
		return InstructionFormat::Format3;
	}


	Instruction::~Instruction()
	{
	}
	size_t Instruction::size()
	{
		return 0;
	}

	uint32_t Instruction::objectCode()
	{
		return 0;
	}

	Format1::Format1(InstructionType) 
	{
		Instruction::type = type;
	}

	size_t Format1::size()
	{
		return 1;
	}

	uint32_t Format1::objectCode()
	{
		return type.opcode;
	}

	Format2::Format2(InstructionType type, std::string r1, std::string r2)
	{
		Instruction::type = type;
		registers = (registerNumber(r1) << 4) + registerNumber(r2);
	}

	size_t Format2::size()
	{
		return 2;
	}

	uint32_t Format2::objectCode()
	{
		return (type.opcode << 8) + registers;
	}

	Format3::Format3(InstructionType type, Address address) : address{address}
	{
		Instruction::type = type;
	}

	size_t Format3::size()
	{
		if(!address.indirect() && !address.immediate())
		{
			return 3;
		}
		if(address.extended())
		{
			return 4;
		}
		return 3;
	}

	uint32_t Format3::objectCode()
	{
		if(!address.indirect() && !address.immediate())
		{
			char x = address.indexed();
			return (type.opcode << 16) + (x << 15) + address.display();
		}
		if(address.extended())
		{
			return (type.opcode << 26) + (address.nixbpe() << 20) + address.display();
		}
		return (type.opcode << 18) + (address.nixbpe() << 12) + address.display();
	}
}
