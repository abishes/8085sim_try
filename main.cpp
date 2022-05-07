#include <iostream>
#include <vector>
#include <string>
#include "dataComparision.h"
#include "registersFlags.h"
#include "dataTransfer.h"
#include "logicalInstruction.h"
#include "arithmeticInstruction.h"
#include "branchAndMemory.h"
#include "branchingInstruction.h"

int instructionDecode(string &line, registers &R, mappingLabel& M, int lineNumber){
	if(line.find(':') != string::npos){
			string lineTemp;
			int instructionStart=line.find(':')+1;
			if(!isalpha(line[instructionStart])){
				cout<<"Instruction should directly follow ':' in line: "<<lineNumber<<endl;
				return -1;
			}
			for(int i = instructionStart; i < (int)line.length();i++){
				lineTemp.push_back(line[i]);
			}
			line = lineTemp;
		}
	string instruction;
	for (int i = 0; i < 5; i++) /*To identify instruction name*/
	{
		if (line[i] == SPACE || line[i] == '\0'){
			break;
		}
		instruction.push_back(line[i]);
	}
	/*Data transfer instructions*/
	if (instruction == "MVI")
		MVI(line, R, lineNumber);
	else if(instruction == "MOV")
		MOV(line, R, lineNumber);
	else if(instruction == "LDA" || instruction == "STA")
		LDA_STA(line, R, lineNumber);
	else if(instruction == "LXI")
		LXI(line, R, lineNumber);
	else if(instruction == "LDAX" || instruction == "STAX")
		LDAX_STAX(line, R, lineNumber);
	else if(instruction == "LHLD")
		LHLD(line, R, lineNumber);
	else if(instruction == "SHLD")
		SHLD(line, R, lineNumber);
	/*Branching instruction*/
	else if(instruction == "JC" || instruction == "JP" ||  instruction == "JM" || instruction == "JZ")
		return JC_JP_JM_JZ(line, R, M, instruction, lineNumber);	//branching instruction have return because they represents
																	//where to go
	else if(instruction == "JMP" || instruction == "JNC" ||instruction == "JNZ" ||instruction == "JPE" ||instruction == "JPO" )
		return JMP_JNC_JNZ_JPE_JPO(line, R, M, instruction, lineNumber);
	/*Arithmetic Instruction*/
	else if(instruction == "ADD" || instruction == "ADC")
		ADD_ADC(line, R, instruction, lineNumber);
	else if(instruction == "ADI" || instruction == "ACI")
		ADI_ACI(line, R, instruction, lineNumber);
	else if(instruction == "SUB" || instruction == "SBB")
		SUB_SBB(line, R, instruction, lineNumber);
	else if(instruction == "SUI" || instruction == "SBI")
		SUI_SBI(line, R, instruction, lineNumber);
	else if(instruction == "INR")
		INR(line, R, lineNumber);
	else if(instruction == "DCR")
		DCR(line, R, lineNumber);
	/*Logical Instructions*/
	else if(instruction =="CMP")
		CMP(line, R, lineNumber);

	else if(instruction == "CPI")
		CPI(line, R, lineNumber);

	else if(instruction == "ANA" || instruction == "ORA" || instruction == "XRA" )
		ANA_ORA_XRA(line, R, instruction, lineNumber);

	else if(instruction == "ANI" ||instruction == "ORI" || instruction == "XRI" )
		ANI_ORI_XRI(line, R, instruction, lineNumber);

	else if(instruction == "RLC")
		RLC(R);

	else if(instruction == "RRC")
		RRC(R);

	else if(instruction == "RAL")
		RAL(R);

	else if(instruction == "RAR")
		RAR(R);

	else if(instruction == "CMA")
		CMA(R);

	else if(instruction == "CMC")
		CMC(R);

	else if(instruction == "STC")
		STC(R);
	else if(instruction == "HLT")
		return -10;
	else if(instruction == "NOP")
	  return (lineNumber -1);
	else
		cout<<"No such instruction in line :"<<lineNumber<<endl;

	return (lineNumber - 1);	//since this function is called by lvalue i in main, and i is index in main so, decreasing
								//lineNumber by 1 gives i its original index.
}

int main(){
	openMemory();
	cout<<"After the code is written write \"STOP\" to indicate the code is all done.\n";
	cout<<"Write your code\n";
	cout<<"--------------------------------------------------------------------------\n";
	registers R;
	vector<string> code;
	mappingLabel M;
	string line;
	int lineNumber = 1;
	while(lineNumber){
		getline(cin, line);
		if(line == "STOP"){
			break;
		}
		if(line[0] != '\0')
			code.push_back(line);
		if(line.find(':') != string::npos){
			labelPush(line, lineNumber, M);
		}
		lineNumber++;
	}
	int lengthOfCode = code.size();
	cout<<"------------------------------------------------------\n";
	cout<<"ERRORS:\n";
	for(int i = 0;i <(int) lengthOfCode; i++){
		if(i<0)
			break;
		i = instructionDecode(code[i], R, M, i+1);
	}
	cout<<"------------------------------------------------------\n";
	R.registerDisplay();
	cout<<"\n";
	R.flagDisplay();
	cin.get();
}
