CCC = g++ -Wall -Wextra -Wpedantic 
8085sim: main.o dataComparision.o registersFlags.o dataTransfer.o\
logicalInstruction.o arithmeticInstruction.o branchAndMemory.o branchingInstruction.o
	$(CCC) main.o dataComparision.o registersFlags.o dataTransfer.o logicalInstruction.o \
arithmeticInstruction.o branchAndMemory.o branchingInstruction.o -o $@
main.o: main.cpp
	$(CCC) -c main.cpp
dataComparision.o: dataComparision.cpp dataComparision.h
	$(CCC) -c dataComparision.cpp
registersFlags.o: registersFlags.cpp registersFlags.h
	$(CCC) -c registersFlags.cpp
dataTransfer.o: dataTransfer.cpp dataTransfer.h
	$(CCC) -c dataTransfer.cpp
logicalInstruction.o: logicalInstruction.h logicalInstruction.cpp
	$(CCC) -c logicalInstruction.cpp
arithmeticInstruction.o: arithmeticInstruction.h arithmeticInstruction.cpp
	$(CCC) -c arithmeticInstruction.cpp
branchAndMemory.o: branchAndMemory.h branchAndMemory.cpp
	$(CCC) -c branchAndMemory.cpp
branchingInstruction.o: branchingInstruction.h branchingInstruction.cpp
	$(CCC) -c branchingInstruction.cpp
.PHONY: test
test:
	sh -c './8085sim < test'

