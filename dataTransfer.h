#include "registersFlags.h"
#include "dataComparision.h"
#include "branchAndMemory.h"
#ifndef dataTransfer
#define dataTransfer

void MVI(string&, registers&);
void MOV(string&, registers&);
void LDA_STA(string&, registers&);
void LXI(string&, registers&);
void LDAX_STAX(string&, registers&);
void LHLD(string&, registers&);
void SHLD(string&, registers&);
void XCHG(string&, registers&);

#endif