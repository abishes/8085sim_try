#include "registersFlags.h"
#include "dataComparision.h"
#include "branchAndMemory.h"
#ifndef dataTransfer
#define dataTransfer

void MVI(string&, registers&, int);
void MOV(string&, registers&, int);
void LDA(string&, registers&, int);
void LXI(string&, registers&, int);

#endif