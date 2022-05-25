#include <fstream>
#include <sstream>
#include <utility>

#include "operationTable.h"
#include "tools.h"
namespace sic
{

	OperationTable::OperationTable(const std::string fileName)
	{
		std::cout << "operation table reading instructions from: " << fileName << std::endl;
		std::ifstream ifstream;
		ifstream.open(fileName);

		int currentLine = 0;
		InstructionType type;

		while(ifstream.good())
		{
			ifstream >> type;
			currentLine++;
			insert(type.mnemonic, type);

		}
		ifstream.close();
	}

	OperationTable::~OperationTable()
	{
	}

	OperationTable::OperationTable(const OperationTable& other) :
		m_table{other.m_table}
	{
	}

	OperationTable::OperationTable(OperationTable&& other) :
		m_table{std::move(other.m_table)}
	{
	}

	OperationTable& OperationTable::operator=(const OperationTable& other)
	{
		m_table = other.m_table;
		return *this;
	}

	OperationTable& OperationTable::operator=(OperationTable&& other)
	{
		m_table = std::move(other.m_table);
		return *this;
	}

	std::string OperationTable::format(const std::string& mnemonic) const
	{
		return type(mnemonic).format;
	}

	uint16_t OperationTable::opcode(const std::string& mnemonic) const
	{
		return type(mnemonic).opcode;
	}

	bool OperationTable::privileged(const std::string& mnemonic) const
	{
		return type(mnemonic).privileged;
	}

	bool OperationTable::extendedOnly(const std::string& mnemonic) const
	{

		return type(mnemonic).extendedOnly;
	}

	bool OperationTable::floatingPoint(const std::string& mnemonic) const
	{
		return type(mnemonic).floatingPoint;
	}

	bool OperationTable::setsConditionCode(const std::string& mnemonic) const
	{
		return type(mnemonic).setsConditionCode;
	}

	InstructionType OperationTable::type(const std::string& mnemonic) const
	{
		if(contains(mnemonic))
		{
			return m_table.at(mnemonic);
		}
		return {};
	}

	size_t OperationTable::operandCount(const std::string& mnemonic) const
	{
		return type(mnemonic).operandCount();
	}

	bool OperationTable::contains(const std::string& mnemonic) const
	{
		return m_table.count(mnemonic) > 0;
	}

	bool OperationTable::contains(const InstructionType& type) const
	{
		return contains(type.mnemonic);
	}


	void OperationTable::insert(std::string& mnemonic, InstructionType& type)
	{
		m_table[mnemonic] = type;
	}

}
