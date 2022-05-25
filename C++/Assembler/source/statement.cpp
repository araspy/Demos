#include <sstream>
#include <cstdio>


#include "statement.h"
#include "tools.h"


namespace sic
{
	std::ostream& operator<<(std::ostream& os, const Statement& statement)
	{
		if(statement.commentLine())
		{
			os << '.' << statement.comment << std::endl;
		} 
		else
		{
			os << std::hex << statement.location << '\t';
			os << statement.label << '\t';

			if(statement.extended)
			{
				os << '+';
			}
			os << statement.operation << '\t';


			if(statement.operands.size() > 0)
			{
				if(statement.indirect)
				{
					os << '@';
				}
				else if(statement.immediate)
				{
					os << '#';
				}

				for(int i = 0; i < statement.operands.size() - 1; ++i)
				{
					os << statement.operands[i] << ',';
				}
				os << statement.operands.back();
				if(statement.indexed)
				{
					os << ",X";
				}
				os << '\t';
			}
			os << statement.comment << std::endl;
		}
		return os;
	}


	StatementParser::StatementParser(OperationTable* optab) : 
		optab{optab}
	{
	
	}


	//constructs a statement object with the text on the current line 
	//if intermediate is true assume we are reading statement from
	//an intermediate file
	// the only difference is that intermediate files have a number in
	// front that represents the location counter at that point.
	//
	//
	//if intermediate:
	//
	//?:q
	//
	//else:
	//
	//
	Statement StatementParser::readStatement(std::istream &is, bool intermediate) const
	{
		Statement statement;

		std::stringstream sstream;
		

		if(is.good() && is.peek() == '.')
		{
			is.ignore();
			while(is.good() && !aTools::tryConsumeNL(is))
			{
				sstream << is.get();
			}
			statement.comment = sstream.str();
			return statement;
		}

		if(intermediate)
		{
			is >> std::hex >> statement.location;
		}

		//which column is currently being parsed (label, operation, operands, comment)
		char column = 0;

		//whether or not characters read should be treated as if they are in a literal
		bool inLiteral = false;
		bool locationParsed = false;


		while(is.good() && !aTools::isCharNL(is.peek()))
		{

			switch(column)
			{
				case 0:
					//end of column
					if(std::isspace(is.peek()))
					{
						is >> std::ws;
						statement.label = sstream.str();
						sstream.str("");
						//little check so whitespace can be in front of period and still be a comment line
						if(is.peek() == '.')
						{
							column = 3;
						}
						else
						{
							column = 1;
						}
					} 
					//comment line
					else if(is.peek() == '.')
					{
						sstream.str("");
						is.ignore();
						column = 3;
					} 
					//still reading label
					else 
					{
						sstream << (char) is.get();
					}

					break;
				case 1:
					//end of column
					if(std::isspace(is.peek()))
					{
						is >> std::ws;
						statement.operation = sstream.str();
						sstream.str("");
						if(optab->operandCount(statement.operation) > 0)
						{
							column = 2;
							inLiteral = false; // this is here in the case of a misformed literal 
						}
						else
						{
							column = 3;
						}
					}
					//still reading operation/directive mnemonic
					else
					{
						sstream << (char) is.get();
					}
					break;

				case 2:
					//single quote starts/ends literal
					if(is.peek() == '\'')
					{
						inLiteral = !inLiteral;
						sstream << is.get();
					}
					//can escape a single character
					//this check is needed since the single quote can be escaped
					else if(inLiteral && (is.peek() == '\\'))
					{

						sstream << is.get() << is.get();
					} 
					//end of operands column
					else if(!inLiteral && (aTools::tryConsumeNL(is) || std::isspace(is.peek())))
					{
						is >> std::ws;

						statement.operands.push_back(sstream.str());
						
						sstream.str("");
						column = 3;
					} 
					//next operand
					else if(!inLiteral && (((char) is.peek()) == ','))
					{

						is.ignore();
						statement.operands.push_back(sstream.str());
						
						sstream.str("");
						//still reading operand
					} 
					else
					{

						sstream << (char) is.get();
					}
					break;

				case 3:
					sstream << (char) is.get();
					//save comment data if next time we don't loop
					if(aTools::isCharNL(is.peek()))
					{
						statement.comment = sstream.str();
						std::cout << sstream.str() << std::endl;
						sstream.str("");
					}
					
					break;
			}


		}
		aTools::tryConsumeNL(is);

		//
		// post read cleanup
		//

		if((statement.operation.size() > 1) && (statement.operation[0] == '+'))
		{
			statement.operation = statement.operation.substr(1);
			statement.extended = true;
		}

		if(!statement.operands.empty())
		{
			if(statement.operands.back() == "X")
			{
				statement.operands.pop_back();
				statement.indexed = true;
			}

			if(statement.operands[0].size() > 1)
			{
				switch(statement.operands.front()[0])
				{

					case '@':
						{
							statement.indirect = true;
							statement.immediate = false;
							break;
						}
					case '#':
						{
							statement.immediate = true;
							statement.indirect = false;
							break;
						}

				}
				if(statement.indirect ^ statement.immediate)
				{
					statement.operands[0] = statement.operands[0].substr(1);
				}
			}


		}
		return statement;
	}
}
