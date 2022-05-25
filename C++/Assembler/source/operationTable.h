#ifndef OPTABLE_H
#define OPTABLE_H

#include <unordered_map>
#include <string>
#include <cstdint>

#include "instruction.h"

namespace sic
{

	class OperationTable 
	{
	
		public:
			OperationTable(const std::string fileName);
			~OperationTable();
			OperationTable(const OperationTable&);
			OperationTable(OperationTable&&);

			OperationTable& operator=(const OperationTable&);
			OperationTable& operator=(OperationTable&&);

	
			std::string format(const std::string& mnemonic) const;
			uint16_t opcode(const std::string& mnemonic) const;
			bool privileged(const std::string& mnemonic) const;
			bool extendedOnly(const std::string& mnemonic) const;
			bool floatingPoint(const std::string& mnemonic) const;
			bool setsConditionCode(const std::string& mnemonic) const;
	
			size_t operandCount(const std::string& mnemonic) const;
	
			InstructionType type(const std::string& mnemonic) const;
	
			bool contains(const std::string& mnemonic) const;
			bool contains(const InstructionType&) const;
		
		private:
			std::unordered_map<std::string, InstructionType> m_table;
	
		protected:
			void insert(std::string& mnemonic, InstructionType&);
	
	};
}
#endif
