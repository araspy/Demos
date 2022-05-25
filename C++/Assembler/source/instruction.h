#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <iostream>

#include "address.h"

namespace sic
{
	enum class InstructionFormat
	{
		Format1,
		Format2,
		Format3,
		Format4
	};


	struct InstructionType
	{
		std::string mnemonic = "";
		std::string format = "";
		uint16_t opcode = -1;


 		bool privileged = false;
		bool extendedOnly = false;
		bool floatingPoint = false;
		bool setsConditionCode = false;

		friend std::ostream& operator << (std::ostream &out, const InstructionType& type);
		friend std::istream& operator >> (std::istream& in,  InstructionType& type);
		size_t operandCount();

		InstructionFormat instructionFormat();
	};
	
	class Instruction 
	{
	
		protected:
			InstructionType type;
		public:
			virtual ~Instruction();
			virtual size_t size();
			virtual uint32_t objectCode();
	};
	
	class Format1 : public Instruction
	{
		public:
			Format1(InstructionType);
			virtual size_t size() override;
			virtual uint32_t objectCode() override;
	};
	
	class Format2 : public Instruction
	{
		protected:
			uint8_t registers;
	
		public:
			Format2(InstructionType type, std::string r1, std::string r2);
			virtual size_t size() override;
			virtual uint32_t objectCode() override;
	};
	
	class Format3 : public Instruction
	{
		protected:
			Address address;
	
		public:
			Format3(InstructionType type, Address address);
			virtual size_t size() override;
			virtual uint32_t objectCode() override;
	};
	
}
#endif
