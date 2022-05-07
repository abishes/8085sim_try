#include <string>
#ifndef dataComparision
#define dataComparision
#define SPACE 32
using namespace std;

int charToInt(char);
char intToChar(int);
int dataStringToInt(string);
string dataIntToString(int);
int addressStringToInt(string);
string addressIntToString(int);
bool checkRegister(char);

bool checkData(char);

bool parityChecker(int);

bool signChecker(int);
bool auxiliaryCarryChecker(string, string, string);


#endif