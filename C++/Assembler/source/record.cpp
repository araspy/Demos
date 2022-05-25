
#include "record.h"
#include "tools.h"
#include <iomanip>

namespace sic
{
	Record::~Record()
	{
	}

	std::ostream& operator << (std::ostream& os, const Record& record)
	{
		record.write(os);
		return os;
	}

	TextRecord::TextRecord()
	{
	}

	TextRecord::~TextRecord()
	{
		for(Instruction* i : instructions)
		{
			delete i;
		}
		instructions.clear();
	}
	bool TextRecord::hasSpaceForInstruction(Instruction* i)
	{
		//60 characters 2 for 1 byte implies 30 bytes
		return (i->size() + instructionsSize) <= 30;
	}

	void TextRecord::add(Instruction* i)
	{
		instructions.push_back(i);
		instructionsSize += i->size();
	}

	bool TextRecord::empty()
	{
		return instructions.empty();
	}


	void TextRecord::write(std::ostream& os) const
	{
		os << 'T';
		os << std::right << std::setfill('0') << std::hex;
		os << std::setw(6) << start; 
		os << std::setw(2) << instructionsSize;

		for(Instruction* instruction : instructions)
		{
			os << std::setw(instruction->size() * 2) << instruction->objectCode();
		}
		os << std::endl;

	}
	void TextRecord::clear()
	{
		start = 0;
		instructionsSize = 0;
		for(Instruction* instruction : instructions)
		{
			delete instruction;
		}
		
		instructions.clear();
	}

	void TextRecord::setStart(uint32_t address) 
	{
		start = address;
	}

	HeaderRecord::HeaderRecord()
	{
	}


	void HeaderRecord::write(std::ostream& os) const
	{
		os << 'H';
		os << std::left << std::setfill(' ') << std::setw(6) << programName;
		os << std::right << std::setfill('0') << std::hex;
		os << std::setw(6) << start; 
		os << aTools::intToHex(size, 6);
		os << std::endl;
	}

	EndRecord::EndRecord()
	{
	}

	void EndRecord::write(std::ostream& os) const
	{
		os << 'E';
		os << std::right << std::setfill('0') << std::hex;
		os << std::setw(6) << end;
		os << std::endl;
	}

	ModificationRecord::ModificationRecord()
	{
	}
	
	void ModificationRecord::write(std::ostream& os) const
	{
		os << 'M';
		//TODO
	}

	DefineRecord::DefineRecord()
	{
	}



	void DefineRecord::write(std::ostream& os) const
	{
		os << 'D';
		//TODO
	}


	ReferRecord::ReferRecord()
	{
	}

	void ReferRecord::write(std::ostream& os) const
	{
		os << 'R';
		//TODO
	}

}
