#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <unordered_map>
#include <string>
#include <cstdint>

class SymbolTable
{
	private:
		std::unordered_map<std::string, uint32_t> table;

	public:

		void insert(std::string, uint32_t location);

		bool contains(std::string) const;
		
		uint32_t at(std::string) const;

};

#endif
