#include "binary.h"
#include "tools.h"
#include "statement.h"
#include <iostream>
#include <fstream>

#ifndef MAX_LOCATION_COUNT
#define MAX_LOCATION_COUNT 2000000
#endif

namespace sic
{
	void Binary::pass1()
	{

		//open file containing sic source code
		std::ifstream source;
		source.open(sourcePath);

		//open file that will store results of pass1
		std::ofstream intermediate;
		intermediate.open(intermediatePath);

		uint32_t locationCounter = 0;
		uint32_t start = 0;

		//loop until there is an error with one of the streams or max locctr reached
		StatementParser parser(optab);
		Statement current;

		//used to get first executalbe instruction
		bool flag = false;

		while(source.good() && intermediate.good() && (locationCounter < MAX_LOCATION_COUNT))
		{

			current = parser.readStatement(source, false);
			current.location = locationCounter;

			std::cout << current;

			//ignore comment lines
			if(current.commentLine())
			{
				continue;
			}

			if(!current.label.empty())
			{

				bool contains = symtab.contains(current.label);
				if(contains)
				{
					current.addError("duplicate symbol");
				}
				else
				{
					symtab.insert(current.label, locationCounter);
				}
			}

			if(!current.operation.empty())
			{

				if(optab->contains(current.operation))
				{
					InstructionType type = optab->type(current.operation);
					switch(type.instructionFormat())
					{
						case InstructionFormat::Format1:
							locationCounter += 1;
							break;

						case InstructionFormat::Format2:
							locationCounter += 2;
							break;

						default:
							locationCounter += 3;
							if(current.extended)
								locationCounter += 1;
							break;

					}
					if(!flag)
					{
						endRecord.setStartingAddress(locationCounter);
						flag = true;
					}

				}
				else if(current.operation == "WORD")
				{
					locationCounter += 3;

				}
				else if((current.operation == "RESW") && 
					!current.operands.empty())
				{
					locationCounter += 3 * aTools::strToInt(current.operands.front());

				} 
				else if((current.operation == "RESB") && 
					!current.operands.empty())
				{
					locationCounter += aTools::strToInt(current.operands.front());

				} 
				else if((current.operation == "BYTE") && 
					!current.operands.empty())
				{

					std::string operand = current.operands.front();
					if ((operand.size() > 3) && (operand.front() == 'C'))
					{
						if((operand.back() == '\'') && operand.at(1) == '\'')
						{
							//TODO handle escaped single quotes
							locationCounter += operand.size() - 3;

						}

					}
					else if (operand.front() == 'X')
						locationCounter += 1;

				}
				else if((current.operation == "START") &&
					!current.operands.empty())
				{
					//offset start by address in operands
					auto num = aTools::strToInt(current.operands.front());
					headerRecord.setStartingAddress(num);
				}
				else if(current.operation == "END")
				{
					intermediate << current;

					break;
				}
				else
				{
					current.addError("invalid operation");
				}

			}
			intermediate << current;
		}

		//close streams
		intermediate.close();
		source.close();

		headerRecord.setProgramSize(locationCounter - start);
	}

}
