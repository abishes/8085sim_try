#include "branchAndMemory.h"
#include "dataComparision.h"
#include "registersFlags.h"
#ifndef branching
#define branching

int JC_JP_JM_JZ(string&, registers&, mappingLabel&, string, int);
int JMP_JNC_JNZ_JPE_JPO(string&, registers&, mappingLabel&, string, int);
#endif