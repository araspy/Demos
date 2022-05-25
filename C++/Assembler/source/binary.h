#ifndef BINARY_H
#define BINARY_H
#include <string>
#include <memory>

#include "operationTable.h"
#include "symbolTable.h"
#include "record.h"

namespace sic
{
	class Binary 
	{
	    //fields
	    private:
	        std::string binaryPath;
	        std::string intermediatePath;
	        std::string sourcePath;
	
	        bool pass1Ran = false;
	        bool pass2Ran = false;
	
		//initialized after pass 1
		HeaderRecord headerRecord;

		//initialized after pass 1
		EndRecord endRecord;
	
	    //methods
	    private:
	        void init();
	
	        void pass1();
		void pass2();
	
	    public:
	
		OperationTable* optab;
		SymbolTable symtab;
	
		void assemble(std::string binaryPath);
		void assemble();
	
	        Binary(std::string sourcePath) : sourcePath{sourcePath}
	        {
			std::string instructionSetCSV = "instruction_set.csv";
			optab = new OperationTable(instructionSetCSV);
	            	init();
	        }

		~Binary()
		{
			delete optab;
		}
	
	
	
	};
}
#endif
