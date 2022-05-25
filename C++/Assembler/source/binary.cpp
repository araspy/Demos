#include <vector>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <iostream>

#include "binary.h"
#include "record.h"
#include "tools.h"
#include "statement.h"
#include "instruction.h"

namespace sic
{
	void Binary::init()
	{
		// create intermediate and binary paths based on path of source
		intermediatePath = sourcePath + ".intermediate";
		binaryPath = sourcePath + ".out";
	}




	void Binary::assemble(std::string binaryPath)
	{
		pass1();
		pass2();
	}

	void Binary::assemble()
	{
		assemble(binaryPath);
	}
}
