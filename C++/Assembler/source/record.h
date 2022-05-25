#ifndef RECORD_H
#define RECORD_H
#include <iostream>
#include <vector>
#include <utility>

#include "address.h"
#include "instruction.h"

namespace sic
{

	class Record
	{
		public:
			virtual ~Record();
			virtual void write(std::ostream&) const = 0;

	};

	std::ostream& operator << (std::ostream& os, const Record& record);

	class TextRecord : public Record
	{
		protected:
			std::vector<Instruction*> instructions;
			uint32_t start;
			size_t instructionsSize;

			//methods
		public:
		~TextRecord();
		TextRecord();
		bool hasSpaceForInstruction(Instruction*);
		void add(Instruction*);
		bool empty();
		void setStart(uint32_t);
		void clear();

		virtual void write(std::ostream&) const override;

	};

	class HeaderRecord : public Record
	{
		protected:
			//max 6 chars
			std::string programName = "basic";
			//length of program in bytes
			size_t size;
			uint32_t start = 0;

		public:
		virtual void write(std::ostream&) const override;
		HeaderRecord();
		inline void setProgramName(std::string name)
		{
			programName = name.substr(0, 6);
		}
		inline void setStartingAddress(uint32_t location)
		{
			start = location;
		}
		inline void setProgramSize(size_t newSize)
		{
			size = newSize;
		}
	};


	class EndRecord : public Record
	{
		protected:
			uint32_t end;
		public:
			EndRecord();
			virtual void write(std::ostream&) const override;
			inline void setStartingAddress(uint32_t address)
			{
				end = address;
			}
	};


	class ModificationRecord : public Record
	{
		protected:
			uint32_t locationToModify;
			size_t fieldLength;
			bool modificationFlag;
			std::string symbolName;
		public:
		virtual void write(std::ostream&) const override;
			ModificationRecord();

		inline void setLocationToModify(uint32_t address)
		{
			locationToModify = address;
		}
		inline void setFieldLength(size_t newLength)
		{
			fieldLength = newLength;
		}
		inline void setModificationFlag(bool newFlag)
		{
			modificationFlag = newFlag;
		}
		inline void setSymbolName(std::string newName)
		{
			symbolName = newName.substr(0,6);
		}
	};

	class DefineRecord : public Record
	{
		protected:
			//symbol name, symbol location
			//symbols have a max length of 6 chars
			typedef std::pair<std::string, uint32_t> define;
			std::vector<define> defines;
		public:
		DefineRecord();
		virtual void write(std::ostream&) const override;
	};

	class ReferRecord : public Record
	{
		protected:
			//symbols have a max length of 6 chars
			//max of 12 symbols
			std::vector<std::string> symbols;
		public:
		virtual void write(std::ostream&) const override;
			ReferRecord();

	};

}
#endif
