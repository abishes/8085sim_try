#include <string>
#ifndef dataComparision
#define dataComparision
#define SPACE 32
using namespace std;

const int error_data =  0;
const int error_register= 1;
const int error_H= 2;
const int error_instructionSize= 3;
const int error_flag= 4;
const int error_registerPair=5;
const int error_memoryExceed= 6;
const int error_label=7;

int charToInt(char);
char intToChar(int);
int dataStringToInt(string);
string dataIntToString(int);
int addressStringToInt(string);
string addressIntToString(int);
bool checkRegister(char);
bool checkData(char);
bool checkAddress(const string&);
bool check2BitData(const string&);
bool parityChecker(int);

bool signChecker(int);
bool auxiliaryCarryChecker(string, string, string);
void codeTransfer(string& line);


#endif