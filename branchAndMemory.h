#ifndef branch_memory
#define branch_memory
#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "dataComparision.h"
using namespace std;

//for mremory
void openMemory();
string readMemory(int);
void writeMemory();
//for branching instruction
class mappingLabel{
	map<string, int> label;
	public:
	void putLabel(string, int);
	int getLabel(string);
};

void labelPush(string, int, mappingLabel&);

#endif
