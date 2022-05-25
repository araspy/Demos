#include <string>

#include "binary.h"

// all the programs to test the assembler on
std::string programs[] = {
	"basic.txt",
	"control_section.txt",
	"functions.txt",
	"literals.txt",
	"macros.txt",
	"prog_blocks.txt"
};

int main(int argc, char** argv)
{


	// driver code to see if parsing is working
	// pass in a file with sic/xe source code
	if(argc == 2)
	{
		sic::Binary b(argv[1]);
		b.assemble();
	}

	return 0;
}
