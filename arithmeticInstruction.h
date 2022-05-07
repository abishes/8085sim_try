#include "dataComparision.h"
#include "registersFlags.h"
#ifndef arithmeticInstruction
#define arithmericInstruction

void ADD_ADC(string&, registers&, string, int);
void ADI_ACI(string&, registers&, string, int);
void SUB_SBB(string&, registers&, string, int);
void SUI_SBI(string&, registers&, string, int);
void INR(string&, registers&, int);
void DCR(string&, registers&, int);
void INX_DCX(string&, registers&, int);
#endif