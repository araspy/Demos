#include "tools.h"

/**
 * contains SIC/XE tools for manipulating strings, integers, etc.
 */

namespace aTools {


	bool tryConsumeSpace(std::istream& istream)
	{
		bool result = false;
		while(std::isspace(istream.peek()))
		{
			result = true;
			istream.ignore();
		}
		return result;

	}

	bool tryConsumeNL(std::istream& istream)
	{
	    bool result = false;
	    //\r
	    if(istream.peek() == '\r')
	    {
	        istream.ignore();
	        result = true;
	    } 
	    else if(istream.peek() == '\036')
	    {
	        istream.ignore();
	        return true;
	    }
	
	
	    //\n \r\n
	    if(istream.peek() == '\n')
	    {
	        istream.ignore();
	        //\n\r
	        if(!result && (istream.peek() == '\r'))
	        {
	            istream.ignore();
	        }
	        result = true;
	    }
	    return result;
	}
	
	bool isCharNL(char c)
	{
	    return (c == '\n') || (c == '\r') || (c == '\036');
	}

//convert string to lower case
	std::string toLower(std::string str) {
		for (int i = 0; i < str.size(); i++) {
			str[i] = tolower(str[i]);
		}
		return str;
	}

//convert string to upper case
	std::string toUpper(std::string str) {
		for (int i = 0; i < str.size(); i++) {
			str[i] = toupper(str[i]);
		}
		return str;
	}

//check for leading spaces, and remove them if present
	std::string checkLeadSpace(std::string& str) {
		int ls = 0;
		for (; ls < str.size(); ++ls) {
			if (str[ls] != ' ' && str[ls] != '\t')
				break;
		}
		return str.substr(ls);
	}

//check for trailing spaces, and remove them if present
	void checkTrailSpace(std::string& str) {
		while (str.back() == ' ' || str.back() == '\t') {
			str.pop_back();
		}
	}


//repeat str parameter specified number of times
	std::string repeat(const std::string& str, int times) {
		std::string result;
		result.reserve(times * str.length()); // avoid repeated reallocation*
		for (int a = 0; a < times; a++)
			result += str;
		return result;
	}


	//normalize numeric string to length len. if length > len, return last len chars. 
	//otherwise add 0 to beginning of string until len is met
	std::string normalize(std::string str, int len) {
		return normalize(str, len, "0");
	}


	// same as above normalize function, adding string c instead of 0 to beginning of str
	std::string normalize(std::string str, int len, std::string c) {
		while (str.size() < len) {
			str = c + str;
		}
		return str.substr(str.size() - len);
	}

//convert string of digits to integer value
	int strToInt(std::string& str) {
		int x = 0;
		int i = str.empty() || (str[0] != '-' && str[0] != '+') ? 0 : 1;
		int posNeg = 1;
		if (!str.empty() && str[0] == '-') {
			posNeg = -1;
		}
		for (; i < str.size(); i++) {
			x = x * 10 + str[i] - '0';
		}
		return x * posNeg;
	}

//convert single hexadecimal character to integer value
	int hexToInt(char c) {
		int digit = tolower(c) - '0';
		return digit + (digit > 9 ? (10 + '0' - 'a') : 0);
	}

//convert string of hex characters to integer value
	int hexToInt(std::string& str) {
		if (str.size() == 6 && tolower(str[0]) == 'f') {
			str = "ff" + str;
		}
		int x = 0;
		for (int i = 0; i < str.size(); i++) {
			x <<= 4;
			x |= hexToInt(str[i]);
		}
		return x;
	}

//convert integer between 0-15 to corresponding hex character
	char intToHexChar(int digit) {
		return (digit > 9 ? ('a' - 10) : '0') + digit;
	}

//convert multiple digit num into a hex string (max length 6 chars, calls intToHexChar)
	std::string intToHex(int num) {
		int msk = 0b1111;
		std::string hex = "";
		for (int i = 0; i < 6; ++i) {
			hex += intToHexChar(num & msk);
			num >>= 4;
		}
		//reverse(hex.begin(), hex.end());
		return hex;
	}

//same as above intToHex, allowing for specification length of hex string
	std::string intToHex(int num, int len) {
		std::string c = num < 0 ? "f" : "0";
		std::string hex = intToHex(num);
		return normalize(hex, len, c);
	}

//convert a positive integer to binary string, with no specification of string length
	std::string intToBin(int num) {
		std::string binary = "";
		while (num > 0) {
			binary += (num % 2) ? "1" : "0";
			num /= 2;
		}
		//reverse(binary.begin(), binary.end());
		return binary;
	}

//convert integer to binary string of specified length len
	std::string intToBin(int num, int len) {
		std::string c = num < 0 ? "1" : "0";
		std::string bin = intToBin(num);
		return normalize(bin, len, c);
	}

//convert binary string to integer value
	int binToInt(std::string binStr) {
		int binInt = 0;
		for (int i = 0; i < binStr.length(); ++i) {
			binInt <<= 1;
			binInt |= (binStr[i] - '0');
		}
		return binInt;
	}

//subtract one hex value from another, returning an integer value
	int subtractHex(std::string a, std::string b) {
		return (hexToInt(a) - hexToInt(b));
	}


//add one hex value to another, returning a new hex string
	std::string addHex(std::string a, std::string b) {
		return intToHex(hexToInt(a) + hexToInt(b));
	}


//convert integer to hex string of length 2 
	std::string intToByte(int num) {
		return intToHex(num, 2);
	}


//convert numeric string to hex string of length 2 
	std::string stringToHex(std::string numStr) {
		return intToByte(strToInt(numStr));
	}

//convert integer to hex string of length 6 
	std::string intToWord(int num) {
		return intToHex(num, 6);
	}


//convert numeric string to hex string
	std::string intToWord(std::string numStr) {
		return intToWord(strToInt(numStr));
	}




}
