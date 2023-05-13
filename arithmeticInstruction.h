#include "dataComparision.h"
#include "registersFlags.h"
#ifndef arithmeticInstruction
#define arithmericInstruction

void ADD_ADC(string&, registers&);
void ADI_ACI(string&, registers&);
void SUB_SBB(string&, registers&);
void SUI_SBI(string&, registers&);
void INR    (string&, registers&);
void DCR    (string&, registers&);
void INX_DCX(string&, registers&);
void DAA    (string&, registers&);
void DAD    (string&, registers&);
#endif