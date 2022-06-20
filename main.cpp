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
	try{
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
		MVI(line, R);
	else if(instruction == "MOV")
		MOV(line, R);
	else if(instruction == "LDA" || instruction == "STA")
		LDA_STA(line, R);
	else if(instruction == "LXI")
		LXI(line, R);
	else if(instruction == "LDAX" || instruction == "STAX")
		LDAX_STAX(line, R, lineNumber);
	else if(instruction == "LHLD")
		LHLD(line, R);
	else if(instruction == "SHLD")
		SHLD(line, R);
	else if(instruction == "XCHG")
		XCHG(R);	
	/*Branching instruction*/
	else if(instruction == "JC" || instruction == "JP" ||  instruction == "JM" || instruction == "JZ")
		return JC_JP_JM_JZ(line, R, M, instruction, lineNumber);	//branching instruction have return because they represents
																	//where to go
	else if(instruction == "JMP" || instruction == "JNC" ||instruction == "JNZ" ||instruction == "JPE" ||instruction == "JPO" )
		return JMP_JNC_JNZ_JPE_JPO(line, R, M, instruction, lineNumber);
	/*Arithmetic Instruction*/
	else if(instruction == "ADD" || instruction == "ADC")
		ADD_ADC(line, R);
	else if(instruction == "ADI" || instruction == "ACI")
		ADI_ACI(line, R);
	else if(instruction == "SUB" || instruction == "SBB")
		SUB_SBB(line, R);
	else if(instruction == "SUI" || instruction == "SBI")
		SUI_SBI(line, R);
	else if(instruction == "INR")
		INR(line, R);
	else if(instruction == "DCR")
		DCR(line, R);
	else if(instruction == "INX" || instruction == "DCX")
		INX_DCX(line, R);
	else if(instruction == "DAA")
		DAA(R);
	else if(instruction == "DAD")
		DAD(line, R);
	/*Logical Instructions*/
	else if(instruction =="CMP")
		CMP(line, R);

	else if(instruction == "CPI")
		CPI(line, R);

	else if(instruction == "ANA" || instruction == "ORA" || instruction == "XRA" )
		ANA_ORA_XRA(line, R);

	else if(instruction == "ANI" ||instruction == "ORI" || instruction == "XRI" )
		ANI_ORI_XRI(line, R);

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

	catch(int errorName){
		switch(errorName){
		case error_data:
		cout << "No such data in line: " << lineNumber << endl;
		break;
		case error_register:
		cout << "No such register in line: " << lineNumber << endl;
		break;
		case error_space:
		cout << "Single space needed in line: " << lineNumber << endl;
		break;
		case error_H:
		cout << "Data must end with 'H' in line: " << lineNumber << endl;
		break;
		case error_instructionSize:
		cout << "Missing full instruction in line: " << lineNumber << endl;
		break;
		case error_flag:
		cout << "No such flag in line: " << lineNumber << endl;
		break;
		case error_registerPair:
		cout << "No such register pair in line: " << lineNumber << endl;
		break;
		case error_memoryExceed:
		cout << "Memory exceed from instruction in line: " << lineNumber << endl;
		break;
		case error_label:
		cout << "No such label in line: "<< lineNumber << endl;
		return (lineNumber - 1);
		default:
		cout << "Error in line: " << lineNumber << endl;
		}
		return (lineNumber - 1);
	}
}



int main(int argc, char* argv[]){
	openMemory();
	setMemory();
	registers R;
	vector<string> code;
	mappingLabel M;
	string line;
	int lineNumber = 1;
	if(argc == 1){
		cout<<"After the code complition enter \"EXIT/exit\", to exit code mode and to execute.\n";
		cout<<"---------------------------Write your code---------------------------------\n";
		cout<<"---------------------------------------------------------------------------\n";
		while(lineNumber){
			getline(cin, line);
			if(line == "EXIT" || line == "exit"){
				break;
			}
			if(line[0] != '\0'){
				codeTransfer(line);
				code.push_back(line);
			}
			if(line.find(':') != string::npos){
				labelPush(line, lineNumber, M);
			}
			lineNumber++;
		}
	}
	else{
		cout << "Reading from file...\n";
		cout << "...\n";
		cout << "...\n";
		codeFromFile(argv[1], code, M, lineNumber);
	}
	cout<<"------------------------------------------------------\n";
	cout<<"ERRORS:\n";
	for(int i = 0;i <(int) lineNumber; i++){
		if(i<0)
			break;
		i = instructionDecode(code[i], R, M, i+1);
	}
	cout<<"------------------------------------------------------\n";
	R.registerDisplay();
	cout<<"\n";
	R.flagDisplay();
	cout << "\n";
	while (1){
		char choice;
		cout << "Do you want to see memory[y/n]: ";
		cin >> choice;
		if(choice == 'n' || choice == 'N')
		return 0;
		seeMemory();
	}
}
