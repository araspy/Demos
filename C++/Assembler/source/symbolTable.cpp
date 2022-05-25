#include "symbolTable.h"

void SymbolTable::insert(std::string label, uint32_t location)
{
	table[label] = location;
}

bool SymbolTable::contains(std::string label) const
{
	return table.count(label) > 0;
}

uint32_t SymbolTable::at(std::string symbol) const
{
	return table.at(symbol);
}
