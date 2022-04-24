#include <iostream>
#ifndef registersFlags
#define registersFlags
using namespace std;
class flags
{
    bool CY, Z, S, AC, P;

public:
    flags();
    bool flagName(char);
    void flagSet(char);
    void flagReset(char);
    void flagDisplay();
};

class registers: public flags
{
    string A, B, C, D, E, H, L;

public:
    registers();
    string registerName(char);
    void registerSet(char, string data);
    void registerSet(char, char);
    void registerDisplay();
};

#endif