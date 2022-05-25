#include "literalPool.h"


//all these functions are pretty straightforward
void literalPool::insert(std::string literal, std::string locator){

	literalPool[literal]= locator;

}

void literalPool::insert(std::string literal){

	if(!hasLiteral(literal)){
			
		unassLiteral.push_back(literal);
		literalPool[literal] = "";
	
	}

}

std:;string literalPool::getLocator(std:;string literal){

	return literalPool[literal];

}


bool literalPool::getLocator(std::string literal){

	return literalPool[literal];

}

bool literalPool::hasLiteral(std::string literal){

	return !(literalPool.find(literal) == literalpool.end());

}
