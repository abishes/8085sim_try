#include "registersFlags.h"
#include "dataComparision.h"
#include "branchAndMemory.h"
#ifndef dataTransfer
#define dataTransfer

void MVI(string&, registers&, int);
void MOV(string&, registers&, int);
void LDA_STA(string&, registers&, int);
void LXI(string&, registers&, int);
void LDAX_STAX(string&, registers&, int);
void LHLD(string&, registers&, int);
void SHLD(string&, registers&, int);

#endif