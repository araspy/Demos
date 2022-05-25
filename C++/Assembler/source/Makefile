SHELL = /bin/sh

BIN_NAME = assembler
GCC = g++
FLAGS = -std=c++11 -Wall -Og

OBJECTS = binary.o instruction.o operationTable.o record.o symbolTable.o test.o tools.o statement.o pass1.o pass2.o

TEST_PROGRAMS = basic.txt control_section.txt functions.txt literals.txt macros.txt

$(BIN_NAME): $(OBJECTS)
	$(GCC) $(FLAGS) -o $(BIN_NAME) $^

binary.o: binary.cpp binary.h
	$(GCC) $(FLAGS) -o $@ -c binary.cpp

instruction.o: instruction.cpp instruction.h
	$(GCC) $(FLAGS) -o $@ -c instruction.cpp

operationTable.o: operationTable.cpp operationTable.h
	$(GCC) $(FLAGS) -o $@ -c operationTable.cpp

record.o: record.cpp record.h
	$(GCC) $(FLAGS) -o $@ -c record.cpp

symbolTable.o: symbolTable.cpp symbolTable.h
	$(GCC) $(FLAGS) -o $@ -c symbolTable.cpp

test.o: test.cpp
	$(GCC) $(FLAGS) -o $@ -c test.cpp

tools.o: tools.cpp tools.h
	$(GCC) $(FLAGS) -o $@ -c tools.cpp

statement.o: statement.cpp statement.h
	$(GCC) $(FLAGS) -o $@ -c statement.cpp

pass1.o: pass1.cpp binary.h
	$(GCC) $(FLAGS) -o $@ -c pass1.cpp

pass2.o: pass2.cpp binary.h
	$(GCC) $(FLAGS) -o $@ -c pass2.cpp

.PHONY: clean

clean:
	rm -rvf $(OBJECTS)
	$(foreach TEST_PROGRAM, ${TEST_PROGRAMS},\
		rm -rvf programs/${TEST_PROGRAM}.intermediate;\
		rm -rvf programs/${TEST_PROGRAM}.out;)
