#include "registersFlags.h"
#include "dataComparision.h"
#ifndef logicalInstruction
#define logicalInstruction

void CMP(string&, registers&);
void CPI(string&, registers&);
void ANA_ORA_XRA(string&, registers&);
void ANI_ORI_XRI(string&, registers&);
void RLC(string&, registers&);
void RRC(string&, registers&);
void RAL(string&, registers&);
void RAR(string&, registers&);
void CMA(string&, registers&);
void CMC(string&, registers&);
void STC(string&, registers&);

#endif