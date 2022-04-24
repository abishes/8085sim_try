#include "branchAndMemory.h"

void labelPush(string line,int lineNumber, mappingLabel& M){
	string labelName;
	for(int i = 0; i < (int)line.length();i++){
		if(line[i] == ':')
			break;
		labelName.push_back(line[i]);
	}
	M.putLabel(labelName, lineNumber);
}

void mappingLabel::putLabel(string labelName,int lineNumber){
		if(label.find(labelName) != label.end()){
			return;
		}
		label[labelName]=lineNumber;
	}

int mappingLabel::getLabel(string labelName){
		int number = label[labelName];
		if(number != 0){
		int lineNumber = label[labelName];
		return lineNumber;
		}
		else{
			cout<<"No such label as \""<<labelName<<"\"\n";
			return -10;
		}
}
