#ifndef branch_memory
#define branch_memory
#include <string>
#include <iostream>
#include <map>
using namespace std;

class mappingLabel{
	map<string, int> label;
	public:
	void putLabel(string, int);
	int getLabel(string);
};

void labelPush(string, int, mappingLabel&);

#endif
