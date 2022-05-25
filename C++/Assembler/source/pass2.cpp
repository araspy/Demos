#include <iostream>
#include <fstream>
#include <sstream>
#include "binary.h"
#include "statement.h"
#include "address.h"
#include "record.h"
#include "instruction.h"
namespace sic
{
	void Binary::pass2()
	{
		std::ifstream intermediate;
		intermediate.open(intermediatePath);

		std::ofstream binary;
		binary.open(binaryPath);
		StatementParser parser(optab);
		Statement current;

		binary << headerRecord;

		TextRecord currentText;
		bool base = false;
		while(intermediate.good() && binary.good())
		{

			current = parser.readStatement(intermediate, true);
			if(currentText.empty())
			{
				currentText.setStart(current.location);
			}

			if(current.commentLine())
			{
				continue;
			}

			if(optab->contains(current.operation))
			{
				bool initialized = false;
				InstructionType type = optab->type(current.operation);
				Instruction* instruction;
				switch(type.instructionFormat())
				{
					case InstructionFormat::Format1:
						instruction = new Format1(type);
						initialized = true;
						break;

					case InstructionFormat::Format2:
						if(current.operands.size() == 2)
						{

							instruction = new Format2(type, current.operands[0], current.operands[1]);
							initialized = true;
						}
						break;

					default:
						if(current.operands.size() == 1)
						{
							std::string operand = current.operands[0];
							if(symtab.contains(operand))
							{
								uint32_t location = symtab.at(operand);
								bool pc = !base && !current.extended;
								Address address(location, current.indirect, current.immediate, current.indexed, base, pc, current.extended);

								instruction = new Format3(type, address);
								initialized = true;

							}
						}
						break;

				}
				if(!initialized)
				{
					continue;
				}

				if(!currentText.hasSpaceForInstruction(instruction))
				{
					binary << currentText;
					currentText.clear();
				}
				if(currentText.empty())
				{
					currentText.setStart(current.location);
				}
				currentText.add(instruction);

			} 
			else if((current.operation == "BYTE") || (current.operation == "WORD"))
			{

				//TODO convert operand to object code
				std::vector<uint8_t> value;
				if(current.operands.size() == 1)
				{
					std::string operand = current.operands.front();
					if((operand.size() > 3) && (operand.at(1) == '\'') && (operand.back() == '\''))
					{

						std::string inner = operand.substr(2, operand.size() - 1);

						switch(operand.front())
						{
							case 'C':
								for(char c : inner)
								{
									value.push_back(c);
								}
								break;
							case 'X':
								uint8_t n;
								std::stringstream sstream;
								sstream << inner;
								sstream >> std::hex >> n;

								value.push_back(n);
								break;
								

						}

					}
				}



			}

		}
		if(!currentText.empty())
		{
			binary << currentText;
		}

		binary << endRecord;
	}
}
