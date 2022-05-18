#include "registersFlags.h"
#include "dataComparision.h"
#ifndef logicalInstruction
#define logicalInstruction

void CMP(string&, registers&);
void CPI(string&, registers&);
void ANA_ORA_XRA(string&, registers&);
void ANI_ORI_XRI(string&, registers&);
void RLC(registers&);
void RRC(registers&);
void RAL(registers&);
void RAR(registers&);
void CMA(registers&);
void CMC(registers&);
void STC(registers&);

#endif