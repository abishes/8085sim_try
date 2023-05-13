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

string errors_container[9]={"No such data in line: ", "No such register in line: ", "Data must end with 'H' in line: ",
		"Missing full instruction in line: ", "No such flag in line: ", "No such register pair in line: ",
		"Memory exceed from instruction in line: ", "No such label in line: ", "No such instruction in line : "};

int (*exec1[2])(string&, registers&, mappingLabel&, string, int)={JC_JP_JM_JZ, JMP_JNC_JNZ_JPE_JPO };
map<string, int> instructionTofunction={
										{"MVI",0},{"MOV",1},{"LDA",2},{"STA",2},{"LXI",3},{"LDAX",4},{"STAX",4},{"LHLD",5},{"SHLD",6},{"XCHG",7},

										{"ADD",8},{"ADC",8},{"ADI",9},{"ACI",9},{"SUB",10},{"SBB",10},{"SUI",11},{"SBI",11},{"INR",12},{"DCR",13},{"INX",14},{"DCX", 14},{"DAA",15},{"DAD",16},
											
										{"CMP",17},{"CPI",18},{"ANA",19},{"ORA",19},{"XRA",19},{"ANI",20},{"ORI",20},{"XRI",20},{"RLC",21},{"RRC",22},{"RAL",23},{"RAR",24},{"CMA",25},{"CMC",26},{"STC",27}
										};

void (*exec2[28])(string&, registers&)={
										MVI, MOV, LDA_STA, LXI, LDAX_STAX, LHLD, SHLD, XCHG,/*Data transfer instructions*/
										ADD_ADC, ADI_ACI, SUB_SBB, SUI_SBI,INR, DCR, INX_DCX, DAA, DAD, /*Arithmetic Instructions*/
										CMP, CPI, ANA_ORA_XRA, ANI_ORI_XRI, RLC, RRC, RAL, RAR, CMA, CMC, STC/*Logical Instructions*/
										};

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
		if (line[i] == ' ' || line[i] == '\0'){
			break;
		}
		instruction.push_back(line[i]);
	}
	if(instructionTofunction.find(instruction) != instructionTofunction.end()){
			exec2[instructionTofunction[instruction]](line, R);
		}
	if(instruction == "HLT")
		return -10;
	if(instruction == "NOP")
		return (lineNumber -1);	
	/*Branching instruction*/
	if (instruction == "JC" || instruction == "JP" ||instruction == "JM" ||instruction == "JZ" ||
		instruction == "JMP" ||instruction == "JNC" ||instruction == "JNZ" ||instruction == "JPE" ||instruction == "JPO")
		return exec1[instruction.size()-2](line, R, M, instruction, lineNumber);
	else{
		throw(error_instruction);
	}
	return (lineNumber - 1);	//since this function is called by lvalue i in main, and i is index in main so, decreasing
							//lineNumber by 1 gives i its original index.
	}

	catch(int errorName){
		cout << errors_container[errorName] << lineNumber << endl;
		cout<< "!!!!!!!!!!!!!!!!!!!!!!!exiting due to error!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		return -10;
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
		cout<<"------------------------------Write your code---------------------------------\n";
		cout<<"------------------------------------------------------------------------------\n";
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
		cout<<"----------------------------Reading from file---------------------------------\n";
		cout<<"------------------------------------------------------------------------------\n";
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
