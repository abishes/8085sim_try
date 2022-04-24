#include "registersFlags.h"
#include "dataComparision.h"
#ifndef logicalInstruction
#define logicalInstruction

void CMP(string&, registers&, int);
void CPI(string&, registers&, int);
void ANA_ORA_XRA(string&, registers&, string, int);
void ANI_ORI_XRI(string&, registers&, string, int);
void RLC(registers&);
void RRC(registers&);
void RAL(registers&);
void RAR(registers&);
void CMA(registers&);
void CMC(registers&);
void STC(registers&);

#endif