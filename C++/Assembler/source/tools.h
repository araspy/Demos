#ifndef TOOLS_H
#define TOOLS_H
#include <string>
#include <iostream>


namespace aTools {

	bool tryConsumeSpace(std::istream& istream);

	bool tryConsumeNL(std::istream& istream);

	bool isCharNL(char c);

	std::string toLower(std::string str);

	std::string toUpper(std::string str);

	std::string checkLeadSpace(std::string& str);

	void checkTrailSpace(std::string& str);

	std::string repeat(const std::string& str, int times);

	std::string normalize(std::string str, int len);

	std::string normalize(std::string str, int len, std::string c);

	int strToInt(std::string& str);

	int hexToInt(char c);

	int hexToInt(std::string& str);

	char intToHexChar(int digit);

	std::string intToHex(int num);

	std::string intToHex(int num, int len);

	std::string intToBin(int num);

	std::string intToBin(int num, int len);

	int binToInt(std::string binStr);

	int subtractHex(std::string a, std::string b);

	std::string addHex(std::string a, std::string b);

	std::string intToByte(int num);

	std::string stringToHex(std::string numStr);

	std::string intToWord(int num);

	std::string intToWord(std::string numStr);

}
#endif // TOOLS_H
