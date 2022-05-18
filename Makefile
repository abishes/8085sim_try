CCC = g++ -Wall -Wextra -Wpedantic 
OBJ = main.o dataComparision.o registersFlags.o dataTransfer.o logicalInstruction.o \
arithmeticInstruction.o branchAndMemory.o branchingInstruction.o
8085sim: $(OBJ)
	$(CCC) $(OBJ) -o $@
main.o: main.cpp
	$(CCC) -c $^
%.o: %.cpp %.h
	$(CCC) -c $<

.PHONY: test
test:
	sh -c './8085sim < test'
