#ifndef LITERAL_POOL_H
#define LITERAL_POOL_H

#include "tools.h"

class literalPool{


	public:
	
		void insert(std::string literal, std::string locator);
		
		void insert(std::string literal);
		
		std::string getLocator(std::string literal);
		
		bool hasLiteral(std::string literal);
	
		vector<std::string> getUnassLiterals(){
		
			return unassLiteral;
		
		}
		
		void clear(){
		
			unassLiteral.clear();
		
		}
	
	private:
		
		unordered_map<string, string> literalPool;
		
		vector<std::string> unassLiteral;


};

#endif 
