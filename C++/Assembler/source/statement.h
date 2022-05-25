#ifndef STATEMENT_H
#define STATEMENT_H
#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include "operationTable.h"

namespace sic
{
	class Statement 
	{
		public:
			bool extended = false;
			bool indexed = false;
			bool indirect = false;
			bool immediate = false;
			std::string label = "";
			std::string operation = "";
			std::vector<std::string> operands = {};
			std::string comment = "";
			std::vector<std::string> errors = {};
			uint32_t location = 0;



			bool commentLine() const
			{
				return label.empty() && operation.empty() && operands.empty() && !comment.empty();
			}

			//probably want to change errors to an enum or bitfield
			void addError(std::string error)
			{
				errors.push_back(error);
			}

			//write statement (intermediate form) to stream
			friend std::ostream& operator << (std::ostream& os, const Statement& statement);
	};


	//StatementParser
	//reads statements from a file
	class StatementParser
	{
		protected:
			OperationTable* optab;
		public:
			StatementParser(OperationTable*);
			Statement readStatement(std::istream& is, bool intermediate=false) const;

	};
}
#endif
