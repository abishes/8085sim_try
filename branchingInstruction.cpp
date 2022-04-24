#include "branchingInstruction.h"
int JC_JP_JM_JZ(string& line, registers& R, mappingLabel& M, string instruction, int lineNumber){
	if(line[2]!= SPACE){
		cout<<"There must be space in line :"<<lineNumber<<endl;
		return 0;
	}
	if(instruction == "JC"){	//for JC instruction
		if(!R.flagName('C'))
			return (lineNumber - 1);	//since this function is called by lvalue i in main, and i is index starting with 0 
	}						//in main so, decreasing lineNumber by 1 gives i its original index.
	else if(instruction == "JP"){	//for JP instruction
		if(R.flagName('S'))
			return (lineNumber - 1);
	}
	else if(instruction == "JM"){	//for JM instruction
		if(!R.flagName('S'))
			return (lineNumber - 1);
	}
	else if(instruction == "JZ"){	//for JZ instruction
		if(!R.flagName('Z'))
			return (lineNumber - 1);
	}
	int whereIsLabel;
	string label;
	for(int i = 3; i < (int)line.length(); i++){ //since name of branch is located after "JC ",0 1 2 are occupied and we start i with 3
		if(line[i] == SPACE || line[i] == '\0')
			break;
		label.push_back(line[i]);
	}
	whereIsLabel = M.getLabel(label);	//returns the position where the label name is decleared
	return (whereIsLabel - 2);	//since whereIsLabel is 1 unit more than index, decreasing it by 2 gives 'i'(in main) the value 1 less
								// than the real value but i loops with i++ and next instruction to execuit is pointed by whereIsLabel
}

int JMP_JNC_JNZ_JPE_JPO(string& line, registers& R, mappingLabel& M, string instruction, int lineNumber){
	if(line[3]!= SPACE){
		cout<<"There must be space in line :"<<lineNumber<<endl;
		return 0;
	}
	if(instruction == "JNC"){	//for JNC instruction
		if(R.flagName('C'))
			return (lineNumber - 1);
	}
	else if(instruction == "JNZ"){	//for JNZ instruction
		if(R.flagName('Z'))
			return (lineNumber - 1);
	}
	else if(instruction == "JPE"){	//for JPE instruction
		if(!R.flagName('P'))
			return (lineNumber - 1);
	}
	else if(instruction == "JPO"){	//for JPO instruction
		if(!R.flagName('P'))
			return (lineNumber - 1);
	}
									//if no other then JMP
	int whereIsLabel;
	string label;
	for(int i = 4; i < (int)line.length(); i++){ 
		if(line[i] == SPACE || line[i] == '\0')
			break;
		label.push_back(line[i]);
	}
	whereIsLabel = M.getLabel(label);
	return (whereIsLabel - 2);
}
